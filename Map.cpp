#include "Map.h"
#include <fstream>
#include <iostream>
#include <stdexcept> // Ä‘á»ƒ dÃ¹ng exception
using namespace std;

Map::Map() {}

Map::Map(const string& duongdan_file) {
    napFile(duongdan_file);
}

void Map::napFile(const string& duongdan_file) {
    ifstream file(duongdan_file);
    if (!file.is_open()) {
        throw runtime_error("Khong mo duoc file map!");
    }

    int so_dong, so_cot;
    if (!(file >> so_dong >> so_cot)) {
        throw runtime_error("File map khong hop le (thieu kich thuoc)!");
    }

    ds_phan_tu.clear();

    for (int i = 0; i < so_dong; i++) {
        for (int j = 0; j < so_cot; j++) {
            int loai;
            if (!(file >> loai)) {
                throw runtime_error("File map khong du du lieu o dong " + to_string(i));
            }

            // V? n?n (ground)
            if (loai == 0)
                ds_phan_tu.emplace_back(Vector2f(j * 64, i * 64), false, "ground.png", true);

            // V? tý?ng không th? phá (wall)
            else if (loai == 1)
                ds_phan_tu.emplace_back(Vector2f(j * 64, i * 64), true, "wall.png", false);

            // V? tý?ng có th? phá (wall2)
            else if (loai == 2)
                ds_phan_tu.emplace_back(Vector2f(j * 64, i * 64), false, "wall2.png", false);

            // V? c? (grass)
            else if (loai == 3)
                ds_phan_tu.emplace_back(Vector2f(j * 64, i * 64), false, "grass.png", true);

            // V? cây (tree)
            else if (loai == 4)
                ds_phan_tu.emplace_back(Vector2f(j * 64, i * 64 - 90), false, "tree.png", true);

            else
                cout << "Canh bao: Gia tri khong hop le (" << loai << ") tai dong " << i << ", cot " << j << endl;
        }
    }

    file.close();
}


void Map::ve(RenderWindow& cua_so) {
    for (auto& phan_tu : ds_phan_tu) {
        phan_tu.ve(cua_so);
    }
}

vector<Wall> Map::layTuongChan() {
    vector<Wall> chan;
    for (auto& p : ds_phan_tu) {
        if (!p.coTheDiQua())
            chan.push_back(p);
    }
    return chan;
}

bool Map::kiemTraVaCham(const FloatRect& khung_nv) {
    for (auto& p : ds_phan_tu) {
        if (!p.coTheDiQua() && khung_nv.intersects(p.layKhung()))
            return true;
    }
    return false;
}
