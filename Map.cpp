#include "Map.h"
#include <bits/stdc++.h>
using namespace std;

Map::Map() : hang(0), cot(0) {}

void Map::napFile(const string& tenfile) {
    ifstream fin(tenfile);
    if (!fin) throw runtime_error("Khong mo duoc file map!");

    fin >> hang >> cot;

    for (int i = 0; i < hang; i++) {
        for (int j = 0; j < cot; j++) {
            int loai;
            fin >> loai;
            Vector2f vitri(j * 64.f, i * 64.f);

            switch (loai) {
                case 0: // Nền gạch
                    ds_tuong[{i, j}] = Wall(vitri, true, "assets/floor.png");
                    break;
                case 1: // Cỏ
                    ds_tuong[{i, j}] = Wall(vitri, true, "assets/grass.png");
                    break;
                case 2: // Tường phá được
                    ds_tuong[{i, j}] = Wall(vitri, true, "assets/wall.png");
                    break;
                case 3: // Tường không phá được
                    ds_tuong[{i, j}] = Wall(vitri, false, "assets/wall2.png");
                    break;
                case 4: // Cây (trang trí)
                    ds_tuong[{i, j}] = Wall(vitri, true, "assets/tree.png");
                    break;
                default:
                    break;
            }
        }
    }
    fin.close();
}

void Map::ve(RenderWindow& cua_so) {
    for (auto& t : ds_tuong) {
        t.second.ve(cua_so);
    }
}

map<pair<int,int>, Wall>& Map::layDanhSach() {
    return ds_tuong;
}
