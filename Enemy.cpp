#include "Enemy.h"
#include "Map_phu.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// ========================
// Static members
// ========================
Texture Enemy::TEXTURES[3];
bool Enemy::EnemyLoad = false;

std::vector<Enemy1> DanhSachEnemy1;
std::vector<Enemy2> DanhSachEnemy2;
std::vector<Enemy3> DanhSachEnemy3;

// ===================================================
//                  KH?I T?O CHUNG
// ===================================================
Enemy::Enemy(float x_, float y_, int type_) {
    if (!EnemyLoad) {
        TEXTURES[0].loadFromFile("assets/enemy1.png");
        TEXTURES[1].loadFromFile("assets/enemy2.png");
        TEXTURES[2].loadFromFile("assets/enemy3.png");
        EnemyLoad = true;
        srand((unsigned)time(NULL));
    }

    SPRITE.setTexture(TEXTURES[type_]);
    SPRITE.setTextureRect(IntRect(0, 0, 64, 64));
    SPRITE.setPosition(x_, y_);
    SPRITE.setScale(1.f, 1.f);

    x = x_;
    y = y_;
    tocDo = 2.0f;
    alive = true;
    frame = 0;
    huong = rand() % 4;
    datHuongNgauNhien();

    c1 = x;
    c2 = y;
    c3 = x + 64;
    c4 = y + 64;
}

// ===================================================
//             C?P NH?T HU?NG NG?U NHIÊN
// ===================================================
void Enemy::datHuongNgauNhien() {
    huong = rand() % 4;
    switch (huong) {
        case 0: vanToc = Vector2f(0, -1); break; // lên
        case 1: vanToc = Vector2f(1, 0);  break; // ph?i
        case 2: vanToc = Vector2f(0, 1);  break; // xu?ng
        case 3: vanToc = Vector2f(-1, 0); break; // trái
    }
}

// ===================================================
//             VA CH?M TU?NG
// ===================================================
bool VaChamWall_Enemy(const Enemy& e, const Wall& w) {
    if (e.c1 >= w.c3) return false;
    if (e.c3 <= w.c1) return false;
    if (e.c2 >= w.c4) return false;
    if (e.c4 <= w.c2) return false;
    return true;
}

bool VaChamWall2_Enemy(const Enemy& e, const Wall2& w) {
    if (e.c1 >= w.c3) return false;
    if (e.c3 <= w.c1) return false;
    if (e.c2 >= w.c4) return false;
    if (e.c4 <= w.c2) return false;
    return true;
}

// ===================================================
//               C?P NH?T ENEMY
// ===================================================
void Enemy::capNhat(float deltaTime) {
    if (!alive) return;

    // Di chuy?n
    x += vanToc.x * tocDo;
    y += vanToc.y * tocDo;
    SPRITE.setPosition(x, y);

    // C?p nh?t vùng va ch?m
    c1 = x;
    c2 = y;
    c3 = x + 64;
    c4 = y + 64;

    bool chamTuong = false;

    // Va ch?m tu?ng thu?ng
    for (int i = 0; i < (int)QuanLyWall.size(); i++) {
        if (VaChamWall_Enemy(*this, QuanLyWall[i])) {
            chamTuong = true;
            break;
        }
    }

    // Va ch?m tu?ng c?ng
    if (!chamTuong) {
        for (int i = 0; i < (int)QuanLyWall2.size(); i++) {
            if (VaChamWall2_Enemy(*this, QuanLyWall2[i])) {
                chamTuong = true;
                break;
            }
        }
    }

    // N?u ch?m tu?ng thì d?i hu?ng
    if (chamTuong) {
        x -= vanToc.x * tocDo;
        y -= vanToc.y * tocDo;
        SPRITE.setPosition(x, y);
        datHuongNgauNhien();
    }

    // C?p nh?t animation (4 hàng, m?i hàng 3 frame)
    if (frameClock.getElapsedTime().asSeconds() > 0.15f) {
        frame = (frame + 1) % 3;  // 3 frame m?i hu?ng
        SPRITE.setTextureRect(IntRect(64 * frame, 64 * huong, 64, 64));
        frameClock.restart();
    }
}

// ===================================================
//                    V? ENEMY
// ===================================================
void Enemy::Ve(RenderWindow &window) {
    if (alive)
        window.draw(SPRITE);
}

// ===================================================
//          KI?M TRA VA CH?M BOM & PLAYER
// ===================================================
bool Enemy::kiemTraVaChamBom(const FloatRect &bomNo) {
    FloatRect bounds(x, y, 64, 64);
    return bounds.intersects(bomNo);
}

bool Enemy::kiemTraVaChamPlayer(const FloatRect &playerBounds) {
    FloatRect bounds(x, y, 64, 64);
    return bounds.intersects(playerBounds);
}

// ===================================================
//                   Enemy1/2/3
// ===================================================
Enemy1::Enemy1(float x_, float y_) : Enemy(x_, y_, 0) {
    tocDo = 1.8f;
}

Enemy2::Enemy2(float x_, float y_) : Enemy(x_, y_, 1) {
    tocDo = 2.2f;
}

Enemy3::Enemy3(float x_, float y_) : Enemy(x_, y_, 2) {
    tocDo = 2.5f;
}

