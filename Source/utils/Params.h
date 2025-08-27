#pragma once
#include "gamedefs.h"

struct Params {
    std::map<std::string, std::string> params;
    int getInt(const std::string& key, int defaultValue = 0) const {
        auto it = params.find(key);
        if (it != params.end()) {
            try {
                return std::stoi(it->second);
            } catch (const std::invalid_argument& ia) {
                TraceLog(LOG_WARNING, "ACTION_PARAMS: Invalid argument for key '%s'. Value: '%s'", key.c_str(), it->second.c_str());
            } catch (const std::out_of_range& oor) {
                TraceLog(LOG_WARNING, "ACTION_PARAMS: Out of range for key '%s'. Value: '%s'", key.c_str(), it->second.c_str());
            }
        }
        return defaultValue;
    }
    [[nodiscard]] std::string getString(const std::string& key, const std::string& defaultValue = "") const {
        auto it = params.find(key);
        if (it != params.end()) {
            return it->second;
        }
        return defaultValue;
    }
    void parseParams(const std::string& paramString) {
        params.clear(); // Xóa các tham số cũ trước khi phân tích chuỗi mới
        if (paramString.empty()) {
            return;
        }
        std::stringstream ss(paramString);
        std::string segment;
        while (std::getline(ss, segment, '&')) {
            size_t eq_pos = segment.find('=');
            if (eq_pos != std::string::npos) {
                std::string key = segment.substr(0, eq_pos);
                std::string value = segment.substr(eq_pos + 1);
                params[key] = value;
            } else {
                params[segment] = "";
                TraceLog(LOG_WARNING, "ACTION_PARAMS: Segment '%s' in param string has no '='. Treating as key with empty value.", segment.c_str());
            }
        }
    }
    bool parseParamsFromFile(const std::string& filePath) {
        std::ifstream infile(filePath); // Mở tệp tin để đọc
        if (!infile.is_open()) {
            TraceLog(LOG_WARNING, "ACTION_PARAMS: Failed to open file for parsing: '%s'", filePath.c_str());
            return false; // Trả về false nếu không mở được tệp
        }
        std::string fileContent;
        std::string line;
        while (std::getline(infile, line)) {
            // Bỏ qua các dòng trống hoặc chỉ chứa khoảng trắng
            if (line.find_first_not_of(" \t\r\n\f\v") == std::string::npos) {
                continue;
            }
            if (line[0] == '#') {
                continue;
            }
            line.erase(0, line.find_first_not_of(" \t\r\n\f\v"));
            line.erase(line.find_last_not_of(" \t\r\n\f\v") + 1);
            // Thêm ký tự '&' để các dòng sau có thể được phân tách bởi parseParams ban đầu
            if (!fileContent.empty()) {
                fileContent += '&';
            }
            fileContent += line;
        }
        infile.close(); // Đóng tệp tin
        // Phân tích nội dung đã đọc
        parseParams(fileContent);
        return true; // Trả về true để báo hiệu thành công
    }
};