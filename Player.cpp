#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
using namespace std;
using namespace sf;

vector<Bomb> QuanLyBomb;
Texture Bomb::TEXTURE;
bool BombLoad = false;

Bomb::Bomb(const Player& a){
	if(!BombLoad){
	TEXTURE.loadFromFile("assets/wall2.png");
	BombLoad = true;
    }
	SPRITE.setTexture(TEXTURE);
    
    time = 3.f;
    x = a.x / 32;
	y = a.y / 32;
	x = int(x)*32 + 16;
	y = int(y)*32 + 16;
	c1 = x - 15;
	c2 = y - 15;
	c3 = x + 15;
	c4 = y + 15;
	SPRITE.setPosition(x - 16, y - 16);
}

void Bomb::No() { }


void Bomb::Ve(RenderWindow &window){
	window.draw(SPRITE);
}

Player::Player(){
	TEXTURE.loadFromFile("assets/wall.png");
	SPRITE.setTexture(TEXTURE);
	bombMax = 3;
	x = 16.f;
	y = 16.f;
	c1 = x - 15;
	c2 = y - 15;
	c3 = x + 15;
	c4 = y + 15;
	SPRITE.setPosition(x - 16.5, y - 16.5);               // nho tru di de hop vi tri
	dx = 0;
	dy = 1;
	speed = 3.f;	
}

bool VaCham(const Player& a, const Bomb& b){
	if(a.c1 >= b.c3)return false;
	if(a.c3 <= b.c1)return false;
	if(a.c2 >= b.c4)return false;
	if(a.c4 <= b.c2)return false;
	return true;
}

void Player::Input(){
	if(Keyboard::isKeyPressed(Keyboard::Up)){dx = 0; dy = -1;}
	else if(Keyboard::isKeyPressed(Keyboard::Left)){dx = -1; dy = 0;}
	else if(Keyboard::isKeyPressed(Keyboard::Down)){dx = 0; dy = 1;}
	else if(Keyboard::isKeyPressed(Keyboard::Right)){dx = 1; dy = 0;}
	
	 int slb = QuanLyBomb.size();
	if(Keyboard::isKeyPressed(Keyboard::X) && !KiemTraTrung(QuanLyBomb, *this) && slb < bombMax) 
	   {  
	                 if(!phimX) { 
                          DatBomb = true;
                         phimX = true;
                   }
	    
       }
	
	else{
	   	phimX = false;
	   }
}

void Player::Move(){
	x += dx*speed;
	y += dy*speed;
	SPRITE.setPosition(x - 16, y-16);
	c1 = x - 15;
	c2 = y - 15;
	c3 = x + 15;
	c4 = y + 15;
}

void Player::Ve(RenderWindow &window){
	window.draw(SPRITE);
}

void CapNhapPlayer(Player &a){
    a.Input();
    float oldX = a.x;
    float oldY = a.y; 
    
    if(a.DatBomb == true && a.phimX == false){
        Bomb b(a);
        QuanLyBomb.push_back(b);
        a.DatBomb = false;
        a.out = false;
    }

    
    a.Move();
   int slb = QuanLyBomb.size();
   
if(slb>0){
	if(!VaCham(a, QuanLyBomb[slb-1]))
	{
		a.out = true;
	}
	
    for(int i = 0; i < slb; ++i){
        if(i != slb - 1 || a.out == true){
                bool nowOverlap = VaCham(a, QuanLyBomb[i]);
                if(nowOverlap){
                a.x = oldX;
                a.y = oldY;
                a.c1 = a.x - 15.0f;
                a.c2 = a.y - 15.0f;
                a.c3 = a.x + 15.0f;
                a.c4 = a.y + 15.0f;
               a.SPRITE.setPosition(a.x - 16.f, a.y - 16.f);
               break;
               }
        }
    }
}
    a.dx = 0;
    a.dy = 0;
}

bool KiemTraTrung(vector<Bomb>& QuanLyBomb, Player a){                 // kt xem c� tr�ng bomb ko
	int x = a.x / 32;
	int y = a.y / 32;
	x = x*32 + 16;
	y = y*32 + 16;
	
	int slb = QuanLyBomb.size();
	
	for(int i = 0 ; i < slb ; i++)
	{
		if(x == QuanLyBomb[i].x && y == QuanLyBomb[i].y){return true;}
    }
    return false;
}

void CapNhapBomb(vector<Bomb>& QuanLyBomb,float deltaTime){
	
	int slb = QuanLyBomb.size();
	
	for(int i = slb - 1 ; i >= 0 ; i--)
	{
	     QuanLyBomb[i].time -= deltaTime;
	     if(QuanLyBomb[i].time <= 0)
	     {
	 	        QuanLyBomb.erase(QuanLyBomb.begin() + i);
	 	        
	     }
    }
}













