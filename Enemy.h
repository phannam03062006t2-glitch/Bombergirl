#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
using namespace sf;
using namespace std;

class Enemy {
    int frame;
    Clock frameClock;
    int huong; // 0=xuong, 1=trai, 2=phai, 3=len

public:
    static Texture TEXTURES[3]; // 3 hình khác nhau
    Sprite SPRITE;
    float x, y;
    float c1, c2, c3, c4;
    Vector2f vanToc;
    float tocDo;
    bool alive;
    int loai; // loai enemy (0,1,2)

    Clock doiHuongClock;

    Enemy(float x, float y, int loai);
    void datHuongNgauNhien();
    void capNhat(RenderWindow &window);
    void Ve(RenderWindow &window);
    bool kiemTraVaChamBom(const FloatRect &bomNo);
    bool kiemTraVaChamPlayer(const FloatRect &playerBounds);
};

extern vector<Enemy> DanhSachEnemy;

#endif
