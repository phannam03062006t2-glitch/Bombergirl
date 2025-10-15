#include "Wall.h"
#include <iostream>
using namespace sf;
using namespace std;

Texture Wall::TEXTURE;
Texture Wall2::TEXTURE;

Wall::Wall(float X, float Y) {
    x = X;
    y = Y;
    if (TEXTURE.getSize().x == 0) {
        if (!TEXTURE.loadFromFile("assets/wall.png"))
            cout << "Khong load duoc wall.png\n";
    }
    SPRITE.setTexture(TEXTURE);
    SPRITE.setPosition(x, y);
}

Wall2::Wall2(float X, float Y) : Wall(X, Y) {
    if (TEXTURE.getSize().x == 0) {
        if (!TEXTURE.loadFromFile("assets/wall2.png"))
            cout << "Khong load duoc wall2.png\n";
    }
    SPRITE.setTexture(TEXTURE);
}
void Wall::Ve(RenderWindow &window) {
    window.draw(SPRITE);
}
