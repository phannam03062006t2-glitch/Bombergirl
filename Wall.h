#ifndef WALL_H
#define WALL_H
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Wall {
private:
    RectangleShape hinh;         // hinh chu nhat de ve tuong
    Sprite anh;                  // sprite cho tuong
    Texture ket_cau;             // texture dung noi bo
    Vector2f vitri;              // vi tri cua tuong
    bool co_the_pha;             // kiem tra xem tuong co the pha duoc khong
    bool di_qua;                 // kiem tra xem co the di qua tuong khong

public:
    Wall();
    Wall(Vector2f vitri, bool pha_duoc, const string& duongdan_anh, bool di_qua);

    void ve(RenderWindow& cua_so);  // ve tuong
    FloatRect layKhung();          // lay khung va cham cua tuong

    bool laPhaDuoc();              // kiem tra tuong co the pha duoc
    bool coTheDiQua();             // kiem tra tuong co the di qua
};

#endif
