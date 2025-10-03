#include <SFML/Graphics.hpp>
#include <fstream>
#include <bits/stdc++.h>
#include <iostream>
#include "Player.h"
using namespace std;
using namespace sf;


int main(){
	// khoi tao cua so
    RenderWindow window(VideoMode(1700, 900), "my game");
	window.setFramerateLimit(60);
	// khai bao
	Player a;
	//
	float deltaTime = 0.f;
	Clock clock;
	float Time  = 0.f;
	//map
    Texture TEXTURE;
    TEXTURE.loadFromFile("assets/map.png");
	Sprite SPRITE;
	SPRITE.setTexture(TEXTURE);
	SPRITE.setPosition(0, 0);
	
	while(window.isOpen()){
		
	deltaTime = clock.restart().asSeconds();
	Time += deltaTime;
	
	Event event;
	while(window.pollEvent(event))
	{
		if(event.type == Event::Closed){window.close();}
	}
   	//--------------------------------------------Cap nhap------------------------------
   	CapNhapBomb(QuanLyBomb, deltaTime);
   	CapNhapPlayer(a);
   		
   	if(a.alive == false)
	   {
	   a.x = 32;
	   a.y = 32;
	   a.alive = true;
	   }
   	
   	//----------------------------------------------Ve--------------------------------
   
   	window.clear();
   	window.draw(SPRITE);
   	for(int i = 0; i < QuanLyBomb.size(); i++)
   	{
   		QuanLyBomb[i].Ve(window);
    }
   	
   	a.Ve(window, Time);
   
   	
   	window.display();
   }
   return 0;
}
