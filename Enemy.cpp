#include "Enemy.h"
#include <cstdlib>
#include <ctime>

vector<Enemy> DanhSachEnemy;
Texture Enemy::TEXTURE;
bool EnemyLoad = false;

Enemy::Enemy(float x_, float y_) {
    if (!EnemyLoad) {
        TEXTURE.loadFromFile("enemy1.png");
        EnemyLoad = true;
    }

    SPRITE.setTexture(TEXTURE);
    SPRITE.setTextureRect(IntRect(0, 0, 64, 64));

    x = x_;
    y = y_;
    SPRITE.setPosition(x, y);

    c1 = x;
    c2 = y;
    c3 = x + 64;
    c4 = y + 64;

    tocDo = 1.5f;
    alive = true;

    datHuongNgauNhien();
}

void Enemy::datHuongNgauNhien() {
    huong = rand() % 4;
    switch (huong) {
        case 0: vanToc = Vector2f(0, tocDo); break;
        case 1: vanToc = Vector2f(-tocDo, 0); break;
        case 2: vanToc = Vector2f(tocDo, 0); break;
        case 3: vanToc = Vector2f(0, -tocDo); break;
    }
}

void Enemy::capNhat(RenderWindow &window) {
    if (!alive) return;

    if (doiHuongClock.getElapsedTime().asSeconds() > 1.5f) {
        datHuongNgauNhien();
        doiHuongClock.restart();
    }

    // cap nhat vi trí
    x += vanToc.x;
    y += vanToc.y;

    // doi huong khi cham biên
    if (x < 0 || x + 64 > window.getSize().x) vanToc.x = -vanToc.x;
    if (y < 0 || y + 64 > window.getSize().y) vanToc.y = -vanToc.y;

    SPRITE.setPosition(x, y);

    // animation
    if (frameClock.getElapsedTime().asSeconds() > 0.15f) {
        frame = (frame + 1) % 3; // ví du: moi huong có 3 frame
        frameClock.restart();
    }

    // moi huong nam trên 1 hàng trong sprite sheet
    SPRITE.setTextureRect(IntRect(frame * 64, huong * 64, 64, 64));

    c1 = x;
    c2 = y;
    c3 = x + 64;
    c4 = y + 64;
}

void Enemy::Ve(RenderWindow &window) {
    if (alive)
        window.draw(SPRITE);
}

bool Enemy::kiemTraVaChamBom(const FloatRect& bomNo) {
    if (alive && SPRITE.getGlobalBounds().intersects(bomNo)) {
        alive = false;
        return true;
    }
    return false;
}

bool Enemy::kiemTraVaChamPlayer(const FloatRect& playerBounds) {
    if (alive && SPRITE.getGlobalBounds().intersects(playerBounds)) {
        return true; // Có the dùng de ket thúc game
    }
    return false;
}

