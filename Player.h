#include <bits/stdc++.h>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Player;
extern bool BombLoad ;

class Bomb{
	public:
	    static Texture TEXTURE;
		Sprite SPRITE;
		float x, y;
		float c1, c2, c3, c4;
		float time;
		float thoiGianNo;
		bool dangNo;
	Bomb(const Player& a);
	    void Ve(RenderWindow &window);
	    void VeBombNo(RenderWindow &window);
};

extern vector<Bomb> QuanLyBomb;

class Player{
	public:
		Texture TEXTURE;
		Sprite SPRITE;
		float x, y;
		float c1, c2, c3, c4;
		float dx, dy;
		float speed;
		bool DatBomb;
		bool phimX;
		bool out;                                 // kt nv out bomb cuoi ch
		bool cham;
		int bombMax;
		bool alive;
	Player();
	   void Move();
	   void Input();
	   void Ve(RenderWindow &window);
};

bool VaCham(const Player& a, const Bomb& b);
bool KiemTraTrung(vector<Bomb>& QuanLyBomb, Player a);
void CapNhapPlayer(Player &a);
void CapNhapBomb(vector<Bomb>& QuanLyBomb,const float& deltaTime);
bool VaChamNo(const Player& a, const Bomb& b);
bool ktCham(Player &a, vector<Bomb>& QuanLyBomb);






