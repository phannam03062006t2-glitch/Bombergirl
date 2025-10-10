#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Wall.h"

class Map {
private:
    std::vector<Wall> ds_phan_tu;

public:
    Map();
    Map(const std::string& duongdan_file);
    void napFile(const std::string& duongdan_file);
    void ve(sf::RenderWindow& cua_so);
    std::vector<Wall>& getWalls();

    // Kiểm tra va chạm player với các tường cản
    bool kiemTraVaCham(const sf::FloatRect& khung_nv);

    // Xử lý phá tường khi bom nổ
    void xuLyBomNo(float bom_x, float bom_y, int pham_vi);
};

#endif
