#ifndef WALL_H
#define WALL_H
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;
class Wall {
public:
    float x, y;
    static Texture TEXTURE;
    Sprite SPRITE;

    Wall(float x, float y);
    void Ve(sf::RenderWindow &window);
};

class Wall2 : public Wall {
public:
    static sf::Texture TEXTURE;
    Wall2(float x, float y);
};

#endif
