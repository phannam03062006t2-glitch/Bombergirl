#ifndef MAP_PHU_H
#define MAP_PHU_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <stdexcept> // th�m d? d�ng exception
using namespace std;
using namespace sf;

class Wall {
public:
    float x, y;
    float c1, c2, c3, c4;
    static Texture TEXTURE;
    Sprite SPRITE;

    Wall(float x, float y);
    void Ve(RenderWindow &window);
};

class Wall2 : public Wall {
public:
    static Texture TEXTURE;
    Wall2(float x, float y);
};

// Bi?n to�n c?c
extern vector<Wall> QuanLyWall;
extern vector<Wall2> QuanLyWall2;

// H�m x? l� b?n d?
void input_map();
void veWall(RenderWindow &window);

#endif

