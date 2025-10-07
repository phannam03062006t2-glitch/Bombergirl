#include <SFML/Graphics.hpp>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Diem.h"
#include "Enemy.h"
#include <vector>

using namespace std;
using namespace sf;

int main() {
    // Khá»Ÿi táº¡o cá»­a sá»•
    RenderWindow window(VideoMode(1700, 900), "my game");
    window.setFramerateLimit(60);

    // Khai bÃ¡o
    Player a;
    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;

    // Khá»Ÿi táº¡o báº£n Ä‘á»“
    Map map;
    try {
        map.napFile("map.txt");   // map.txt cÃ³ cÃ¡c loáº¡i: 0-ná»n, 1-tÆ°á»ng cá»©ng, 2-tÆ°á»ng phÃ¡, 3-cá», 4-cÃ¢y
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return -1;
    }

    // Khá»Ÿi táº¡o Ä‘iá»ƒm
    Diem diem;

    // Khá»Ÿi táº¡o enemy
    vector<Enemy*> enemies;
    enemies.push_back(new Enemy1(200.f, 200.f));
    enemies.push_back(new Enemy2(500.f, 500.f));
    enemies.push_back(new Enemy3(800.f, 300.f));

    // VÃ²ng láº·p game
    while (window.isOpen()) {
        // Cáº­p nháº­t thá»i gian
        deltaTime = clock.restart().asSeconds();
        Time += deltaTime;

        // Sá»± kiá»‡n
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        //--------------------------------------------Cáº¬P NHáº¬T--------------------------------
        CapNhapBomb(QuanLyBomb, deltaTime);
        CapNhapPlayer(a);

        // Cáº­p nháº­t enemy
        for (auto enemy : enemies) {
            enemy->capNhat(window);
        }

        //----------------------------------------------Váº¼--------------------------------
        window.clear();

        // Váº½ báº£n Ä‘á»“ (ná»n, tÆ°á»ng, cÃ¢y, cá»...)
        map.ve(window);

        // Váº½ bomb
        for (int i = 0; i < QuanLyBomb.size(); i++) {
            QuanLyBomb[i].Ve(window);
        }

        // Váº½ enemy
        for (auto enemy : enemies) {
            enemy->ve(window);
        }

        // Váº½ ngÆ°á»i chÆ¡i
        a.Ve(window, Time);

        // Váº½ Ä‘iá»ƒm
        diem.draw(window);

        window.display();
    }

    // Giáº£i phÃ³ng bá»™ nhá»› enemy
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    return 0;
}
