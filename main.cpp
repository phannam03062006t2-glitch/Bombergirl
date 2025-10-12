#include <SFML/Graphics.hpp>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Map.h"
#include "Diem.h"

// ===================================

using namespace std;
using namespace sf;

Map mapGame;
Diem diem;

extern vector<Bomb> QuanLyBomb;
//  doi vector Enemy -> vector<Enemy*> de chua các loai quái ke thua
vector<Enemy*> DanhSachEnemy;

int main() {
    RenderWindow window(VideoMode(1700, 900), "my game");
    window.setFramerateLimit(60);
    srand(time(0));

    // Nap map
    try {
        mapGame = Map("map.txt");
    } catch (runtime_error& e) {
        cerr << "L?i map: " << e.what() << endl;
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
    //  Thêm 3 loai quái khác nhau (ke thua Enemy)
    // ==========================
    DanhSachEnemy.clear();
    DanhSachEnemy.push_back(new Enemy1(200, 200));   // enemy1.png
    DanhSachEnemy.push_back(new Enemy2(600, 400));   // enemy2.png
    DanhSachEnemy.push_back(new Enemy3(1000, 600));  // enemy3.png
    // ==========================

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        Time += deltaTime;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        // ==========================
        //  Cap nhat bomb & player
        // ==========================
        CapNhapBomb(QuanLyBomb, deltaTime);
        CapNhapPlayer(a);

        // ==========================
        //  Cap nhat enemy
        // ==========================
        for (auto &enemy : DanhSachEnemy) {
            enemy->capNhat(window);
            if (enemy->kiemTraVaChamPlayer(a.SPRITE.getGlobalBounds())) {
                a.alive = false;
            }
        }

        // ==========================
        //  Kiem tra enemy trúng bomb
        // ==========================
        for (auto &enemy : DanhSachEnemy) {
            for (auto &bomb : QuanLyBomb) {
                if (bomb.dangNo) {
                    FloatRect bomNo(
                        bomb.x - 64 * bomb.phamVi,
                        bomb.y - 64 * bomb.phamVi,
                        64 * (2 * bomb.phamVi + 1),
                        64 * (2 * bomb.phamVi + 1)
                    );
                    enemy->kiemTraVaChamBom(bomNo);
                }
            }
        }

        // ==========================
        //  Ve moi thu
        // ==========================
        window.clear();

        // Ve ban do truoc (nen)
        mapGame.ve(window);

        // Ve background map.png
        window.draw(SPRITE);

        // Ve bomb
        for (auto &bomb : QuanLyBomb)
            bomb.Ve(window);

        // Ve player
        a.Ve(window, Time);

        // Ve enemy
        for (auto &enemy : DanhSachEnemy)
            enemy->Ve(window);

        // Ve diem lên góc màn
        diem.draw(window);

        window.display();
    }

    // ==========================
    //  Giai phóng bo nho Enemy
    // ==========================
    for (auto enemy : DanhSachEnemy) delete enemy;
    DanhSachEnemy.clear();

    return 0;
}

