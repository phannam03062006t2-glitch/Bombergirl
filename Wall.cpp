#include "Wall.h"
#include <iostream>
using namespace std;

Wall::Wall() {}

Wall::Wall(Vector2f vitri, bool pha_duoc, const string& duongdan_anh, bool di_qua)
    : vitri(vitri), co_the_pha(pha_duoc), di_qua(di_qua)
{
    hinh.setSize(Vector2f(64, 64)); // set kich thuoc cua hinh
    hinh.setPosition(vitri); // set vi tri cua hinh

    if (!ket_cau.loadFromFile(duongdan_anh)) { // neu khong tai duoc anh thi tao mau
        if (pha_duoc) hinh.setFillColor(Color(139, 69, 19)); // mau nau cho tuong pha duoc
        else hinh.setFillColor(Color(128, 128, 128)); // mau xam cho tuong khong pha duoc
    } else {
        anh.setTexture(ket_cau); // set anh cho tuong
        anh.setPosition(vitri); // set vi tri cho anh
        anh.setScale(64.f / ket_cau.getSize().x, 64.f / ket_cau.getSize().y); // dieu chinh ti le cua anh
    }
}

void Wall::ve(RenderWindow& cua_so) {
    if (ket_cau.getSize().x > 0) // neu anh co size hop le thi ve anh
        cua_so.draw(anh);
    else // neu khong co anh thi ve hinh chu nhat
        cua_so.draw(hinh);
}

FloatRect Wall::layKhung() {
    if (ket_cau.getSize().x > 0) // neu anh co size hop le thi tra ve khung cua anh
        return anh.getGlobalBounds();
    else // neu khong co anh thi tra ve khung cua hinh
        return hinh.getGlobalBounds();
}

bool Wall::laPhaDuoc() { return co_the_pha; } // kiem tra xem tuong co the pha duoc khong
bool Wall::coTheDiQua() { return di_qua; } // kiem tra xem tuong co the di qua khong
