#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include <vector>
#include <string>
using namespace std;
using namespace sf;

class Map {
private:
    vector<Wall> ds_phan_tu; // các ô bản đồ

public:
    Map();
    Map(const string& duongdan_file);

    void napFile(const string& duongdan_file);
    void ve(RenderWindow& cua_so);

    // thêm: trả về danh sách tường có collision
    vector<Wall> layTuongChan();
};
