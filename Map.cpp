#include "Map.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace sf;

Map::Map() {}

Map::Map(const string& duongdan_file) {
    napFile(duongdan_file);
}

void Map::napFile(const string& duongdan_file) {
    ifstream file(duongdan_file);
    if (!file.is_open()) {
        throw runtime_error("Khong mo duoc file map: " + duongdan_file);
    }

    int hang, cot;
    file >> hang >> cot;
    if (!file || hang <= 0 || cot <= 0) {
        throw runtime_error("File map khong hop le!");
    }

    danh_sach_tuong_pha_duoc.clear();
    danh_sach_tuong_khong_pha.clear();

    int a;
    int i = 0, j = 0;

    while (file >> a) {
        float x = j * 64.f;
        float y = i * 64.f;

        if (a == 1)
            danh_sach_tuong_khong_pha.push_back(Wall2(x, y));
        else if (a == 2)
            danh_sach_tuong_pha_duoc.push_back(Wall(x, y));

        j++;
        if (j >= cot) {
            j = 0;
            i++;
        }
    }

    cout << "Da nap map thanh cong! (" << hang << "x" << cot << ")\n";
}

void Map::ve(RenderWindow& window) {
    for (auto& tuong : danh_sach_tuong_khong_pha)
        tuong.Ve(window);
    for (auto& tuong : danh_sach_tuong_pha_duoc)
        tuong.Ve(window);
}

vector<Wall>& Map::layDanhSachTuongPhaDuoc() {
    return danh_sach_tuong_pha_duoc;
}

vector<Wall2>& Map::layDanhSachTuongKhongPha() {
    return danh_sach_tuong_khong_pha;
}

bool Map::kiemTraVaCham(const FloatRect& khung_nv) {
    for (auto& tuong : danh_sach_tuong_khong_pha) {
        if (khung_nv.intersects(tuong.SPRITE.getGlobalBounds()))
            return true;
    }
    for (auto& tuong : danh_sach_tuong_pha_duoc) {
        if (khung_nv.intersects(tuong.SPRITE.getGlobalBounds()))
            return true;
    }
    return false;
}
