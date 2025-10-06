#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Wall.h"
using namespace std;
using namespace sf;

// ======= LỚP NỀN =======
class Nen {
private:
    RectangleShape hinh;   // Hình chữ nhật nền
    Texture ket_cau;       // Kết cấu ảnh nền
    Sprite anh;            // Sprite hiển thị ảnh nền

public:
    Nen() {}   // Hàm khởi tạo mặc định

    // ======= KHỞI TẠO NỀN =======
    Nen(Vector2f vitri, const string& duongdan_anh) {
        hinh.setSize(Vector2f(64, 64));        // Kích thước 1 ô (64x64)
        hinh.setPosition(vitri);               // Vị trí trên map

        if (!ket_cau.loadFromFile(duongdan_anh)) {
            hinh.setFillColor(Color(120, 200, 120)); // fallback: xanh lá
        } else {
            anh.setTexture(ket_cau);
            anh.setPosition(vitri);
            anh.setScale(64.f / ket_cau.getSize().x, 64.f / ket_cau.getSize().y);
        }
    }

    // ======= HÀM VẼ NỀN =======
    void ve(RenderWindow& cua_so) {
        if (ket_cau.getSize().x > 0)
            cua_so.draw(anh);
        else
            cua_so.draw(hinh);
    }
};

// ======= LỚP BẢN ĐỒ =======
class Map {
private:
    map<pair<int, int>, Nen> ds_nen;     // Danh sách nền (mỗi ô là 1 ảnh)
    map<pair<int, int>, Wall> ds_tuong;  // Danh sách tường, vật thể

public:
    Map();                               // Hàm khởi tạo mặc định
    Map(const string& duong_dan_file);   // Hàm khởi tạo từ file

    // ======= NẠP FILE BẢN ĐỒ =======
    void napFile(const string& duong_dan_file);

    // ======= VẼ TOÀN BỘ BẢN ĐỒ =======
    void ve(RenderWindow& cua_so);
};
