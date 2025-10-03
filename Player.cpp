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
    
    time = 3.f;                                                 // thời gian đếm ngược đến lúc nổ
    phamVi = 2;                                           // phạm vi vụ nổ
    thoiGianNo = 0.5f;                                           // thời gian vụ nổ xảy ra
    dangNo = false;
	// tạo tọa độ chính giữa ô
    x = a.x / 64;
	y = a.y / 64;
	x = int(x)*64 + 32;
	y = int(y)*64 + 32;
	// tạo vùng va chạm
	c1 = x - 32;
	c2 = y - 32;
	c3 = x + 32;
	c4 = y + 32;
	// set SPRITE
	SPRITE.setPosition(x - 32, y - 32);
}


void Bomb::Ve(RenderWindow &window){
	if(dangNo == true){                                             // nếu đang nổ thì vẽ vụ nổ
	TEXTURE.loadFromFile("assets/no.png");
	SPRITE.setTexture(TEXTURE);
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
	else{                                                        // nếu không nổ thì vẽ bomb
        TEXTURE.loadFromFile("assets/bomb.png");
	    SPRITE.setTexture(TEXTURE);
		window.draw(SPRITE);
	}
}

Player::Player(){
	TEXTURE.loadFromFile("assets/player.png");
	SPRITE.setTexture(TEXTURE);
    SPRITE.setTextureRect(IntRect(0, 0, 62.4,64));
	bombMax = 3;                                                   // số bomb max
	// set vị trí
	x = 32.f;
	y = 32.f;
	// chỉnh vùng va chạm
	c1 = x - 23;
	c2 = y - 26;
	c3 = x + 23;
	c4 = y + 26;
	SPRITE.setPosition(x - 27, y - 32);   
	// hướng lúc đầu
	dx = 0;
	dy = 1;
	// tốc độ
	speed = 3.f;
	// kiểm tra nếu true thì đặt  bomb xong trả về false
	DatBomb = false;
	// để không đặt quá nhiều bomb
    phimX  = false;    
	// kiểm tra out bomb cuối
    out    = true;
	// kiểm tra còn sống
	alive = true;	
}

bool VaCham(const Player& a, const Bomb& b){                            // hàm kiểm tra va chạm bomb với player 
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
	
	if(Keyboard::isKeyPressed(Keyboard::X) && (int)QuanLyBomb.size() < bombMax)                // điều kiện đặt bomb : đã rời bomb cuối 
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
	c1 = x - 23;
	c2 = y - 26;
	c3 = x + 23;
	c4 = y + 26;
}

void Player::Ve(RenderWindow &window, float Time){                          // vẽ player
	if(alive == false){
		SPRITE.setScale(1.f, 1.f);
        SPRITE.setOrigin(0, 0);
        SPRITE.setTextureRect(IntRect(3*62.4, 2*64, 62.4, 64));
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


void CapNhapPlayer(Player &a){
	a.dx = 0;
	a.dy = 0;
	// lấy dữ liệu
    a.Input();
	// lưu vị trí cũ nếu va chạm thì dịch chuyển lại
    float oldX = a.x;
    float oldY = a.y; 
    // đặt bomb
    if(a.DatBomb == true && a.phimX == false){
        Bomb b(a);
        QuanLyBomb.push_back(b);
        a.DatBomb = false;
        a.out = false;
    }
    // di chuyển
    a.Move();
   // nếu có bomb
if((int)QuanLyBomb.size()>0){
	// nếu rời khỏi bomb cuối thì out = true
	if(!VaCham(a, QuanLyBomb[(int)QuanLyBomb.size()-1]))
	{
		a.out = true;
    }
	// kt va chạm
    for (int i = 0; i < (int)QuanLyBomb.size(); ++i) {
    if (i != (int)QuanLyBomb.size() - 1 || a.out == true) {
        bool nowOverlap = VaCham(a, QuanLyBomb[i]);
        if (nowOverlap) {
            a.x = oldX;
            a.y = oldY;
            a.c1 = a.x - 23.0f;
            a.c2 = a.y - 26.0f;
            a.c3 = a.x + 23.0f;
            a.c4 = a.y + 26.0f;
            a.SPRITE.setPosition(a.x - 33.f, a.y - 32.f);
            break;
        }
    }
}
}

   ktCham(a,QuanLyBomb);
}

void CapNhapBomb(vector<Bomb>& QuanLyBomb,const float& deltaTime){
    for (int i = (int)QuanLyBomb.size() - 1; i >= 0; --i) {
        Bomb &b = QuanLyBomb[i];

        if (b.dangNo) {
            b.thoiGianNo -= deltaTime;                             // nếu đang nổ thì trừ thời gian nổ
        } else {
            b.time -= deltaTime;                                // nếu đang chờ nổ thì trừ thời gian đếm ngược
        }

        if (b.time <= 0.0f && !b.dangNo) {
            b.dangNo = true;
            ktCham2(b, QuanLyBomb, i);                                 // kiểm tra nếu nổ lên bomb thì cho thời gian đếm ngược về 0.1  ( gần như nổ luôn)
        }
        
        if (b.dangNo && b.thoiGianNo <= 0.0f) {
            QuanLyBomb.erase(QuanLyBomb.begin() + i);                   // xóa bomb khi xong
            continue; 
        }
    }
}

bool VaChamNo(const Player& a, const Bomb& b){                        // kiểm tra xem người chơi bị nổ không        (kiểm tra 1 bomb)
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

bool VaChamNo2(const Bomb& a, const Bomb& b){                          // kiểm tra bomb nổ bomb không               (kiển tra 1 bomb)
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

bool ktCham(Player &a, vector<Bomb>& QuanLyBomb){                                 // kiểm tra nếu bị nổ thì chết        (kiểm tra tất cả  bomb)
	for(int i = 0; i < (int)QuanLyBomb.size(); i++)
	{   
		if( QuanLyBomb[i].dangNo && VaChamNo(a, QuanLyBomb[i]))
		{
			a.alive = false;
		}
	}
}

bool ktCham2(Bomb &a, vector<Bomb>& QuanLyBomb, int j){                           // kiểm tra bomb nổ bomb               (kiểm tra tất cả bomb)
	for(int i = j + 1; i < (int)QuanLyBomb.size(); i++)
	{   
		if( !QuanLyBomb[i].dangNo && VaChamNo2(a, QuanLyBomb[i]))
		{
			QuanLyBomb[i].time = 0.1f;
		}
	}
}



