#include "Wall.h"
#include <iostream>

Wall::Wall() : position(0, 0), loai(0), ton_tai(true) {}

Wall::Wall(sf::Vector2f pos, int loai, const std::string& duong_dan_anh)
    : position(pos), loai(loai), ton_tai(true)
{
    if (!texture.loadFromFile(duong_dan_anh)) {
        std::cout << "Không load được ảnh: " << duong_dan_anh << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(64.f / texture.getSize().x, 64.f / texture.getSize().y);
}

void Wall::ve(sf::RenderWindow& window) {
    if (ton_tai) {
        window.draw(sprite);
    }
}

sf::FloatRect Wall::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Wall::coTheDiQua() const {
    if (!ton_tai) return true;
    return (loai == 0); // nền đi qua được
}

bool Wall::coThePha() const {
    return (ton_tai && loai == 1); // tường mềm
}

bool Wall::tonTai() const {
    return ton_tai;
}

void Wall::pha() {
    ton_tai = false;
}

int Wall::getLoai() const {
    return loai;
}

