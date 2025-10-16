#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Map_phu.h"
using namespace std;
using namespace sf;

vector<Bomb> QuanLyBomb;
Texture Bomb::TEXTURE;
Texture Bomb::TEXTURE2;

Bomb::Bomb(const Player& a){

	TEXTURE.loadFromFile("assets/cherrybomb.png");
	TEXTURE2.loadFromFile("assets/no.png");
	SPRITE.setTexture(TEXTURE);
    
    time = 3.f;                                                 // th?i gian d?m ngu?c d?n lúc n?
    phamVi = 1;                                           // ph?m vi v? n?
    thoiGianNo = 0.5f;                                           // th?i gian v? n? x?y ra
    dangNo = false;
	// t?o t?a d? chính gi?a ô
    x = a.x / 64;
	y = a.y / 64;
	x = int(x)*64 + 32;
	y = int(y)*64 + 32;
	// t?o vùng va ch?m
	c1 = x - 32;
	c2 = y - 32;
	c3 = x + 32;
	c4 = y + 32;
	// set SPRITE
	SPRITE.setPosition(x - 32, y - 32);
}


void Bomb::Ve(RenderWindow &window){
	if(dangNo == true){                                             // n?u dang n? thì v? v? n?
	SPRITE.setTexture(TEXTURE2);
	SPRITE.setTextureRect(IntRect(3, 3, 60, 60));
	SPRITE.setPosition(x - 32, y - 32);
	window.draw(SPRITE);
	for(int i = 1; i <= phamVi; i++){
	SPRITE.setPosition(x - 32 - 64*i, y - 32);
	window.draw(SPRITE);
    }
    for(int i = 1; i <= phamVi; i++){
	SPRITE.setPosition(x - 32 + 64*i, y - 32);
	window.draw(SPRITE);
    }
	for(int i = 1; i <= phamVi; i++){
	SPRITE.setPosition(x - 32, y - 32 + 64*i);
	window.draw(SPRITE);
    }
	for(int i = 1; i <= phamVi; i++){
	SPRITE.setPosition(x - 32, y - 32 - 64*i);
	window.draw(SPRITE);
    }
	}
	else{                                                        // n?u không n? thì v? bomb
        TEXTURE.loadFromFile("assets/cherrybomb.png");
        if(time >= 2.5f){ SPRITE.setTextureRect(IntRect(8, 5, 48, 53));}
        else if(time >= 2.0f){SPRITE.setTextureRect(IntRect(60, 5, 51, 53));}
          else if(time >= 1.5f){SPRITE.setTextureRect(IntRect(115, 5, 67, 53));}
            else {SPRITE.setTextureRect(IntRect(187, 5, 66, 53));}
	    SPRITE.setTexture(TEXTURE);
	    SPRITE.setPosition(x-30, y-32);
		window.draw(SPRITE);
	}
}

Player::Player(){
	TEXTURE.loadFromFile("assets/player.png");
	SPRITE.setTexture(TEXTURE);
    SPRITE.setTextureRect(IntRect(0, 0, 62.4,64));
	bombMax = 3;     
	health = 3;                                              // s? bomb max
	thoiGianBatTu = 0.f;
	// set v? trí
	x = 32.f + 64;
	y = 32.f + 64;
	// ch?nh vùng va ch?m
	kx = 20;
	ky = 26;
	c1 = x - kx;
	c2 = y - ky;
	c3 = x + kx - 10;
	c4 = y + ky;
	SPRITE.setPosition(x - 27, y - 32);   
	// hu?ng lúc d?u
	dx = 0;
	dy = 1;
	// t?c d?
	speed = 3.f;
	// ki?m tra n?u true thì d?t  bomb xong tr? v? false
	DatBomb = false;
	// d? không d?t quá nhi?u bomb
    phimX  = false;    
	// ki?m tra out bomb cu?i
    out    = true;
	// ki?m tra còn s?ng
	alive = true;	
}

bool VaCham(const Player& a, const Bomb& b){                            // hàm ki?m tra va ch?m bomb v?i player 
	if(a.c1 >= b.c3)return false;
	if(a.c3 <= b.c1)return false;
	if(a.c2 >= b.c4)return false;
	if(a.c4 <= b.c2)return false;
	return true;
}
bool VaChamWall(const Player& a, const Wall& b){                            // hàm ki?m tra va ch?m bomb v?i player 
	if(a.c1 >= b.c3)return false;
	if(a.c3 <= b.c1)return false;
	if(a.c2 >= b.c4)return false;
	if(a.c4 <= b.c2)return false;
	return true;
}
bool VaChamWall2(const Player& a, const Wall2& b){                            // hàm ki?m tra va ch?m bomb v?i player 
	if(a.c1 >= b.c3)return false;
	if(a.c3 <= b.c1)return false;
	if(a.c2 >= b.c4)return false;
	if(a.c4 <= b.c2)return false;
	return true;
}

