#include "utils.h"
extern int screenWidth;
extern int screenHeight;
extern string title;
extern int FrameRate;
class logo {
private:
    Texture2D l = {};
public:
    logo() {
        l = LoadTexture("resources/1.jpeg");
    }
    ~logo(){UnloadTexture(l);}
    static bool readData();
    void display();
    void errorDataScreen();
};