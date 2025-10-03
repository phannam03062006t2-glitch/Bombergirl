#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

class Enemy {
protected:
    RectangleShape hinh;
    Vector2f vanToc;
    float tocDo = 1.0f;
    Clock doiHuongClock;

public:
    Enemy(float x, float y, Color mau);
    virtual void datHuongNgauNhien();
    virtual void capNhat(RenderWindow& cuaSo);
    virtual void ve(RenderWindow& cuaSo);
    virtual ~Enemy();
};

// loai quai 1
class Enemy1 : public Enemy {
public:
    Enemy1(float x, float y);
};

// loai quai 2
class Enemy2 : public Enemy {
public:
    Enemy2(float x, float y);
};

// loai quai 3
class Enemy3 : public Enemy {
public:
    Enemy3(float x, float y);
};

#endif

