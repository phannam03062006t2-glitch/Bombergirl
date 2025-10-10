#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Wall.h"
using namespace std;
using namespace sf;

class Map {
private:
    vector<Wall> danh_sach_tuong_pha_duoc;
    vector<Wall> danh_sach_tuong_khong_pha;

    vector<Wall> danh_sach_phan_khac; // gồm ground, grass, tree...

public:
    Map();
    Map(const string& duongdan_file);
    void napFile(const string& duongdan_file);
    void ve(RenderWindow& cua_so);

    vector<Wall>& layDanhSachTuongPhaDuoc();
    vector<Wall>& layDanhSachTuongKhongPha();

    bool kiemTraVaCham(const FloatRect& khung_nv);
};

#endif
