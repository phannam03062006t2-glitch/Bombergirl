#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>
#include <string>

class Wall {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    int loai;           // 0=nen,1=tuong pha duoc,2=tuong ko pha duoc,3=co,4=cay
    bool ton_tai;       // false nếu bị phá rồi

public:
    Wall();
    Wall(sf::Vector2f pos, int loai, const std::string& duong_dan_anh);

    void ve(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool coTheDiQua() const;  // player có đi qua được không
    bool coThePha() const;    // có thể phá bởi bom không
    bool tonTai() const;      // còn tồn tại không
    void pha();               // gọi khi bom phá tường/cây
    int getLoai() const;
};

#endif
