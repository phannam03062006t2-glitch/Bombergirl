#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "Wall.h"
using namespace std;
using namespace sf;

// Cấu trúc lưu thông tin một ô trong bản đồ
struct OMap {
    int loai;       // loại ô: 0 trống, 1 tường phá được, 2 tường cứng, 3 cỏ, 4 cây
    Vector2f viTri; // vị trí của ô trên cửa sổ
};

class Map {
private:
    map<pair<int, int>, Wall> ds_tuong; // danh sách tường
    vector<OMap> ds_o;                  // danh sách toàn bộ ô trong bản đồ
    int hang, cot;                      // kích thước bản đồ

    Texture nenTex, coTex, cayTex;      // các texture dùng để vẽ

public:
    Map();
    void napFile(const string& tenFile); // nạp dữ liệu bản đồ
    void ve(RenderWindow& cua_so);       // vẽ bản đồ
    map<pair<int, int>, Wall>& layDanhSach(); // trả danh sách tường
};

#endif
