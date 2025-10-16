#ifndef ENEMY_H
#define ENEMY_H

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

// ====================== L?P CO S? ENEMY ======================
class Enemy {
protected:
    Sprite SPRITE;
    static Texture TEXTURES[3];   // Texture dùng chung cho 3 lo?i quái
    static bool EnemyLoad;        // Ch? load 1 l?n

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

    Enemy(float x_ = 0, float y_ = 0, int type_ = 0);
    virtual ~Enemy() {}

    virtual void datHuongNgauNhien();
    virtual void capNhat(RenderWindow &window);
    virtual void Ve(RenderWindow &window);

    bool kiemTraVaChamBom(const FloatRect &bomNo);
    bool kiemTraVaChamPlayer(const FloatRect &playerBounds);
};

// ====================== Enemy1 ======================
class Enemy1 : public Enemy {
public:
    Enemy1(float x_, float y_);
};

// ====================== Enemy2 ======================
class Enemy2 : public Enemy {
public:
    Enemy2(float x_, float y_);
};

// ====================== Enemy3 ======================
class Enemy3 : public Enemy {
public:
    Enemy3(float x_, float y_);
};

extern std::vector<Enemy1> DanhSachEnemy1;
extern std::vector<Enemy2> DanhSachEnemy2;
extern std::vector<Enemy3> DanhSachEnemy3;

#endif
