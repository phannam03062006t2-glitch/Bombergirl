#include <SFML/Graphics.hpp>
#include <iostream>
#include <bits/stdc++.h>
#include "Map.h"
using namespace std;
using namespace sf;

vector<Wall> QuanLyWall;
vector<Wall2> QuanLyWall2;
Texture Wall::TEXTURE;
Texture Wall2::TEXTURE;

Wall::Wall(float X, float Y){
	x = X;
	y = Y;
	TEXTURE.loadFromFile("assets/wall.png");
	SPRITE.setTexture(TEXTURE);
	SPRITE.setPosition(x, y);
}

void Wall::Ve(RenderWindow &window){
	window.draw(SPRITE);
}

void input_map(){
	ifstream file;
	file.open("map.txt");
	int a;
	int hang, cot;
	file >> hang >> cot;
	int i = 0, j = 0;
	while(file >> a){

		if(a == 1){QuanLyWall.push_back(Wall(j*64, i*64));}
		else if(a == 2){QuanLyWall2.push_back(Wall2(j*64, i*64));}
		
		j++;
		if(j == cot){
		    j = 0;
			i++;	
		}
	}
	
	file.close();
}

void veWall(RenderWindow &window){
	for (auto &wall : QuanLyWall)
            wall.Ve(window);
            
    for (auto &wall2 : QuanLyWall2)
            wall2.Ve(window);
}








