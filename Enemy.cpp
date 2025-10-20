#include "Enemy.h"
#include "Diem.h"
#include "Map_phu.h"
#include "Player.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

// =======================
// Static members
// ========================
Texture Enemy::TEXTURES[3];
bool Enemy::EnemyLoad = false;

std::vector<Enemy*> DanhSachEnemy;
// Truy c?p danh sách bomb t? Player.cpp
extern std::vector<Bomb> QuanLyBomb;
// Truy c?p player 
extern Player a;
int SoLuongQuai;

// ===================================================
//                  KH?I T?O CHUNG
// ===================================================
Enemy::Enemy(float x_, float y_, int type_) {
    if (!EnemyLoad) {
        // T?i 3 file texture (b?n ph?i có các file trong thu m?c assets)
        TEXTURES[0].loadFromFile("assets/enemy1.png");
        TEXTURES[1].loadFromFile("assets/enemy2.png");
        TEXTURES[2].loadFromFile("assets/enemy3.png");
        EnemyLoad = true;
        srand((unsigned)time(NULL));
    }

    type = type_;
    SPRITE.setTexture(TEXTURES[type]);
    // m?c d?nh m?i sprite 64x64, 4 hàng hu?ng, 3 c?t frame -> header s? set khi anim
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

    // khung va ch?m (di?u ch?nh d? phù h?p sprite)
    c1 = x + 10;
    c2 = y + 10;
    c3 = x + 64 - 10;
    c4 = y + 64 - 10;
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
//             VA CH?M TU?NG (dành cho Enemy)
// ===================================================
bool VaChamWall_Enemy(const Enemy& e, const Wall& w) {
    if (e.c1 - 2 > w.c3) return false;
    if (e.c3 + 2 < w.c1) return false;
    if (e.c2 - 2 > w.c4) return false;
    if (e.c4 + 2 < w.c2) return false;
    return true;
}

bool VaChamWall2_Enemy(const Enemy& e, const Wall2& w) {
    if (e.c1 - 2 > w.c3) return false;
    if (e.c3 + 2 < w.c1) return false;
    if (e.c2 - 2 > w.c4) return false;
    if (e.c4 + 2 < w.c2) return false;
    return true;
}

// ===================================================
//               C?P NH?T ENEMY
// ===================================================
void Enemy::capNhat(float deltaTime, int& SoLuongQuai){
    if (!alive) return;

    // Di chuy?n t?m th?i (dùng tocDo làm t?c d? pixel/frame)
    x += vanToc.x * tocDo;
    y += vanToc.y * tocDo;
    SPRITE.setPosition(x, y);

    // C?p nh?t vùng va ch?m
    c1 = x + 10;
    c2 = y + 10;
    c3 = x + 64 - 10;
    c4 = y + 64 - 10;

    bool chamTuong = false;

    // Va ch?m v?i wall (Wall - tu?ng c? d?nh)
    for (int i = 0; i < (int)QuanLyWall.size(); i++) {
        if (VaChamWall_Enemy(*this, QuanLyWall[i])) {
            chamTuong = true;
            break;
        }
    }

    // Va ch?m v?i wall2 (có th? là g?ch có th? b? phá)
    if (!chamTuong) {
        for (int i = 0; i < (int)QuanLyWall2.size(); i++) {
            if (VaChamWall2_Enemy(*this, QuanLyWall2[i])) {
                chamTuong = true;
                break;
            }
        }
    }

    // Không di xuyên qua BOM chua n?
    if (!chamTuong) {
        for (size_t i = 0; i < QuanLyBomb.size(); ++i) {
            const Bomb &b = QuanLyBomb[i];
            if (!b.dangNo) {
                // vùng bomb chua n? là ô 64x64 ? v? trí b.x-32, b.y-32
                FloatRect bombRect(b.c1, b.c2 , b.c3 - b.c1, b.c4 - b.c2);
                FloatRect enemyRect(c1, c2, c3 - c1, c4 - c2);
                if (enemyRect.intersects(bombRect)) {
                    chamTuong = true;
                    break;
                }
            }
        }
    }

    // N?u ch?m -> lùi l?i và d?i hu?ng ng?u nhiên
    if (chamTuong) {
        x -= vanToc.x * tocDo;
        y -= vanToc.y * tocDo;
        SPRITE.setPosition(x, y);
        datHuongNgauNhien();
    }

    // --- KI?M TRA VA CH?M V?I PLAYER (tr? m?t máu / làm ch?m) ---
    {
        // vùng va ch?m enemy (dùng bounding box)
        FloatRect enemyRect(c1, c2, c3 - c1, c4 - c2);
        // vùng player t? bi?n global a (player)
        FloatRect playerRect(a.c1, a.c2, a.c3 - a.c1, a.c4 - a.c2);
        if (enemyRect.intersects(playerRect) && a.alive) {
            if (a.thoiGianBatTu <= 0.0f) {
                a.health--;
                a.thoiGianBatTu = 3.f; // th?i gian b?t t?
                if (a.health <= 0) {
                    a.alive = false;
                }
            }
        }
    }

    // --- KI?M TRA BOM ÐANG N? (dangNo) -> N?U ROI VÀO VÙNG N? THÌ QUÁI CH?T ---
    for (size_t i = 0; i < QuanLyBomb.size(); ++i) {
        const Bomb &b = QuanLyBomb[i];
        if (!b.dangNo) continue;

        // Các di?u ki?n tuong t? VaChamNo trong Player.cpp
        if (c1 >= b.c3 + 64 * b.phamVi) continue; // enemy quá ph?i
        if (c3 <= b.c1 - 64 * b.phamVi) continue; // enemy quá trái
        if (c2 >= b.c4 + 64 * b.phamVi) continue; // enemy quá du?i
        if (c4 <= b.c2 - 64 * b.phamVi) continue; // enemy quá trên
        if (c3 <= b.c1 && c4 <= b.c2) continue;   // góc trên trái
        if (c1 >= b.c3 && c4 <= b.c2) continue;   // góc trên ph?i
        if (c2 >= b.c4 && c1 >= b.c3) continue;   // góc du?i ph?i
        if (c2 >= b.c4 && c3 <= b.c1) continue;   // góc du?i trái

        // n?u không roi vào vùng lo?i tr? => b? n? trúng
        alive = false;
        SoLuongQuai--;
        diemGame.add(100);
        break;
    }

    // C?p nh?t animation (gi? s? m?i hàng là 1 hu?ng, m?i hàng 3 frame)
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
//          KI?M TRA VA CH?M BOM & PLAYER (TI?N ÍCH)
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
    tocDo = 1.f;
}

Enemy2::Enemy2(float x_, float y_) : Enemy(x_, y_, 1) {
    tocDo = 1,5.f;
}

Enemy3::Enemy3(float x_, float y_) : Enemy(x_, y_, 2) {
    tocDo = 2,5.f;
}
