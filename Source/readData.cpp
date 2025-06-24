#include "readData.h"

void readData() {
    ifstream in("resources/dataGame.txt");
    if (!in.is_open()) {
        cerr << "Error"; return;
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
}
