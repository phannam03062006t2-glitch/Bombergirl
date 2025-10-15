#ifndef WALL_H
#define WALL_H
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class Wall {
public:
    float x, y;        // Toa do tuong
    static Texture TEXTURE; // Anh dung cho tat ca tuong
    Sprite SPRITE;

    Wall(float x, float y);  // Tao tuong tai toa do
    void Ve(sf::RenderWindow &window);
};

class Wall2 : public Wall {
public:
    static Texture TEXTURE; Anh rieng dung cho Wall2
    Wall2(float x, float y);
};

#endif

