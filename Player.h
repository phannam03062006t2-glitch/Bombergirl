#ifndef PLAYER_H
#define PLAYER_H

#include <bits/stdc++.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Map_phu.h"
#include "QLAmThanh.h"
using namespace std;
using namespace sf;

class Player;
extern bool BombLoad ;

class Bomb{
	public:
	    static Texture TEXTURE;
	    static Texture TEXTURE2;
		Sprite SPRITE;
		float x, y;                                    // t?a d?
		float c1, c2, c3, c4;                        // vùng va ch?m
		float time;                                   // th?i gian d?m ngu?c
		float thoiGianNo;                             // th?i gian v? n? x?y ra
		bool dangNo;                                   // ki?m tra có dang n? không
		int phamVi;                                  // ph?m vi v? n?
	Bomb(const Player& a);
	    void Ve(RenderWindow &window);
};

extern vector<Bomb> QuanLyBomb;

class Player{
	public:
		Texture TEXTURE;
		Sprite SPRITE;
		int health;
		float thoiGianBatTu;
		float x, y;                               // t?a d?
		float kx, ky;
		float c1, c2, c3, c4;                     // vùng va ch?m
		float dx, dy;                             // hu?ng
		float speed;                              // t?c d?
		bool DatBomb;                             // bi?n d? d?t bomb
		bool phimX;                               // tránh d?t nhi?u bomb khi nh?n gi? nút X
		bool out;                                 // kt nv out bomb cuoi ch
		bool cham;
		int bombMax;                               // bomb max d?t du?c
		bool alive;                                // ki?m tra còn s?ng không
	Player();
	   void Move();
	   void Input();
	   void Ve(RenderWindow &window, float Time);
};

extern vector<Bomb> QuanLyBomb;
bool VaCham(const Player& a, const Bomb& b);
bool VaChamWall(const Player& a, const Wall& b);
bool VaChamWall2(const Player& a, const Wall2& b);
void CapNhapPlayer(Player &a);
void CapNhapBomb(vector<Bomb>& QuanLyBomb,const float& deltaTime);
bool VaChamNo(const Player& a, const Bomb& b);
bool VaChamNo2(const Bomb& a, const Bomb& b);
bool ktCham(Player &a, vector<Bomb>& QuanLyBomb);
bool ktCham2(Bomb &a, vector<Bomb>& QuanLyBomb, int j);
bool ktCham3(Bomb &a, vector<Wall2>& QuanLyWall2);




#endif


