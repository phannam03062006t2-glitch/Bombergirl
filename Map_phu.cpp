#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Map_phu.h"
#include "Enemy.h"

using namespace std;
using namespace sf;

// ===================
// Bi?n toàn c?c
// ===================
vector<Wall> QuanLyWall;
vector<Wall2> QuanLyWall2;

Texture Wall::TEXTURE;
Texture Wall2::TEXTURE;

// ===================
// L?p Wall
// ===================
Wall::Wall(float X, float Y) {
    x = X;
    y = Y;
    c1 = x;
    c2 = y;
    c3 = x + 64;
    c4 = y + 64;

    if (!TEXTURE.loadFromFile("assets/wall.png")) {
        cerr << "[LOI] Khong the tai anh: assets/wall.png" << endl;
        throw runtime_error("Khong the tai texture wall.png");
    }

    SPRITE.setTexture(TEXTURE);
    SPRITE.setPosition(x, y);
}

void Wall::Ve(RenderWindow &window) {
    window.draw(SPRITE);
}

// ===================
// L?p Wall2
// ===================
Wall2::Wall2(float x, float y) : Wall(x, y) {
    if (!TEXTURE.loadFromFile("assets/wall2.png")) {
        cerr << "[LOI] Khong the tai anh: assets/wall2.png" << endl;
        throw runtime_error("Khong the tai texture wall2.png");
    }
    SPRITE.setTexture(TEXTURE);
}

// ===================
// Ð?c b?n d? t? file
// ===================
void input_map() {
    ifstream file("map.txt");
    if (!file.is_open()) {
        cerr << "[LOI] Khong the mo file map.txt" << endl;
        throw runtime_error("Khong the mo file map.txt");
    }

    int hang = 0, cot = 0;
    if (!(file >> hang >> cot)) {
        cerr << "[LOI] File map.txt khong có du lieu kich thuoc hop le." << endl;
        throw runtime_error("Thieu thông tin hang và cot trong file map.txt");
    }

    if (hang <= 0 || cot <= 0 || hang > 1000 || cot > 1000) {
        cerr << "[LOI] Kich thuoc ban do khong hop le: " << hang << "x" << cot << endl;
        throw runtime_error("Kich thuoc ban do khong hop le.");
    }

    int a;
    int i = 0, j = 0;
    int count = 0;
    while (file >> a) {
        if (a < 0 || a > 5) {
            cerr << "[CANH BAO] Gia tri khong hop le tai (" << i << "," << j << "): " << a << endl;
            continue; // b? qua giá tr? sai
        }

        if (a == 1) QuanLyWall.push_back(Wall(j * 64, i * 64));
        else if (a == 2) QuanLyWall2.push_back(Wall2(j * 64, i * 64));
        else if (a == 3) DanhSachEnemy1.push_back(Enemy1(j * 64, i * 64));
        else if (a == 4) DanhSachEnemy2.push_back(Enemy2(j * 64, i * 64));
        else if (a == 5) DanhSachEnemy3.push_back(Enemy3(j * 64, i * 64));

        j++;
        if (j == cot) {
            j = 0;
            i++;
        }
        count++;
    }

    if (count < hang * cot) {
        cerr << "[CANH BAO] File map.txt thieu du lieu, chi doc duoc " << count 
             << " o thay vi " << (hang * cot) << endl;
    } else if (count > hang * cot) {
        cerr << "[CANH BAO] File map.txt thua du lieu, co " << count 
             << " o thay vi " << (hang * cot) << endl;
    }

    file.close();
    cout << "[INFO] Ða nap ban do thanh cong: " << hang << "x" << cot << endl;
}

// ===================
// V? tu?ng
// ===================
void veWall(RenderWindow &window) {
    for (auto &wall : QuanLyWall)
        wall.Ve(window);

    for (auto &wall2 : QuanLyWall2)
        wall2.Ve(window);
}

