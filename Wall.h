#ifndef WALL_H
#define WALL_H
#include<SFML/Graphics.hpp>
#include<bits/stdc++.h>
using namespace std;
using namespace sf;
class Wall{
	private:
		RectangleShape hinh;
		Sprite anh;
		Texture ket_cau;
		bool co_the_pha;
	public:
		Wall();
		Wall(Vector2f vitri, bool pha_duoc, const string& duongdan_anh);
		void ve(RenderWindow& cua_so);
		FloatRect layKhung();
		bool laPhaDuoc();
};
#endif

