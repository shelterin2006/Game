#pragma once
#include <utility>

#include "../utils/gamedefs.h"
#include "Resource.h"

struct Animation {
    // --- DỮ LIỆU ---
    string key;
    Texture2D spritesheet;  // Tấm ảnh chứa tất cả các khung hình
    int frameCount;         // Tổng số khung hình của animation
    Rectangle frameRec;     // Hình chữ nhật để cắt (source) từ spritesheet

    float frameTime;        // Thời gian hiển thị mỗi khung hình (ví dụ: 0.1 giây)
    bool loop;              // Animation có tự động lặp lại khi kết thúc không?
    float impactTime;       // (Tùy chọn) Thời điểm "va chạm" trong animation, tính bằng giây.
                            // Rất hữu ích cho animation tấn công.

    bool isPlaying;         // Animation có đang chạy không?
    int currentFrame;       // Khung hình hiện tại đang được hiển thị (từ 0 đến frameCount-1)
    float frameTimer;       // Bộ đếm thời gian để biết khi nào cần chuyển khung hình
    Animation()
        : frameCount(1), frameRec({0,0,0,0}), frameTime(0.1f), loop(true), impactTime(0.0f),
          isPlaying(false), currentFrame(0), frameTimer(0.0f) {}
    Animation(string key, int frames,
        float time, bool loops, float impact = 0.0f)
        : frameCount(frames), frameTime(time), loop(loops), impactTime(impact),
          isPlaying(false), currentFrame(0), frameTimer(0.0f),
            key(key)
    {
        spritesheet = Resource::getInstance().getTexture2D(*this);
        frameRec = {
            0.0f,
            0.0f,
            (float)spritesheet.width / frameCount,
            (float)spritesheet.height
        };
    }
    void Update() {
        if (!isPlaying) {
            return; // Không làm gì nếu animation không chạy
        }
        frameTimer += GetFrameTime();
        if (frameTimer >= frameTime) {
            frameTimer -= frameTime; // Trừ đi thay vì reset về 0 để chính xác hơn
            currentFrame++;
            if (currentFrame >= frameCount) {
                if (loop) {
                    currentFrame = 0; // Quay về frame đầu nếu lặp
                } else {
                    currentFrame = frameCount - 1; // Dừng ở frame cuối
                    isPlaying = false;             // Dừng animation
                }
            }
        }
        frameRec.x = (float)currentFrame * frameRec.width;
    }
    void Play() {
        // Nếu animation không lặp và đã chạy xong, ta reset nó lại
        if (!loop && !isPlaying && currentFrame == frameCount - 1) {
            currentFrame = 0;
            frameTimer = 0.0f;
        }
        isPlaying = true;
    }
    void Pause() {
        isPlaying = false;
    }
    void Stop() {
        isPlaying = false;
        currentFrame = 0;
        frameTimer = 0.0f;
        frameRec.x = 0.0f;
    }
};