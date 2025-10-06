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
    // Khởi tạo cửa sổ
    RenderWindow window(VideoMode(1700, 900), "my game");
    window.setFramerateLimit(60);

    // Khai báo
    Player a;
    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;

    // Khởi tạo bản đồ
    Map map;
    try {
        map.napFile("map.txt");   // map.txt có các loại: 0-nền, 1-tường cứng, 2-tường phá, 3-cỏ, 4-cây
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return -1;
    }

    // Khởi tạo điểm
    Diem diem;

    // Khởi tạo enemy
    vector<Enemy*> enemies;
    enemies.push_back(new Enemy1(200.f, 200.f));
    enemies.push_back(new Enemy2(500.f, 500.f));
    enemies.push_back(new Enemy3(800.f, 300.f));

    // Vòng lặp game
    while (window.isOpen()) {
        // Cập nhật thời gian
        deltaTime = clock.restart().asSeconds();
        Time += deltaTime;

        // Sự kiện
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        //--------------------------------------------CẬP NHẬT--------------------------------
        CapNhapBomb(QuanLyBomb, deltaTime);
        CapNhapPlayer(a);

        // Cập nhật enemy
        for (auto enemy : enemies) {
            enemy->capNhat(window);
        }

        //----------------------------------------------VẼ--------------------------------
        window.clear();

        // Vẽ bản đồ (nền, tường, cây, cỏ...)
        map.ve(window);

        // Vẽ bomb
        for (int i = 0; i < QuanLyBomb.size(); i++) {
            QuanLyBomb[i].Ve(window);
        }

        // Vẽ enemy
        for (auto enemy : enemies) {
            enemy->ve(window);
        }

        // Vẽ người chơi
        a.Ve(window, Time);

        // Vẽ điểm
        diem.draw(window);

        window.display();
    }

    // Giải phóng bộ nhớ enemy
    for (auto enemy : enemies) {
        delete enemy;
    }
    enemies.clear();

    return 0;
}
