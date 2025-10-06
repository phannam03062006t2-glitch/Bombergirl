#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include <vector>
#include <string>
#include <map>
using namespace std;
using namespace sf;

class Map {
private:
    vector<Wall> ds_phan_tu; // Danh sách tất cả phần tử bản đồ (nền, cỏ, cây, tường,...)
public:
    Map();
    Map(const string& duongdan_file);

    void napFile(const string& duongdan_file); // Nạp dữ liệu bản đồ từ file
    void ve(RenderWindow& cua_so);             // Vẽ toàn bộ bản đồ
};
