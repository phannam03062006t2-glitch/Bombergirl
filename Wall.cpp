#include "Wall.h"
#include <iostream>

Wall::Wall() : position(0,0), loai(0), ton_tai(true) {}

Wall::Wall(sf::Vector2f pos, int loai, const std::string& duong_dan_anh)
    : position(pos), loai(loai), ton_tai(true)
{
    if (!texture.loadFromFile(duong_dan_anh)) {
        std::cout << "Khong load duoc anh: " << duong_dan_anh << std::endl;
        // Có thể xử lý bằng màu mặc định nếu cần
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
    // Nền (0) và cỏ (3) thì đi qua được, còn lại không
    if (!ton_tai) return true;  // nếu đã phá thì đi qua được
    return (loai == 0 || loai == 3);
}

bool Wall::coThePha() const {
    // Tường phá được (1) và cây (4) thì có thể phá
    return (ton_tai && (loai == 1 || loai == 4));
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
