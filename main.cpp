#include <SFML/Graphics.hpp>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include "Player.h"
#include "Map_phu.h"
#include "Diem.h"
#include "Enemy.h"
// ===================================

using namespace std;
using namespace sf;

Diem diem;


int main() {
    RenderWindow window(VideoMode(1700, 900), "my game");
    window.setFramerateLimit(60);
    srand(time(0));

    // Nap map
    input_map();
    
    
    // khai báo
    Player a;
    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;

    Texture TEXTURE;
    TEXTURE.loadFromFile("assets/map.png");
    Sprite SPRITE(TEXTURE);

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
        // Bomb
        for (auto &bomb : QuanLyBomb)
            bomb.Ve(window);
        // Player
        a.Ve(window, Time);
        // Enemy
        for (auto &Enemy : DanhSachEnemy1)
            Enemy.Ve(window);
        for (auto &Enemy : DanhSachEnemy2)
            Enemy.Ve(window);
        for (auto &Enemy : DanhSachEnemy3)
            Enemy.Ve(window);
        // Wall
        veWall(window);
        // Ve diem
        diem.draw(window);



        window.display();
    }
    return 0;
}

