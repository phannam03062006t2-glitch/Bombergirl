#include "Wall.h"
#include <bits/stdc++.h>
using namespace std;

Wall::Wall() {}

Wall::Wall(Vector2f vitri, bool pha_duoc, const string& duongdan_anh, bool di_qua)
    : vitri(vitri), co_the_pha(pha_duoc), di_qua(di_qua)
{
    hinh.setSize(Vector2f(64,64));
    hinh.setPosition(vitri);

    if(!ket_cau.loadFromFile(duongdan_anh)) {
        if(pha_duoc) hinh.setFillColor(Color(139, 69, 19)); // fallback: nâu
        else hinh.setFillColor(Color(128, 128, 128));       // fallback: xám
    } else {
        anh.setTexture(ket_cau);
        anh.setPosition(vitri);
        anh.setScale(64.f/ket_cau.getSize().x, 64.f/ket_cau.getSize().y);
    }
}

void Wall::ve(RenderWindow& cua_so) {
    if (ket_cau.getSize().x > 0)
        cua_so.draw(anh);
    else
        cua_so.draw(hinh);
}

FloatRect Wall::layKhung() {
    if (ket_cau.getSize().x > 0)
        return anh.getGlobalBounds();
    else
        return hinh.getGlobalBounds();
}

bool Wall::laPhaDuoc() { return co_the_pha; }
bool Wall::coTheDiQua() { return di_qua; }
