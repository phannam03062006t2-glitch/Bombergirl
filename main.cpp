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
	
	while(window.isOpen()){
		
	deltaTime = clock.restart().asSeconds();
		
	Event event;
	while(window.pollEvent(event))
	{
		if(event.type == Event::Closed){window.close();}
	}
   	//--------------------------------------------Cap nhap------------------------------
   	CapNhapBomb(QuanLyBomb, deltaTime);
   	CapNhapPlayer(a);
   	
   	//----------------------------------------------Ve--------------------------------
   	
   	if(a.alive == false){return 0;}
   	
   	window.clear();
   	
   	a.Ve(window);
   	
   	for(int i = 0; i < QuanLyBomb.size(); i++)
   	{
   		QuanLyBomb[i].Ve(window);
    }

   	
   	window.display();
   }
   return 0;
}
