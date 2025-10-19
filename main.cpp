#include <SFML/Graphics.hpp>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include "Player.h"
#include "Map_phu.h"
#include "Diem.h"
#include "Enemy.h"
#include "QLAmThanh.h"
#include "ThanhMau.h"
// ===================================

using namespace std;
using namespace sf;

Diem diem;
Player a;

int main() {
    RenderWindow window(VideoMode(1700, 900), "my game");
    window.setFramerateLimit(60);
    srand((unsigned)time(NULL));
    ThanhMau thanhMau(3); 

    // =================== N?N ===================
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/anhnen.png")) {
        cout << "Khong the tai nen.png!" << endl;
    }
    Sprite backgroundSprite(backgroundTexture);
    Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(1700.f / textureSize.x, 900.f / textureSize.y);

    // Nap map
    input_map();
    
    // khai báo
    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;

    Texture TEXTURE;
    TEXTURE.loadFromFile("assets/map.png");
    Sprite SPRITE(TEXTURE);
    
    amThanh.napAm("datbomb", "sound/datbom.wav");
    amThanh.napAm("no", "sound/no.wav");
    amThanh.phatNhacNen("sound/nhacnen.ogg");
    
    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();
        Time += deltaTime;

        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) window.close();
        }

        CapNhapBomb(QuanLyBomb, deltaTime);
        CapNhapPlayer(a);
        thanhMau.capNhat(a.health);
        
        for (auto &e : DanhSachEnemy1) e.capNhat(deltaTime);
        for (auto &e : DanhSachEnemy2) e.capNhat(deltaTime);
        for (auto &e : DanhSachEnemy3) e.capNhat(deltaTime);
       
        if (!a.alive) {
            amThanh.phatAm("no");
            diem.save("score.txt");
            cout << "Game Over! Diem: " << diem.get() << endl;
            window.close();
            continue;
        }

        // ========================== V? ==========================
        window.clear();

        window.draw(backgroundSprite);  // ? V? n?n
        window.draw(SPRITE);            // ? V? map.png

        for (auto &bomb : QuanLyBomb)
            bomb.Ve(window);
        a.Ve(window, Time);
        for (auto &Enemy : DanhSachEnemy1)
            Enemy.Ve(window);
        for (auto &Enemy : DanhSachEnemy2)
            Enemy.Ve(window);
        for (auto &Enemy : DanhSachEnemy3)
            Enemy.Ve(window);
        veWall(window);
        diem.draw(window);
        thanhMau.ve(window);

        window.display();
    }
    return 0;
}

