#include "Map.h"
#include <fstream>
#include <iostream>
using namespace std;

Map::Map() {}

Map::Map(const string& duong_dan_file) {
    napFile(duong_dan_file);
}

// ======= NẠP FILE BẢN ĐỒ =======
void Map::napFile(const string& duong_dan_file) {
    ifstream file(duong_dan_file);
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

            // ======= VẼ NỀN (mặc định là nền gạch) =======
            Nen nen(Vector2f(j * 64, i * 64), "assets/ground.png");
            ds_nen[{i, j}] = nen;

            // ======= VẼ TƯỜNG, CỎ, CÂY =======
            if (loai == 1) {
                // Tường phá được
                ds_tuong[{i, j}] = Wall(Vector2f(j * 64, i * 64), true, "assets/wall.png", false);
            }
            else if (loai == 2) {
                // Tường không phá được
                ds_tuong[{i, j}] = Wall(Vector2f(j * 64, i * 64), false, "assets/wall2.png", false);
            }
            else if (loai == 3) {
                // Cỏ: có thể đi qua, chồng lên nền
                ds_tuong[{i, j}] = Wall(Vector2f(j * 64, i * 64), false, "assets/grass.png", true);
            }
            else if (loai == 4) {
                // Cây: có thể đi qua, cao hơn nền
                ds_tuong[{i, j}] = Wall(Vector2f(j * 64, i * 64 - 90), false, "assets/tree.png", true);
            }
        }
    }
}

// ======= VẼ TOÀN BỘ BẢN ĐỒ =======
void Map::ve(RenderWindow& cua_so) {
    // Vẽ nền trước
    for (auto& nen : ds_nen) {
        nen.second.ve(cua_so);
    }

    // Sau đó vẽ các vật thể lên trên (tường, cỏ, cây)
    for (auto& tuong : ds_tuong) {
        tuong.second.ve(cua_so);
    }
}

