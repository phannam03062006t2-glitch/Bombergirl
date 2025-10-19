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
#include "Menu.h"

using namespace std;
using namespace sf;

Player a;

int main() {
    RenderWindow window(VideoMode(1700, 900), "Bomber Girl");
    window.setFramerateLimit(60);

    // ===== MENU CHINH =====
    Menu menu;
    bool batDau = menu.hienMenu(window);
    if (!batDau) return 0;

    srand((unsigned)time(NULL));
    ThanhMau thanhMau(3);

    // ===== GAME SETUP =====
    input_map();

    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;
    bool paused = false;

    Texture TEXTURE;
    TEXTURE.loadFromFile("assets/map.png");
    Sprite SPRITE(TEXTURE);

    amThanh.napAm("datbomb", "sound/datbom.wav");
    amThanh.napAm("no", "sound/no.wav");
    amThanh.phatNhacNen("sound/nhacnen.ogg");

    // ===== GAME LOOP =====
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                // Bat pause
                paused = true;

                // Dung tat ca am thanh
                amThanh.dungTatCaAmThanh();

                // Ve khung hien tai
                window.clear();
                window.draw(SPRITE);
                for (auto &bomb : QuanLyBomb) bomb.Ve(window);
                a.Ve(window, Time);
                for (auto &Enemy : DanhSachEnemy1) Enemy.Ve(window);
                for (auto &Enemy : DanhSachEnemy2) Enemy.Ve(window);
                for (auto &Enemy : DanhSachEnemy3) Enemy.Ve(window);
                veWall(window);
                diemGame.draw(window);
                thanhMau.ve(window);
                window.display();

                // Goi menu pause
                int luaChon = menu.hienPause(window);
                if (luaChon == 0) {
                    paused = false; // Tiep tuc

                    // Reset clock de khong bi nhay thoi gian
                    clock.restart();
                } else if (luaChon == 1) {
                    window.close();
                    return 0;
                }
            }
        }

        if (paused) continue; // Bo qua update khi dang pause

        // Cap nhat thoi gian
        deltaTime = clock.restart().asSeconds();
        Time += deltaTime;

        // ===== CAP NHAT GAME =====
        CapNhapBomb(QuanLyBomb, deltaTime);
        CapNhapPlayer(a);
        thanhMau.capNhat(a.health);

        for (auto &e : DanhSachEnemy1) e.capNhat(deltaTime);
        for (auto &e : DanhSachEnemy2) e.capNhat(deltaTime);
        for (auto &e : DanhSachEnemy3) e.capNhat(deltaTime);

        if (!a.alive) {
    amThanh.phatAm("no");
    diemGame.save("score.txt");

    // T?o c?a s? game over full màn
    window.create(VideoMode(1700, 900), "Game Over", Style::Close);

    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Khong tim thay font!" << endl;
    }

    // ==== Tieu de GAME OVER ====
    Text gameOverText("GAME OVER", font, 120);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setStyle(Text::Bold);
    FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.width / 2, textRect.height / 2);
    gameOverText.setPosition(1700 / 2, 900 / 2 - 200);

    // ==== Diem hien tai ====
    Text diemText("Score: " + to_string(diemGame.get()), font, 70);
    diemText.setFillColor(Color::White);
    FloatRect diemRect = diemText.getLocalBounds();
    diemText.setOrigin(diemRect.width / 2, diemRect.height / 2);
    diemText.setPosition(1700 / 2, 900 / 2);

    // ==== Huong dan nut bam ====
    Text huongDanText("PRESS ENTER TO RETURN TO MENU\nPRESS ESC TO EXIT GAME", font, 45);
    huongDanText.setFillColor(Color::Yellow);
    FloatRect hdRect = huongDanText.getLocalBounds();
    huongDanText.setOrigin(hdRect.width / 2, hdRect.height / 2);
    huongDanText.setPosition(1700 / 2, 900 / 2 + 200);

    bool choLuaChon = true;

    while (choLuaChon && window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) {
                window.close();
                return 0;
            }
            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::Return) {
                    // Quay lai menu (neu menu nam trong main)
                    return main();
                }
                if (e.key.code == Keyboard::Escape) {
                    window.close();
                    return 0;
                }
            }
        }

        window.clear(Color::Black);
        window.draw(gameOverText);
        window.draw(diemText);
        window.draw(huongDanText);
        window.display();
    }

    continue;
}


        // ===== VE GAME =====
        window.clear();
        window.draw(SPRITE);

        for (auto &bomb : QuanLyBomb) bomb.Ve(window);
        a.Ve(window, Time);

        for (auto &Enemy : DanhSachEnemy1) Enemy.Ve(window);
        for (auto &Enemy : DanhSachEnemy2) Enemy.Ve(window);
        for (auto &Enemy : DanhSachEnemy3) Enemy.Ve(window);

        veWall(window);
        diemGame.draw(window);
        thanhMau.ve(window);

        window.display();
    }

    return 0;
}


