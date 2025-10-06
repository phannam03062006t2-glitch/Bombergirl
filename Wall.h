#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

class Wall {
private:
    Sprite hinh;
    Texture anh;
    bool pha_duoc;   // có thể bị phá khi bomb nổ không
    bool di_qua;     // có thể đi qua được không
    Vector2f vitri;

public:
    Wall();
    Wall(Vector2f vitri, bool pha_duoc, const string& duongdan_anh, bool di_qua = true);

    void ve(RenderWindow& window);
    bool coThePha() const;
    bool coTheDiQua() const;
    Vector2f layViTri() const;
};

#endif
