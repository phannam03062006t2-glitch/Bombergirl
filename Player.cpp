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
	TEXTURE.loadFromFile("assets/bomb.png");
	BombLoad = true;
    }
	SPRITE.setTexture(TEXTURE);
    
    time = 3.f;
    thoiGianNo = 0.5f;
    dangNo = false;
    x = a.x / 64;
	y = a.y / 64;
	x = int(x)*64 + 32;
	y = int(y)*64 + 32;
	c1 = x - 32;
	c2 = y - 32;
	c3 = x + 32;
	c4 = y + 32;
	SPRITE.setPosition(x - 32, y - 32);
}


void Bomb::Ve(RenderWindow &window){
	if(dangNo == true){
	TEXTURE.loadFromFile("assets/no.png");
	SPRITE.setTexture(TEXTURE);
	SPRITE.setPosition(x - 32, y - 32);
	window.draw(SPRITE);
	SPRITE.setPosition(x - 32 - 64, y - 32);
	window.draw(SPRITE);
	SPRITE.setPosition(x - 32 + 64, y - 32);
	window.draw(SPRITE);
	SPRITE.setPosition(x - 32, y - 32 + 64);
	window.draw(SPRITE);
	SPRITE.setPosition(x - 32, y - 32 - 64);
	window.draw(SPRITE);
	}
	else{
        TEXTURE.loadFromFile("assets/bomb.png");
	    SPRITE.setTexture(TEXTURE);
		window.draw(SPRITE);
	}
}

Player::Player(){
	TEXTURE.loadFromFile("assets/wall.png");
	SPRITE.setTexture(TEXTURE);
    //SPRITE.setTextureRect(IntRect(40, 40, 128 - 40, 128 -40));
	bombMax = 3;
	x = 32.f;
	y = 32.f;
	c1 = x - 32;
	c2 = y - 32;
	c3 = x + 32;
	c4 = y + 32;
	SPRITE.setPosition(x - 32, y - 32);               
	dx = 0;
	dy = 1;
	speed = 3.f;
	DatBomb = false;
    phimX  = false;    
    out    = true;
	alive = true;	
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
	
	if(Keyboard::isKeyPressed(Keyboard::X) && !KiemTraTrung(QuanLyBomb, *this) && (int)QuanLyBomb.size() < bombMax) 
	   {  
	                 if(!phimX && out == true) { 
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
	SPRITE.setPosition(x - 32, y - 32);
	c1 = x - 32;
	c2 = y - 32;
	c3 = x + 32;
	c4 = y + 32;
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
   
if((int)QuanLyBomb.size()>0){
	if(!VaCham(a, QuanLyBomb[(int)QuanLyBomb.size()-1]))
	{
		a.out = true;
    }
	
    for (int i = 0; i < (int)QuanLyBomb.size(); ++i) {
    if (i != (int)QuanLyBomb.size() - 1 || a.out == true) {
        bool nowOverlap = VaCham(a, QuanLyBomb[i]);
        if (nowOverlap) {
            a.x = oldX;
            a.y = oldY;
            a.c1 = a.x - 32.0f;
            a.c2 = a.y - 32.0f;
            a.c3 = a.x + 32.0f;
            a.c4 = a.y + 32.0f;
            a.SPRITE.setPosition(a.x - 32.f, a.y - 32.f);
            break;
        }
    }
}
}

   ktCham(a,QuanLyBomb);

    a.dx = 0;
    a.dy = 0;
}

bool KiemTraTrung(vector<Bomb>& QuanLyBomb, Player a){                 
	int x = a.x / 64;
	int y = a.y / 64;
	x = x*64 + 32;
	y = y*64 + 32;
	
	
	for(int i = 0 ; i < (int)QuanLyBomb.size() ; i++)
	{
		if(x == QuanLyBomb[i].x && y == QuanLyBomb[i].y){return true;}
    }
    return false;
}

void CapNhapBomb(vector<Bomb>& QuanLyBomb,const float& deltaTime){
    for (int i = (int)QuanLyBomb.size() - 1; i >= 0; --i) {
        Bomb &b = QuanLyBomb[i];

        if (b.dangNo) {
            b.thoiGianNo -= deltaTime;
        } else {
            b.time -= deltaTime;
        }

        if (b.time <= 0.0f && !b.dangNo) {
            b.dangNo = true;
            ktCham2(b, QuanLyBomb, i);
        }
        
        if (b.dangNo && b.thoiGianNo <= 0.0f) {
            QuanLyBomb.erase(QuanLyBomb.begin() + i);
            continue; 
        }
    }
}

bool VaChamNo(const Player& a, const Bomb& b){
	if(a.c1 >= b.c3 + 63)return false;
	if(a.c3 <= b.c1 - 63)return false;
	if(a.c2 >= b.c4 + 63)return false;
	if(a.c4 <= b.c2 - 63)return false;
	if(a.c3 <= b.c1 && a.c4 <= b.c2)return false;
	if(a.c1 >= b.c3 && a.c4 <= b.c2)return false;
	if(a.c2 >= b.c4 && a.c1 >= b.c3)return false;
	if(a.c2 >= b.c4 && a.c3 <= b.c1)return false;
	return true;
}

bool VaChamNo2(const Bomb& a, const Bomb& b){
	if(a.c1 >= b.c3 + 63)return false;
	if(a.c3 <= b.c1 - 63)return false;
	if(a.c2 >= b.c4 + 63)return false;
	if(a.c4 <= b.c2 - 63)return false;
	if(a.c3 <= b.c1 && a.c4 <= b.c2)return false;
	if(a.c1 >= b.c3 && a.c4 <= b.c2)return false;
	if(a.c2 >= b.c4 && a.c1 >= b.c3)return false;
	if(a.c2 >= b.c4 && a.c3 <= b.c1)return false;
	return true;
}

bool ktCham(Player &a, vector<Bomb>& QuanLyBomb){
	for(int i = 0; i < (int)QuanLyBomb.size(); i++)
	{   
		if( QuanLyBomb[i].dangNo && VaChamNo(a, QuanLyBomb[i]))
		{
			a.alive = false;
		}
	}
}

bool ktCham2(Bomb &a, vector<Bomb>& QuanLyBomb, int j){
	for(int i = j + 1; i < (int)QuanLyBomb.size(); i++)
	{   
		if( !QuanLyBomb[i].dangNo && VaChamNo2(a, QuanLyBomb[i]))
		{
			QuanLyBomb[i].time = 0.1f;
		}
	}
}

