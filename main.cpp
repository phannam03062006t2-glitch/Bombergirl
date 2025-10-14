#include <SFML/Graphics.hpp>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Diem.h"
// ===================================

using namespace std;
using namespace sf;

Map mapGame;
Diem diem;

extern vector<Bomb> QuanLyBomb;
extern vector<Enemy> DanhSachEnemy;

int main() {
    RenderWindow window(VideoMode(1700, 900), "my game");
    window.setFramerateLimit(60);
    srand(time(0));

    // Nap map
    try {
        mapGame = Map("map.txt");
    } catch (runtime_error& e) {
        cerr << "Loi map: " << e.what() << endl;
        return -1;
    }

    Player a;
    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;

    Texture TEXTURE;
    TEXTURE.loadFromFile("map.png");
    Sprite SPRITE(TEXTURE);

    // ==========================
    // ?? Thêm 3 quái khác hình
    // ==========================
    DanhSachEnemy.clear();
    DanhSachEnemy.push_back(Enemy(200, 200, 0)); // enemy1.png
    DanhSachEnemy.push_back(Enemy(600, 400, 1)); // enemy2.png
    DanhSachEnemy.push_back(Enemy(1000, 600, 2)); // enemy3.png
    // ==========================

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

        // Cap nhat enemy
        for (auto &enemy : DanhSachEnemy) {
            enemy.capNhat(window);
            if (enemy.kiemTraVaChamPlayer(a.SPRITE.getGlobalBounds())) {
                a.alive = false;
            }
        }

        // Kiem tra enemy chet khi trúng bomb
        for (auto &enemy : DanhSachEnemy) {
            for (auto &bomb : QuanLyBomb) {
                if (bomb.dangNo) {
                    FloatRect bomNo(
                        bomb.x - 64 * bomb.phamVi,
                        bomb.y - 64 * bomb.phamVi,
                        64 * (2 * bomb.phamVi + 1),
                        64 * (2 * bomb.phamVi + 1)
                    );
                    enemy.kiemTraVaChamBom(bomNo);
                }
            }
        }

        // ==========================
        //  Ve moi thu
        // ==========================
        window.clear();

        

        // Ve background map.png
        window.draw(SPRITE);

        // Ve cac doi tuong
        mapGame.ve(window);

        // Ve player, bom, quai,..
        for (auto &bomb : QuanLyBomb)
            bomb.Ve(window);

        a.Ve(window, Time);

        for (auto &enemy : DanhSachEnemy)
            enemy.Ve(window);

        // Ve diem len goc man 
        diem.draw(window);

        window.display();
    }
    return 0;
}

