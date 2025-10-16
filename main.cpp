#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include "Player.h"
#include "Map_phu.h"
#include "Diem.h"
#include "QLAmThanh.h"
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
    //==== Am thanh =====
    QLAmThanh amThanh;
    amThanh.napAm("datbomb", "sound/datbom.wav");
    amThanh.napAm("no", "sound/no.wav");
    amThanh.phatNhacNen("sound/nhacnen.ogg");
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
         if (!player.alive) {
            amThanh.phatAm("no");
            diem.save("score.txt");
            cout << "Game Over! Diem: " << diem.get() << endl;
            window.close();
            continue;
        }
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


