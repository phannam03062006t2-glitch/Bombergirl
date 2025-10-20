#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
using namespace sf;

class Menu {
private:
    Font font;
    Texture bgTexture;
    Sprite bgSprite;
    Text title;
    Text startText;
    Text exitText;

public:
    Menu();
    bool hienGameOver(RenderWindow &window, int diem);
    bool hienMenu(RenderWindow &window);
    int hienPause(RenderWindow &window); // 0: tiep tuc, 1: thoat
    bool hienBangXepHang(RenderWindow &window);

};

#endif