void Player::Input(){
	if(alive == false)return;
	if(Keyboard::isKeyPressed(Keyboard::Up)){dx = 0; dy = -1;}
	else if(Keyboard::isKeyPressed(Keyboard::Left)){dx = -1; dy = 0;}
	else if(Keyboard::isKeyPressed(Keyboard::Down)){dx = 0; dy = 1;}
	else if(Keyboard::isKeyPressed(Keyboard::Right)){dx = 1; dy = 0;}
	
	if(Keyboard::isKeyPressed(Keyboard::X) && (int)QuanLyBomb.size() < bombMax)                // di?u ki?n d?t bomb : dã r?i bomb cu?i 
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
	SPRITE.setPosition(x - 33, y - 32);
	c1 = x - kx;
	c2 = y - ky;
	c3 = x + kx - 10;
	c4 = y + ky;
}

void Player::Ve(RenderWindow &window, float Time){                          // v? player
	if(alive == false){
		SPRITE.setScale(1.f, 1.f);
        SPRITE.setOrigin(0, 0);
        SPRITE.setTextureRect(IntRect(3*62.4, 2*64, 62.4, 64));
	}
	else if(thoiGianBatTu > 0){
		SPRITE.setScale(1.f, 1.f);
        SPRITE.setOrigin(0, 0);
        SPRITE.setTextureRect(IntRect(9*62.4, 3*64, 62.4, 64));
	}
    else if (dy == 1) {
        SPRITE.setScale(1.f, 1.f);
        SPRITE.setOrigin(0, 0); 
        SPRITE.setTextureRect(IntRect(0 + (int)(Time*5) % 3 * 62.4, 0, 62.4, 64));
    }
    else if (dy == -1) {
        SPRITE.setScale(1.f, 1.f);
        SPRITE.setOrigin(0, 0);
        SPRITE.setTextureRect(IntRect(62.4 * 3 + (int)(Time*5) % 3 * 62.4, 0, 62.4, 64));
    }
    else if (dx == -1) {
        SPRITE.setScale(1.f, 1.f);
        SPRITE.setOrigin(0, 0);
        SPRITE.setTextureRect(IntRect(62.4 * 6 + (int)(Time*5) % 3 * 62.4, 0, 62.4, 64));
    }
    else if (dx == 1) {
        SPRITE.setScale(-1.f, 1.f);
        SPRITE.setOrigin(SPRITE.getLocalBounds().width, 0); 
        SPRITE.setTextureRect(IntRect(62.4 * 6 + (int)(Time*5) % 3 * 62.4, 0, 62.4, 64));
    }
    window.draw(SPRITE);
}

bool KiemTraChan(Player& a){
    bool kt_Chan = false;

    if (!QuanLyBomb.empty()) {
        // N?u r?i kh?i bomb cu?i cùng thì out = true
        if (!VaCham(a, QuanLyBomb.back())) {
            a.out = true;
        }

        // Ki?m tra va ch?m v?i bomb
        for (int i = 0; i < (int)QuanLyBomb.size(); ++i) {
            if (i != (int)QuanLyBomb.size() - 1 || a.out == true) {
                if (VaCham(a, QuanLyBomb[i])) {
                    kt_Chan = true;
                    break;
                }
            }
        }
    }

    // Ki?m tra va ch?m v?i Wall
    if (!kt_Chan) {
        for (int i = 0; i < (int)QuanLyWall.size(); ++i) {
            if (VaChamWall(a, QuanLyWall[i])) {
                kt_Chan = true;
                break;
            }
        }
    }

    // Ki?m tra va ch?m v?i Wall2
    if (!kt_Chan) {
        for (int i = 0; i < (int)QuanLyWall2.size(); ++i) {
            if (VaChamWall2(a, QuanLyWall2[i])) {
                kt_Chan = true;
                break;
            }
        }
    }

    return kt_Chan;
}


void CapNhapPlayer(Player &a){
	a.thoiGianBatTu -= 1.00/60;
	a.dx = 0;
	a.dy = 0;
	// l?y d? li?u
    a.Input();
	// luu v? trí cu n?u va ch?m thì d?ch chuy?n l?i
    float oldX = a.x;
    float oldY = a.y; 
    // d?t bomb
    if(a.DatBomb == true && a.phimX == false){
        Bomb b(a);
        amThanh.phatAm("datbomb");
        QuanLyBomb.push_back(b);
        a.DatBomb = false;
        a.out = false;
    }
    // di chuy?n
    a.Move();
   // n?u có bomb
   if(KiemTraChan(a))
			{
			a.x = oldX;
            a.y = oldY;
			a.c1 = a.x - a.kx;
            a.c2 = a.y - a.ky;
            a.c3 = a.x + a.kx - 10;
            a.c4 = a.y + a.ky;
             a.SPRITE.setPosition(a.x - 33.f, a.y - 32.f);
			}
   ktCham(a,QuanLyBomb);
}

bool ktCham3(Bomb &a, vector<Wall2>& QuanLyWall2);

