#ifndef THANHMAU_H
#define THANHMAU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
using namespace sf;
using namespace std;

class ThanhMau {
private:
    vector<Sprite> hearts;
    Texture heartTexture;
    RectangleShape background;
    int soTimToiDa;

public:
    ThanhMau(int maxHearts = 3);
    void capNhat(int mauHienTai);
    void ve(RenderWindow &window);
};

#endif

