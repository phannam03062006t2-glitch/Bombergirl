#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Enemy {
	int frame;
	Clock frameClock;
	int huong; // 0=xuong,1=trai,2=phai,3=len
public:
    static Texture TEXTURE;
    Sprite SPRITE;
    float x, y;           // toa do?
    float c1, c2, c3, c4; // vùng va cham
    Vector2f vanToc;
    float tocDo;
    bool alive;

    Clock doiHuongClock;

    Enemy(float x, float y);
    void datHuongNgauNhien();
    void capNhat(RenderWindow &window);
    void Ve(RenderWindow &window);
    bool kiemTraVaChamBom(const FloatRect& bomNo);
    bool kiemTraVaChamPlayer(const FloatRect& playerBounds);
};

extern vector<Enemy> DanhSachEnemy;

#endif