void CapNhapBomb(vector<Bomb>& QuanLyBomb,const float& deltaTime){
    for (int i = (int)QuanLyBomb.size() - 1; i >= 0; --i) {
        Bomb &b = QuanLyBomb[i];

        if (b.dangNo) {
            b.thoiGianNo -= deltaTime;                             // n?u dang n? thì tr? th?i gian n?
        } else {
            b.time -= deltaTime;                                // n?u dang ch? n? thì tr? th?i gian d?m ngu?c
        }

        if (b.time <= 0.0f && !b.dangNo) {
        	amThanh.phatAm("no");
            b.dangNo = true;
            ktCham2(b, QuanLyBomb, i);                                 // ki?m tra n?u n? lên bomb thì cho th?i gian d?m ngu?c v? 0.1  ( g?n nhu n? luôn)
             ktCham3(b, QuanLyWall2);
        }
        
        if (b.dangNo && b.thoiGianNo <= 0.0f) {
            QuanLyBomb.erase(QuanLyBomb.begin() + i);                   // xóa bomb khi xong
            continue; 
        }
    }
}

bool VaChamNo(const Player& a, const Bomb& b){                        // ki?m tra xem ngu?i choi b? n? không        (ki?m tra 1 bomb)
	if(a.c1 >= b.c3 + 64*b.phamVi)return false;
	if(a.c3 <= b.c1 - 64*b.phamVi)return false;
	if(a.c2 >= b.c4 + 64*b.phamVi)return false;
	if(a.c4 <= b.c2 - 64*b.phamVi)return false;
	if(a.c3 <= b.c1 && a.c4 <= b.c2)return false;
	if(a.c1 >= b.c3 && a.c4 <= b.c2)return false;
	if(a.c2 >= b.c4 && a.c1 >= b.c3)return false;
	if(a.c2 >= b.c4 && a.c3 <= b.c1)return false;
	return true;
}

bool VaChamNo2(const Bomb& a, const Bomb& b){                          // ki?m tra bomb n? bomb không               (ki?n tra 1 bomb)
	if(a.c1 >= b.c3 + 64*b.phamVi)return false;
	if(a.c3 <= b.c1 - 64*b.phamVi)return false;
	if(a.c2 >= b.c4 + 64*b.phamVi)return false;
	if(a.c4 <= b.c2 - 64*b.phamVi)return false;
	if(a.c3 <= b.c1 && a.c4 <= b.c2)return false;
	if(a.c1 >= b.c3 && a.c4 <= b.c2)return false;
	if(a.c2 >= b.c4 && a.c1 >= b.c3)return false;
	if(a.c2 >= b.c4 && a.c3 <= b.c1)return false;
	return true;
}

bool VaChamNo3(const Bomb& b, const Wall2& a){                          // ki?m tra bomb n? bomb không               (ki?n tra 1 bomb)
	if(a.c1 >= b.c3 + 64*b.phamVi)return false;
	if(a.c3 <= b.c1 - 64*b.phamVi)return false;
	if(a.c2 >= b.c4 + 64*b.phamVi)return false;
	if(a.c4 <= b.c2 - 64*b.phamVi)return false;
	if(a.c3 <= b.c1 && a.c4 <= b.c2)return false;
	if(a.c1 >= b.c3 && a.c4 <= b.c2)return false;
	if(a.c2 >= b.c4 && a.c1 >= b.c3)return false;
	if(a.c2 >= b.c4 && a.c3 <= b.c1)return false;
	return true;
}

bool ktCham(Player &a, vector<Bomb>& QuanLyBomb){                                 // ki?m tra n?u b? n? thì ch?t        (ki?m tra t?t c?  bomb)
	for(int i = 0; i < (int)QuanLyBomb.size(); i++)
	{   
		if( QuanLyBomb[i].dangNo && VaChamNo(a, QuanLyBomb[i]))
		{   
		    if(a.thoiGianBatTu <= 0){a.health--;a.thoiGianBatTu = 3.f;}
		    if(a.health == 0){
			a.alive = false;
		    }
		}
	}
}

bool ktCham2(Bomb &a, vector<Bomb>& QuanLyBomb, int j){                           // ki?m tra bomb n? bomb               (ki?m tra t?t c? bomb)
	for(int i = j + 1; i < (int)QuanLyBomb.size(); i++)
	{   
		if( !QuanLyBomb[i].dangNo && VaChamNo2(a, QuanLyBomb[i]))
		{
			QuanLyBomb[i].time = 0.1f;
		}
	}
}

bool ktCham3(Bomb &a, vector<Wall2>& QuanLyWall2){                           // ki?m tra bomb n? bomb               (ki?m tra t?t c? bomb)
	for(int i = 0; i < (int)QuanLyWall2.size(); i++)
	{   
		if(VaChamNo3(a, QuanLyWall2[i]))
		{
			QuanLyWall2.erase(QuanLyWall2.begin() + i); 
			i--;  
		}
	}
}







