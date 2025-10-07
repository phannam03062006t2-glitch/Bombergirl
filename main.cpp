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
    // Khoi tao cua so
    RenderWindow window(VideoMode(1700, 900), "my game");
    window.setFramerateLimit(60);

    // Khai bao
    Player a;
    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;

    // Khoi tao ban do
    Map map;
    try {
        map.napFile("map.txt");   // map.txt co cac loai: 0-nen, 1-tuong cung, 2-tuong pha, 3-co, 4-cay
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return -1;
    }

    // Khoi tao diem
    Diem diem;

    // Khoi tao enemy
    vector<Enemy*> enemies;
    enemies.push_back(new Enemy1(200.f, 200.f));
    enemies.push_back(new Enemy2(500.f, 500.f));
    enemies.push_back(new Enemy3(800.f, 300.f));

    // Vong lap game
    while (window.isOpen()) {
        // Cap nhat thoi gian
        deltaTime = clock.restart().asSeconds();
        Time += deltaTime;

        // Su kien
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        //--------------------------------------------CAP NHAT--------------------------------
        CapNhapBomb(QuanLyBomb, deltaTime);
        CapNhapPlayer(a);

        // Cap nhat enemy
        for (auto enemy : enemies) {
            enemy->capNhat(window);
        }

        //----------------------------------------------VE--------------------------------
        window.clear();

        // Ve ban do (nen, tuong, cay, co...)
        map.ve(window);

        // Ve bomb
        for (int i = 0; i < QuanLyBomb.size(); i++) {
            QuanLyBomb[i].Ve(window);
        }

        // Ve enemy
        for (auto enemy : enemies) {
            enemy->ve(window);
        }

        // Ve nguoi choi
        a.Ve(window, Time);

        // Ve diem
        diem.draw(window);

        window.display();
    }

    // Giai phong bo nho enemy
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    return 0;
}
