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
Rect recthealth2;

Rect recthealth3;
Rect recthealth4;
Rect recthealth5;
Rect recthealth6;
Rect recthealth7;
Rect recthealth8;
Rect recthealth9;
Rect recthealth10;
Rect recthealth11;
Rect recthealth12;


float screenHeight{ 900 };
float screenWidth{ 1600 };
static bool ishealth = true;

void playermovement(float& x, float& y);
void clampScreen(float& x, float& y, float& width, float& height, float screenWidth, float screenHeight);
bool collisionCircle(float x0, float y0, float width0, float height0, float x1, float y1, float width1, float height1);
bool healhbarexist(float healthwidth, float x, float healthwidth2);


#endif // MAIN_H
