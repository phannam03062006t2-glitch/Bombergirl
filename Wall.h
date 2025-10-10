#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include <string>

class Wall {
private:
    sf::Vector2f position;
    int loai;
    bool ton_tai;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Wall();  // mặc định
    Wall(sf::Vector2f pos, int loai, const std::string& duong_dan_anh);

    void ve(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

    bool coTheDiQua() const;     // Nền, cỏ: đi được. Tường, cây: không đi được
    bool coThePha() const;       // Tường mềm, cây: có thể phá
    bool tonTai() const;         // Còn tồn tại trên map không
    void pha();                  // Phá tường/cây
    int getLoai() const;         // Loại gì (0..4)
};

#endif
