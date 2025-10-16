#include <SFML/Graphics.hpp>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include "Player.h"
#include "Map_phu.h"
#include "Diem.h"
// ===================================

using namespace std;
using namespace sf;

Diem diem;


//extern vector<Enemy1> DanhSachEnemy1;
//extern vector<Enemy2> DanhSachEnemy2;
//extern vector<Enemy3> DanhSachEnemy3;

int main() {
    RenderWindow window(VideoMode(1700, 900), "my game");
    window.setFramerateLimit(60);
    srand(time(0));

    // Nap map
    input_map();

    Player a;
    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;

    Texture TEXTURE;
    TEXTURE.loadFromFile("assets/map.png");
    Sprite SPRITE(TEXTURE);

    // ==========================
    // ?? Thêm 3 quái khác hình
    // ==========================
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
        
        // ==========================
        window.clear();

        // Ve background map.png
        window.draw(SPRITE);

        // Ve player, bom, quai,..
        for (auto &bomb : QuanLyBomb)
            bomb.Ve(window);

        a.Ve(window, Time);

        // Ve cac doi tuong
        veWall(window);
        
        // Ve diem
        diem.draw(window);

        window.display();
    }
    return 0;
}
