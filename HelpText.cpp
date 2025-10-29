#include "HelpText.h"
#include <iostream>

HuongDan huongDan; // Ä?nh ngh?a bi?n toÃ n c?c

HuongDan::HuongDan() {
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Khong the tai font arial.ttf\n";
    }

    vanBan.setFont(font);
    vanBan.setCharacterSize(22);
    vanBan.setFillColor(Color::White);
    vanBan.setString(
        "LEN XUONG TRAI PHAI  : Phim di chuyen\n"
        "X        	: Dat bom\n"
        "ESC       : Pause game\n"
        "H        	: An / Hien huong dan"
    );
    hienThi = true;
}

void HuongDan::doiTrangThai() {
    hienThi = !hienThi;
}

void HuongDan::ve(RenderWindow &cuaSo, float chieuCaoBanDo) {
    if (!hienThi) return;

    // Kich thuoc khung huong dan 
    float rong = 450.0f;
    float cao = 120.0f;
    float le = 10.0f;

    // Kich thuoc cua so
    float rongCuaSo = cuaSo.getSize().x;
    float caoCuaSo = cuaSo.getSize().y;

    // Vi tri: goc phai-duoi
    float viTriX = le;  // sat mep phai 
    float viTriY = caoCuaSo - cao - le;    // sat day 

    // Nen mo
    nen.setSize(Vector2f(rong, cao));
    nen.setPosition(viTriX, viTriY);
    nen.setFillColor(Color(0, 0, 0, 160));

    // Noi dung chu
    vanBan.setPosition(viTriX + 15.0f, viTriY + 10.0f);

    cuaSo.draw(nen);
    cuaSo.draw(vanBan);
}
