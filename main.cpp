#include <SFML/Graphics.hpp>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
using namespace std;
using namespace sf;


int main() {
    RenderWindow window(VideoMode(1700, 900), "my game");
    window.setFramerateLimit(60);
    srand(time(0));

    Player a;
    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;

    Texture TEXTURE;
    TEXTURE.loadFromFile("map.png");
    Sprite SPRITE(TEXTURE);

    // ? Thêm quái
    DanhSachEnemy.push_back(Enemy(200, 200));
    DanhSachEnemy.push_back(Enemy(400, 400));
    DanhSachEnemy.push_back(Enemy(800, 600));

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        Time += deltaTime;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        // Cap nhat bomb & player
        CapNhapBomb(QuanLyBomb, deltaTime);
        CapNhapPlayer(a);

        // ? Cap nhat enemy
        for (auto &enemy : DanhSachEnemy) {
            enemy.capNhat(window);
            if (enemy.kiemTraVaChamPlayer(a.SPRITE.getGlobalBounds())) {
                a.alive = false;
            }
        }

        // ? Kiem tra enemy chet khi trúng va cham?
        for (auto &enemy : DanhSachEnemy) {
            for (auto &bomb : QuanLyBomb) {
                if (bomb.dangNo) {
                    FloatRect bomNo(bomb.x - 64 * bomb.phamVi, bomb.y - 64 * bomb.phamVi,
                                    64 * (2 * bomb.phamVi + 1), 64 * (2 * bomb.phamVi + 1));
                    enemy.kiemTraVaChamBom(bomNo);
                }
            }
        }

        window.clear();
        window.draw(SPRITE);

        for (auto &bomb : QuanLyBomb)
            bomb.Ve(window);

        a.Ve(window, Time);

        // ? Ve enemy
        for (auto &enemy : DanhSachEnemy)
            enemy.Ve(window);

        window.display();
    }
    return 0;
}
