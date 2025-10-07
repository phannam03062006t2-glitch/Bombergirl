#include "Map.h"
#include <fstream>
#include <iostream>
using namespace std;

Map::Map() {}

Map::Map(const string& duongdan_file) {
    napFile(duongdan_file);
}

void Map::napFile(const string& duongdan_file) {
    ifstream file(duongdan_file);
    if (!file.is_open()) {
        cout << "Khong mo duoc file map!" << endl;
        return;
    }

    int so_dong, so_cot;
    file >> so_dong >> so_cot;

    ds_phan_tu.clear();

    for (int i = 0; i < so_dong; i++) {
        for (int j = 0; j < so_cot; j++) {
            int loai;
            file >> loai;

            // vẽ nền trước
            ds_phan_tu.emplace_back(Vector2f(j * 64, i * 64), false, "assets/ground.png", true);

            // phân loại ô
            if (loai == 1)
                ds_phan_tu.emplace_back(Vector2f(j * 64, i * 64), true, "assets/wall.png", false);
            else if (loai == 2)
                ds_phan_tu.emplace_back(Vector2f(j * 64, i * 64), false, "assets/wall2.png", false);
            else if (loai == 3)
                ds_phan_tu.emplace_back(Vector2f(j * 64, i * 64), false, "assets/grass.png", true);
            else if (loai == 4)
                ds_phan_tu.emplace_back(Vector2f(j * 64, i * 64 - 90), false, "assets/tree.png", true);
        }
    }
}

void Map::ve(RenderWindow& cua_so) {
    for (auto& phan_tu : ds_phan_tu) {
        phan_tu.ve(cua_so);
    }
}

// trả về các ô không thể đi qua để kiểm tra va chạm
vector<Wall> Map::layTuongChan() {
    vector<Wall> chan;
    for (auto& p : ds_phan_tu) {
        if (!p.coTheDiQua())
            chan.push_back(p);
    }
    return chan;
}
