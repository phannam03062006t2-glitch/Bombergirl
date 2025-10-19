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

extern Diem diemGame;
Player a;

// ===== KHAI BAO HAM HO TRO =====
void NapLaiTexture(Player &a);
void NapLaiTextureThanhMau(ThanhMau &thanhMau);

int main() {
    RenderWindow window(VideoMode(1700, 900), "Bomber Girl");
    window.setFramerateLimit(60);

    // ===== MENU CHINH =====
    Menu menu;
    bool batDau = menu.hienMenu(window);
    if (!batDau) return 0;

    srand((unsigned)time(NULL));
    ThanhMau thanhMau(3);

    // ===== CAI DAT GAME =====
    input_map();

    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;
    bool paused = false;

    Texture TEXTURE;
    TEXTURE.loadFromFile("assets/map.png");
    Sprite SPRITE(TEXTURE);

    // ===== AM THANH =====
    amThanh.napAm("datbomb", "sound/datbom.wav");
    amThanh.napAm("no", "sound/no.wav");
    amThanh.phatNhacNen("sound/nhacnen.ogg");

    // ===== VONG LAP GAME =====
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Nhan ESC de tam dung
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                paused = true;
				amThanh.dungTatCaAmThanh();
                // Ve khung tam dung
                window.clear();
                window.draw(SPRITE);
                for (auto &bomb : QuanLyBomb) bomb.Ve(window);
                a.Ve(window, Time);
                for (auto &Enemy : DanhSachEnemy) Enemy->Ve(window);
                veWall(window);
                diemGame.draw(window);
                thanhMau.ve(window);
                window.display();

                // Hien menu tam dung
                int luaChon = menu.hienPause(window);
                if (luaChon == 0) {
                    paused = false;
                    clock.restart();
                    amThanh.tiepTucTatCaAmThanh();
                } else if (luaChon == 1) {
                    window.close();
                    return 0;
                }
            }
        }

        if (paused) continue;

        // Cap nhat thoi gian
        deltaTime = clock.restart().asSeconds();
        Time += deltaTime;

        // ===== CAP NHAT GAME =====
        CapNhapBomb(QuanLyBomb, deltaTime);
        CapNhapPlayer(a);
        thanhMau.capNhat(a.health);

        for (auto &e : DanhSachEnemy) e->capNhat(deltaTime);

        // ===== NEU NHAN VAT CHET =====
        if (!a.alive) {
            amThanh.phatAm("no");
            diemGame.save("score.txt");

            // Hien man hinh Game Over
            bool quayLaiMenu = menu.hienGameOver(window, diemGame.get());

            if (quayLaiMenu) {
                // Dung nhac, mo lai menu
                amThanh.dungTatCaAmThanh();
                bool batDauLai = menu.hienMenu(window);
                if (!batDauLai) {
                    window.close();
                    break;
                }

                // === Khoi tao lai game ===
                a = Player();
                NapLaiTexture(a);

                QuanLyBomb.clear();
                DanhSachEnemy.clear();

                input_map();

                thanhMau.reset(3);
                
                diemGame.reset();

                amThanh.phatNhacNen("sound/nhacnen.ogg"); // Phat lai nhac nen

                Time = 0.f;
                clock.restart();
                continue;
            } else {
                window.close();
                break;
            }
        }

        // ===== VE MAN HINH GAME =====
        window.clear();
        window.draw(SPRITE);

        for (auto &bomb : QuanLyBomb) bomb.Ve(window);
        a.Ve(window, Time);

        for (auto &Enemy : DanhSachEnemy) Enemy->Ve(window);

        veWall(window);
        diemGame.draw(window);
        thanhMau.ve(window);

        window.display();
    }

    return 0;
}

// ===== CAC HAM PHU =====
void NapLaiTexture(Player &a) {
    a.TEXTURE.loadFromFile("assets/player.png");
    a.SPRITE.setTexture(a.TEXTURE);
}

