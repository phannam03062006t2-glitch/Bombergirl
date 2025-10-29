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
#include "HelpText.h"
using namespace std;
using namespace sf;

extern Diem diemGame;
extern HuongDan huongDan;
Player a;

// ===== KHAI BAO HAM HO TRO =====
void NapLaiTexture(Player &a);
void NapLaiTextureThanhMau(ThanhMau &thanhMau);
bool XuLyKetThucTran(RenderWindow &window, Menu &menu, QLAmThanh &amThanh, Player &a, ThanhMau &thanhMau, Clock &clock, float &Time);

int main() {
//===========================================================KHOI TAO=============================================================================================================
    RenderWindow window(VideoMode(1700, 900), "Bomber Girl");
    window.setFramerateLimit(60);

    // ===== MENU CHINH =====
    Menu menu;
    bool batDau = menu.hienMenu(window);
    if (!batDau) return 0;
    
    // ==== NHAP TEN NGUOI CHOI ====
	Font font;
	if (!font.loadFromFile("arial.ttf")) {
    	cout << "Khong the tai font arial.ttf!" << endl;
	}
	string ten = nhapTenNguoiChoi(window, font);
	diemGame.setPlayerName(ten);


    srand((unsigned)time(NULL));
    ThanhMau thanhMau(3);

    // ===== CAI DAT GAME =====
    input_map();

    float deltaTime = 0.f;
    Clock clock;
    float Time = 0.f;
    bool paused = false;

    // ===== MAP TEXTURE =====
    Texture TEXTURE;
    TEXTURE.loadFromFile("assets/map.png");
    Sprite SPRITE(TEXTURE);

    // ===== ANH NEN =====
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/anhnen.png")) {
        cout << "Khong the tai anhnen.png!" << endl;
    }
    Sprite backgroundSprite(backgroundTexture);
    Vector2u textureSize = backgroundTexture.getSize();
    backgroundSprite.setScale(1700.f / textureSize.x, 900.f / textureSize.y);

    // ===== AM THANH =====
    amThanh.napAm("datbomb", "sound/datbom.wav");
    amThanh.napAm("no", "sound/no.wav");
    amThanh.phatNhacNen("sound/nhacnen.ogg");

    // =================================================================== VONG LAP GAME ============================================================================================
    while (window.isOpen()) {
        Event event;
        // ============================================================XU LY EVENT ===================================================================================================
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::H) 
        		huongDan.doiTrangThai();
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                paused = true;
                amThanh.tamDungTatCaAmThanh();
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

        // ======================================================================= CAP NHAT GAME =====================================================================================
        deltaTime = clock.restart().asSeconds();
        Time += deltaTime;     
        CapNhapBomb(QuanLyBomb, deltaTime);
        CapNhapPlayer(a);
        thanhMau.capNhat(a.health);
        for (auto &e : DanhSachEnemy) e->capNhat(deltaTime, SoLuongQuai);

        // ===== KIEU DE WIN/LOSE =====
        if (!a.alive) {
            bool tiepTuc = XuLyKetThucTran(window, menu, amThanh, a, thanhMau, clock, Time);
            if (!tiepTuc) break;
        }

        if (SoLuongQuai == 0) {
            bool tiepTuc = XuLyKetThucTran(window, menu, amThanh, a, thanhMau, clock, Time);
            if (!tiepTuc) break;
        }

        // ====================================================================== VE MAN HINH GAME =================================================================================
        window.clear();

        window.draw(backgroundSprite);  // VE ANH NEN TRUOC
        window.draw(SPRITE);            // VE MAP

        for (auto &bomb : QuanLyBomb) bomb.Ve(window);
        a.Ve(window, Time);

        for (auto &Enemy : DanhSachEnemy) Enemy->Ve(window);

        veWall(window);
        diemGame.draw(window);
        thanhMau.ve(window);
        huongDan.ve(window, 0.f);
        window.display();
    }

    return 0;
}

// =============================================================KET THUC MAIN====================================================================================================
// ===== CAC HAM PHU =====
void NapLaiTexture(Player &a) {
    a.TEXTURE.loadFromFile("assets/player.png");
    a.SPRITE.setTexture(a.TEXTURE);
}

bool XuLyKetThucTran(RenderWindow &window, Menu &menu, QLAmThanh &amThanh, Player &a, ThanhMau &thanhMau, Clock &clock, float &Time) {
    amThanh.phatAm("no");
    
    diemGame.save("score.txt");

    bool quayLaiMenu = menu.hienGameOver(window, diemGame.get());

    if (quayLaiMenu) {
        // Dung lai nhac menu
        amThanh.dungTatCaAmThanh();
        bool batDauLai = menu.hienMenu(window);

        if (!batDauLai) {
            window.close();
            return false;  // ThoÃ¡t game
        }

        // === Khoi tao lai game ===
        a = Player();
        NapLaiTexture(a);

        QuanLyBomb.clear();
        DanhSachEnemy.clear();

        input_map();

        thanhMau.reset(3);
        diemGame.reset();

        amThanh.phatNhacNen("sound/nhacnen.ogg");

        Time = 0.f;
        clock.restart();
        return true;  // Choi l?i
    } else {
        window.close();
        return false; // ThoÃ¡t game
    }
}

