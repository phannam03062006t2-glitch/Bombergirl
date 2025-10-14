#include "Map.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
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
        throw runtime_error("File map khong hop le!");
    }

    danh_sach_phan_khac.clear();
    danh_sach_tuong_pha_duoc.clear();
    danh_sach_tuong_khong_pha.clear();

    for (int i = 0; i < so_dong; i++) {
        for (int j = 0; j < so_cot; j++) {
            int loai;
            if (!(file >> loai)) {
                throw runtime_error("File map khong du du lieu!");
            }

            Vector2f pos(j * 64, i * 64);

            switch (loai) {
                case 0:
                    break;
                case 1: // tuong pha duoc
                    danh_sach_tuong_pha_duoc.emplace_back(pos, loai, "assets/wall_soft.png");
                    break;
                case 2: // tuong khong pha
                    danh_sach_tuong_khong_pha.emplace_back(pos, loai, "assets/wall_hard.png");
                    break;
                default:
                    cout << "Gia tri loai khong hop le: " << loai << endl;
            }
        }
    }

    file.close();
}

void Map::ve(RenderWindow& window) {
    for (auto& obj : danh_sach_phan_khac)
        obj.ve(window);

    // Vẽ tường không phá trước
    for (auto& wall : danh_sach_tuong_khong_pha)
        wall.ve(window);

    // Vẽ tường phá được sau để đè lên vụ nổ
    for (auto& wall : danh_sach_tuong_pha_duoc)
        wall.ve(window);
}

vector<Wall>& Map::layDanhSachTuongPhaDuoc() {
    return danh_sach_tuong_pha_duoc;
}

vector<Wall>& Map::layDanhSachTuongKhongPha() {
    return danh_sach_tuong_khong_pha;
}

bool Map::kiemTraVaCham(const FloatRect& khung_nv) {
    for (auto& wall : danh_sach_tuong_khong_pha) {
        if (!wall.coTheDiQua() && wall.getBounds().intersects(khung_nv))
            return true;
    }

    for (auto& wall : danh_sach_tuong_pha_duoc) {
        if (wall.tonTai() && !wall.coTheDiQua() && wall.getBounds().intersects(khung_nv))
            return true;
    }

    return false;
}



