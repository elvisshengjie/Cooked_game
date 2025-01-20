#ifndef MAIN_H
#define MAIN_H

// Rect class definition
class Rect {
public: 
    float x{};
    float y{};
    float width{};
    float height{};

};


Rect rectleft;
Rect rectright;
Rect rectplayer;
Rect recthealth;
float screenHeight{ 900 };
float screenWidth{ 1600 };

void playermovement(float &x,float &y);
void clampScreen(float& x, float& y, float& width, float& height, float screenWidth, float screenHeight);

#endif // MAIN_H
