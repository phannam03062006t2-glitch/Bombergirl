#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Wall.h"

using namespace std;
using namespace sf;

class Map {
private:
    vector<Wall> danh_sach_tuong_pha_duoc;
    vector<Wall2> danh_sach_tuong_khong_pha;

public:
    Map();
    Map(const string& duongdan_file);

    void napFile(const string& duongdan_file);

 
    void ve(RenderWindow& window);


    vector<Wall>& layDanhSachTuongPhaDuoc();   // Tra ve tuong mem
    vector<Wall2>& layDanhSachTuongKhongPha(); //        tuong cung


    bool kiemTraVaCham(const FloatRect& khung_nv); //Kiem tra va tram
};

#endif

