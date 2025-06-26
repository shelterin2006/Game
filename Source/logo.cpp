#include "logo.h"

bool logo::readData() {
    ifstream in("resources/dataGame.txt");
    if (!in.is_open()) {
        cerr << "Error"; return false;
    }
    string s;
    while (getline(in, s)) {
        stringstream ss(s);
        string t; ss >> t;
        if (t == "width:") ss >> screenWidth;
        if (t == "title:") getline(ss, title);
        if (t == "height:") ss >> screenHeight;
        if (t == "FPS:") ss >> FrameRate;
    }
    in.close();
    return true;
}

void logo::display() {
    float d = Utils::centered(l.width, screenWidth);
    float e = Utils::centered(l.height, screenHeight);
    DrawTexture(l, d, e, WHITE);
}

