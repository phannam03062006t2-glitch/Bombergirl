#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Wall.h"
using namespace std;
using namespace sf;

class Map {
private:
    vector<Wall> ds_phan_tu; // danh sach cac o (nen, tuong, co, cay...)

public:
    Map();
    Map(const string& duongdan_file);
    void napFile(const string& duongdan_file); // nap du lieu ban do
    void ve(RenderWindow& cua_so); // ve ban do
    vector<Wall> layTuongChan(); // tra ve cac o khong the di qua
    bool kiemTraVaCham(const FloatRect& khung_nv); // kiem tra va cham
};

#endif
