#include "Wall.h"
#include<bits/stdc++.h>
using namespace std;
Wall::Wall(Vector2f vitri, bool pha_duoc, const string& duongdan_anh) {
	co_the_pha=pha_duoc;
	hinh.setSize(Vector2f(32,32));
	hinh.setPosition(vitri);
	
	if(!ket_cau.loadFromFile(duongan_anh)) {
		if(pha_duoc) hinh.setFillColor(Color(139, 69, 19)); //fallback nau
		else hinh.setFillColor(Color(128, 128, 128));       //fallback xam
	} else {
		anh.setTexture(ket_cau);
		anh.setPosition(vitri);
		anh.setScale(32.f/ket_cau.getSize().x, 32.f/ket_cau.getSize().y);
	}
}

void Wall::ve(RenderWindow& cua_so) {
	if (ket_cau.getSize().x>0)
		cua_so.draw(anh);
	else
		cua_so.draw(hinh);
}

FloatRect Wall::layKhung() {
	if (ket_cau.getSize().x > 0) 
        return anh.getGlobalBounds(); // sprite (có texture)
    else 
        return hinh.getGlobalBounds(); // rectangle fallback
}
bool Wall::laPhaDuoc() {return co_the_pha;}
