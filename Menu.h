#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Menu {
private:
    Font font;

    // === N?N MENU CH�NH ===
    Texture bgTexture;
    Sprite bgSprite;

    // === N?N CHO C�C M�N PH? ===
    Texture backgroundTextureMenu;
    Sprite backgroundSpriteMenu;

    Text title;
    Text startText;
    Text exitText;

public:
    Menu();
    bool hienGameOver(RenderWindow &window, int diem);
    bool hienMenu(RenderWindow &window);
    int hienPause(RenderWindow &window); // 0: ti?p t?c, 1: tho�t
    bool hienBangXepHang(RenderWindow &window);
};

std::string nhapTenNguoiChoi(sf::RenderWindow &window, sf::Font &font);

#endif
