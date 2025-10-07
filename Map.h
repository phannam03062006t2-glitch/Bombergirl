#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "Wall.h"
using namespace std;
using namespace sf;

class Map {
private:
    vector<Wall> ds_phan_tu;

public:
    Map();
    Map(const string& duongdan_file);
    void napFile(const string& duongdan_file);
    void ve(RenderWindow& cua_so);
    vector<Wall> layTuongChan();
    bool kiemTraVaCham(const FloatRect& khung_nv);
};

#endif
