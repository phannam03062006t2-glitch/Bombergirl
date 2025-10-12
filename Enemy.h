#ifndef ENEMY_H
#define ENEMY_H

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Enemy {
protected:
    Sprite SPRITE;
    static Texture TEXTURES[3];  // Chua anh chung
    static bool EnemyLoad;

    float x, y;
    float tocDo;
    int frame;
    int huong;
    Clock frameClock;
    Clock doiHuongClock;
    Vector2f vanToc;

public:
    bool alive;
    float c1, c2, c3, c4;

    Enemy(float x_ = 0, float y_ = 0);
    virtual ~Enemy() {}

    virtual void datHuongNgauNhien();
    virtual void capNhat(RenderWindow &window);
    virtual void Ve(RenderWindow &window);

    bool kiemTraVaChamBom(const FloatRect &bomNo);
    bool kiemTraVaChamPlayer(const FloatRect &playerBounds);
};

#endif
