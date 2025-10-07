#include "Map.h"
#include <fstream>
#include <iostream>
using namespace std;

Map::Map() {}

Map::Map(const string& duongdan_file) {
    napFile(duongdan_file);
}

// NẠP FILE BẢN ĐỒ
void Map::napFile(const string& duongdan_file) {
    ifstream file(duongdan_file);
    if (!file.is_open()) {
        cout << "Khong mo duoc file map!" << endl;
        return;
    }

    int so_dong, so_cot;
    file >> so_dong >> so_cot;

    for (int i = 0; i < so_dong; i++) {
        for (int j = 0; j < so_cot; j++) {
            int loai;
            file >> loai;

            // NỀN MẶC ĐỊNH
            // Luôn vẽ nền gạch dưới cùng
            Wall nen(Vector2f(j * 64, i * 64), false, "assets/ground.png", true);
            ds_phan_tu.push_back(nen);

            // PHÂN LOẠI CÁC Ô 
            if (loai == 1) {
                // Tường phá được
                Wall tuongpha(Vector2f(j * 64, i * 64), true, "assets/wall.png", false);
                ds_phan_tu.push_back(tuongpha);
            }
            else if (loai == 2) {
                // Tường không phá được
                Wall tuongcung(Vector2f(j * 64, i * 64), false, "assets/wall2.png", false);
                ds_phan_tu.push_back(tuongcung);
            }
            else if (loai == 3) {
                // Cỏ: có thể đi qua, chồng lên nền
                Wall co(Vector2f(j * 64, i * 64), false, "assets/grass.png", true);
                ds_phan_tu.push_back(co);
            }
            else if (loai == 4) {
                // Cây: cao hơn nền, có thể đi qua
                Wall cay(Vector2f(j * 64, i * 64 - 90), false, "assets/tree.png", true);
                ds_phan_tu.push_back(cay);
            }
        }
    }
}

// VẼ TOÀN BỘ BẢN ĐỒ 
void Map::ve(RenderWindow& cua_so) {
    for (auto& phan_tu : ds_phan_tu) {
        phan_tu.ve(cua_so);
    }
}

