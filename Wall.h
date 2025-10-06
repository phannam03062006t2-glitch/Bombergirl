#ifndef WALL_H
#define WALL_H
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Wall {
private:
    RectangleShape hinh;  // Dạng fallback (ô vuông màu)
    Sprite anh;           // Dùng khi có texture (ảnh)
    Texture ket_cau;      // Dữ liệu hình ảnh (texture)
    Vector2f vitri;       // Vị trí trên bản đồ
    bool co_the_pha;      // Có thể phá được không
    bool di_qua;          // Có thể đi qua được không

public:
    Wall(); 
    Wall(Vector2f vitri, bool pha_duoc, const string& duongdan_anh, bool di_qua);

    void ve(RenderWindow& cua_so);
    FloatRect layKhung();

    bool laPhaDuoc();
    bool coTheDiQua();
};

#endif
