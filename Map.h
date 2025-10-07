#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Wall.h"
using namespace std;
using namespace sf;

class Map {
private:
    vector<Wall> ds_phan_tu; // danh sách các ô (nền, tường, cỏ, cây...)

public:
    Map();
    Map(const string& duongdan_file);
    void napFile(const string& duongdan_file); // nạp dữ liệu bản đồ
    void ve(RenderWindow& cua_so); // vẽ bản đồ
    vector<Wall> layTuongChan(); // trả về các ô không thể đi qua
    bool kiemTraVaCham(const FloatRect& khung_nv); // kiểm tra va chạm
};

#endif
