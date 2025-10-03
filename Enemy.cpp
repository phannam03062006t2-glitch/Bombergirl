#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(float x, float y, Color mau) {
    hinh.setSize(Vector2f(64, 64));
    hinh.setFillColor(mau);
    hinh.setPosition(x, y);
    srand(time(0));
    datHuongNgauNhien();
}

void Enemy::datHuongNgauNhien() {
    int huong = rand() % 4;
    switch (huong) {
        case 0: vanToc = Vector2f(-tocDo, 0); break;  // trai
        case 1: vanToc = Vector2f(tocDo, 0); break;   // phai
        case 2: vanToc = Vector2f(0, -tocDo); break;  // len
        case 3: vanToc = Vector2f(0, tocDo); break;   // xuong
    }
}

void Enemy::capNhat(RenderWindow& cuaSo) {
    if (doiHuongClock.getElapsedTime().asSeconds() > 1.5f) {
        datHuongNgauNhien();
        doiHuongClock.restart();
    }

    hinh.move(vanToc);

    // gioi han cua so
    if (hinh.getPosition().x < 0 || hinh.getPosition().x + hinh.getSize().x > cuaSo.getSize().x) {
        vanToc.x = -vanToc.x;
    }
    if (hinh.getPosition().y < 0 || hinh.getPosition().y + hinh.getSize().y > cuaSo.getSize().y) {
        vanToc.y = -vanToc.y;
    }
}

void Enemy::ve(RenderWindow& cuaSo) {
    cuaSo.draw(hinh);
}

Enemy::~Enemy() {}

// loai quai 1
Enemy1::Enemy1(float x, float y) : Enemy(x, y, Color::Red) {}

// loai quai 2
Enemy2::Enemy2(float x, float y) : Enemy(x, y, Color::Blue) {}

// loai quai 3
Enemy3::Enemy3(float x, float y) : Enemy(x, y, Color::Green) {}

