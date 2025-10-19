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

    float x, y;                   // T?a d?
    float tocDo;                  // T?c d? di chuy?n
    int frame;                    // Frame animation hi?n t?i
    Clock frameClock;             // Ð?ng h? d?i frame
    Clock doiHuongClock;          // Ð?ng h? d?i hu?ng ng?u nhiên (n?u c?n)
    Vector2f vanToc;              // Hu?ng di chuy?n (x, y)
    int type;                     // Lo?i quái (0,1,2)
    int huong;                    // Hu?ng di chuy?n (0=LÊN,1=PH?I,2=XU?NG,3=TRÁI)

public:
    bool alive;
    float c1, c2, c3, c4;         // Biên va ch?m (collision box)

    Enemy(float x_ = 0, float y_ = 0, int type_ = 0);
    virtual ~Enemy() {}

    virtual void datHuongNgauNhien();
    virtual void capNhat(float deltaTime);
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

// Các danh sách quái toàn c?c

extern std::vector<Enemy*> DanhSachEnemy;
#endif
