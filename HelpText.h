#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class HuongDan {
private:
    Font font;              // Phong chu
    Text vanBan;            // Noi dung huong dan
    RectangleShape nen;     // Nen mo phia duoi
    bool hienThi;           // Co hien hay khong

public:
    HuongDan();                             // Ham khoi tao
    void doiTrangThai();                    // An / hien
    void ve(RenderWindow &cuaSo, float chieuCaoBanDo); // Ve ra man hinh
};

// Khai báo bi?n toàn c?c (s? ðý?c ð?nh ngh?a trong HelpText.cpp)
extern HuongDan huongDan;

