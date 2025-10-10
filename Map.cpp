#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map() {}

Map::Map(const std::string& duongdan_file) {
    napFile(duongdan_file);
}

void Map::napFile(const std::string& duongdan_file) {
    std::ifstream file(duongdan_file);
    if (!file.is_open()) {
        std::cerr << "Khong mo duoc file map!" << std::endl;
        return;
    }

    int so_dong, so_cot;
    file >> so_dong >> so_cot;

    ds_phan_tu.clear();

    for (int i = 0; i < so_dong; i++) {
        for (int j = 0; j < so_cot; j++) {
            int loai;
            file >> loai;
            sf::Vector2f pos(j * 64.f, i * 64.f);
            std::string img_path;

            switch (loai) {
                case 0: img_path = "ground.png"; break;
                case 1: img_path = "wall1.png"; break;   // tường phá được
                case 2: img_path = "wall2.png"; break;   // tường không phá được
                case 3: img_path = "grass.png"; break;
                case 4: img_path = "tree.png"; break;    // cây
                default: img_path = "ground.png"; break;
            }

            ds_phan_tu.emplace_back(pos, loai, img_path);
        }
    }

    file.close();
}

void Map::ve(sf::RenderWindow& cua_so) {
    for (auto& phan_tu : ds_phan_tu) {
        phan_tu.ve(cua_so);
    }
}

std::vector<Wall>& Map::getWalls() {
    return ds_phan_tu;
}

bool Map::kiemTraVaCham(const sf::FloatRect& khung_nv) {
    for (auto& wall : ds_phan_tu) {
        if (!wall.coTheDiQua() && wall.tonTai() && wall.getBounds().intersects(khung_nv)) {
            return true;
        }
    }
    return false;
}

void Map::xuLyBomNo(float bom_x, float bom_y, int pham_vi) {
    // Vùng nổ bom
    sf::FloatRect vung_no(bom_x - 64.f * pham_vi, bom_y - 64.f * pham_vi,
                         64.f * (2 * pham_vi + 1), 64.f * (2 * pham_vi + 1));
    for (auto& wall : ds_phan_tu) {
        if (wall.coThePha() && wall.tonTai() && wall.getBounds().intersects(vung_no)) {
            wall.pha();
        }
    }
}
