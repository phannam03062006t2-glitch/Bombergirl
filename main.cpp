#include <SFML/Graphics.hpp>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include "Player.h"
#include "Map.h"
#include "Diem.h"

using namespace std;
using namespace sf;


int main(){
	// khoi tao cua so
    RenderWindow window(VideoMode(1700, 900), "my game");
	window.setFramerateLimit(60);
	// khai bao
	Player a;
	//
	float deltaTime = 0.f;             // thời gian mỗi vòng while
	Clock clock;
	float Time  = 0.f;                // đếm thời gian từ lúc đầu game
	//map (tạm thời) 64x64
    //Texture TEXTURE;
    //TEXTURE.loadFromFile("assets/map.png");
	//Sprite SPRITE;
	//SPRITE.setTexture(TEXTURE);
	//SPRITE.setPosition(0, 0);
	// Khởi tạo bản đồ
	Map map;
	try {
		map.napFile("map.txt");
	} catch (const exception& e) {
		cerr<< e.what() <<endl;
		return -1;
	}
	//Khởi tạo điểm
	Diem diem;

	// Vòng lặp game
	while(window.isOpen()){
	// cập nhập thời gian
	deltaTime = clock.restart().asSeconds();
	Time += deltaTime;
	// giữ cửa sổ mở
	Event event;
	while(window.pollEvent(event))
	{
		if(event.type == Event::Closed){window.close();}
	}
   	//--------------------------------------------Cap nhap------------------------------
   	CapNhapBomb(QuanLyBomb, deltaTime);
   	CapNhapPlayer(a);
   	
   	//----------------------------------------------Ve--------------------------------
   	// Vẽ
   	window.clear();

	// Vẽ map
	map.ve(window);
   	//window.draw(SPRITE);
	// Vẽ các quả bomb
   	for(int i = 0; i < QuanLyBomb.size(); i++)
   	{
   		QuanLyBomb[i].Ve(window);
    }
   	// Vẽ người chơi
   	a.Ve(window, Time);
   
   	// Vẽ điểm
	diem.draw(window);
   	window.display();
   }
   return 0;
}


