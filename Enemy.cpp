#include "Enemy.h"
#include "Map_phu.h"
#include "Player.h"  
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

// Truy c?p danh s�ch bomb t? Player.cpp
extern std::vector<Bomb> QuanLyBomb;
// Truy c?p player 
extern Player a;

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

    c1 = x ;
    c2 = y ;
    c3 = x + 64 - 4;
    c4 = y + 64 - 4;
}

// ===================================================
//             C?P NH?T HU?NG NG?U NHI�N
// ===================================================
void Enemy::datHuongNgauNhien() {
    huong = rand() % 4;
    switch (huong) {
        case 0: vanToc = Vector2f(0, -1); break; // l�n
        case 1: vanToc = Vector2f(1, 0);  break; // ph?i
        case 2: vanToc = Vector2f(0, 1);  break; // xu?ng
        case 3: vanToc = Vector2f(-1, 0); break; // tr�i
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

    // Di chuy?n t?m th?i
    x += vanToc.x * tocDo;
    y += vanToc.y * tocDo;
    SPRITE.setPosition(x, y);

    // C?p nh?t v�ng va ch?m
    c1 = x ;
    c2 = y ;
    c3 = x + 64 - 4;
    c4 = y + 64 - 4;

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

    // --- Kh�ng di xuy�n qua BOM CHUA N? ---
    if (!chamTuong) {
        for (size_t i = 0; i < QuanLyBomb.size(); ++i) {
            const Bomb &b = QuanLyBomb[i];
            if (!b.dangNo) {
                // v�ng bomb chua n? l� � 64x64 ? v? tr� b.x-32, b.y-32
                FloatRect bombRect(b.x - 32.f, b.y - 32.f, 64.f, 64.f);
                FloatRect enemyRect(x, y, 64.f, 64.f);
                if (enemyRect.intersects(bombRect)) {
                    chamTuong = true;
                    break;
                }
            }
        }
    }

    // N?u ch?m (tu?ng ho?c bomb chua n?) -> l�i l?i v� d?i hu?ng
    if (chamTuong) {
        x -= vanToc.x * tocDo;
        y -= vanToc.y * tocDo;
        SPRITE.setPosition(x, y);
        datHuongNgauNhien();
    }

    // --- KI?M TRA VA CH?M V?I PLAYER (TR? M?T M�U / CH?T) ---
    {
        // Ki?m tra b?o d?m player t?n t?i 
        FloatRect enemyRect(x, y, 64.f, 64.f);

        // D�ng v�ng va ch?m player c� trong Player class 
        FloatRect playerRect(a.c1, a.c2, a.c3 - a.c1, a.c4 - a.c2);
        if (enemyRect.intersects(playerRect) && a.alive) {
            if (a.thoiGianBatTu <= 0.0f) {
                a.health--;
                a.thoiGianBatTu = 3.f; // th?i gian b?t t?
                a.out = true;
                if (a.health <= 0) {
                    a.alive = false;
                }
            }
            // Khi ch?m player, qu�i c� th? d?i hu?ng d? tr�nh ch?ng ch�o li�n t?c
            datHuongNgauNhien();
        }
    }

    // --- N?U BOM �ANG N? (dangNo) -> KI?M TRA V�NG N?, N?U TR�NG TH� QU�I CH?T ---
    for (size_t i = 0; i < QuanLyBomb.size(); ++i) {
    const Bomb &b = QuanLyBomb[i];
    if (!b.dangNo) continue;

    if (c1 >= b.c3 + 64 * b.phamVi) continue; // enemy qu� ph?i
    if (c3 <= b.c1 - 64 * b.phamVi) continue; // enemy qu� tr�i
    if (c2 >= b.c4 + 64 * b.phamVi) continue; // enemy qu� du?i
    if (c4 <= b.c2 - 64 * b.phamVi) continue; // enemy qu� tr�n
    if (c3 <= b.c1 && c4 <= b.c2) continue;   // g�c tr�n tr�i
    if (c1 >= b.c3 && c4 <= b.c2) continue;   // g�c tr�n ph?i
    if (c2 >= b.c4 && c1 >= b.c3) continue;   // g�c du?i ph?i
    if (c2 >= b.c4 && c3 <= b.c1) continue;   // g�c du?i tr�i

    // N?u kh�ng roi v�o c�c v�ng lo?i tr? => tr�ng bom
    alive = false;
    break;
}

    // C?p nh?t animation (4 h�ng, m?i h�ng 3 frame)
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

