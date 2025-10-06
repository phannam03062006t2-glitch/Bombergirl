#include "Map.h"
#include <fstream>
#include <iostream>
using namespace std;

Map::Map() {}

Map::Map(const string& duong_dan_file)
{
    napFile(duong_dan_file);
}

// ======= HÀM NẠP DỮ LIỆU BẢN ĐỒ =======
void Map::napFile(const string& duong_dan_file)
{
    ifstream file(duong_dan_file);
    if (!file.is_open()) {
        cout << "Khong the mo file map!" << endl;
        return;
    }

    int so_dong, so_cot;
    file >> so_dong >> so_cot;

    for (int i = 0; i < so_dong; i++) {
        for (int j = 0; j < so_cot; j++) {
            int loai;
            file >> loai;

            // ======= ẢNH NỀN (layer thấp nhất) =======
            Nen nen(Vector2f(j * 64, i * 64), "assets/grass.png");
            ds_nen[{i, j}] = nen;

            // ======= TẠO TƯỜNG, CỎ, CÂY =======
            if (loai == 1) {
                // Tường phá được
                ds_tuong[{i, j}] = Wall(Vector2f(j * 64, i * 64), true, "assets/breakable.png", false);
            }
            else if (loai == 2) {
                // Tường không phá được
                ds_tuong[{i, j}] = Wall(Vector2f(j * 64, i * 64), false, "assets/solid.png", false);
            }
            else if (loai == 3) {
                // Cỏ - vẽ chồng lên nền (đi qua được)
                ds_tuong[{i, j}] = Wall(Vector2f(j * 64, i * 64), false, "assets/grass_top.png", true);
            }
            else if (loai == 4) {
                // Cây - cao hơn 1 ô, căn Y lên để chân cây nằm vừa ô
                ds_tuong[{i, j}] = Wall(Vector2f(j * 64, i * 64 - 91), false, "assets/tree.png", false);
            }
        }
    }

    file.close();
}

// ======= HÀM VẼ MAP =======
void Map::ve(RenderWindow& cua_so)
{
    // Vẽ nền trước
    for (auto& n : ds_nen)
        n.second.ve(cua_so);

    // Sau đó vẽ tường, cây, cỏ, v.v...
    for (auto& t : ds_tuong)
        t.second.ve(cua_so);
}
