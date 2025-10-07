#ifndef WALL_H
#define WALL_H
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Wall {
private:
    RectangleShape hinh;
    Sprite anh;
    Texture ket_cau;      // texture dùng nội bộ
    Vector2f vitri;
    bool co_the_pha;
    bool di_qua;

public:
    Wall();
    Wall(Vector2f vitri, bool pha_duoc, const string& duongdan_anh, bool di_qua);

    void ve(RenderWindow& cua_so);
    FloatRect layKhung();

    bool laPhaDuoc();
    bool coTheDiQua();
};

#endif
