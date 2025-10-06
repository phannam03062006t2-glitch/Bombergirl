#include "Map.h"
#include <bits/stdc++.h>
using namespace std;

Map::Map() : hang(0), cot(0) {}

// Hàm nạp dữ liệu bản đồ từ file
void Map::napFile(const string& tenfile) {
    ifstream fin(tenfile);
    if (!fin) throw runtime_error("Khong mo duoc file map!");

    // Đọc kích thước bản đồ
    fin >> hang >> cot;

    // Duyệt qua từng ô trong bản đồ
    for (int i = 0; i < hang; i++) {
        for (int j = 0; j < cot; j++) {
            int loai;
            fin >> loai;

            // Lưu lại thông tin từng ô
            ds_o.push_back({loai, Vector2f(j * 64, i * 64)});

            // Nếu là tường thì thêm vào danh sách tường
            if (loai == 1) {
                ds_tuong[{i, j}] = Wall(Vector2f(j * 64, i * 64), true, "assets/wall.png");
            }
            else if (loai == 2) {
                ds_tuong[{i, j}] = Wall(Vector2f(j * 64, i * 64), false, "assets/wall2.png");
            }
        }
    }
    fin.close();

    // Nạp ảnh nền và các loại ô khác
    nenTex.loadFromFile("assets/ground.png"); // nền gạch
    coTex.loadFromFile("assets/grass.png");   // cỏ
    cayTex.loadFromFile("assets/tree.png");   // cây
}

// Hàm vẽ bản đồ ra cửa sổ
void Map::ve(RenderWindow& cua_so) {
    // --------- Vẽ nền toàn bản đồ ---------
    Sprite nen(nenTex);
    for (auto& o : ds_o) {
        nen.setPosition(o.viTri);
        cua_so.draw(nen); // luôn vẽ nền ở tất cả các ô
    }

    // --------- Vẽ cỏ và cây đè lên nền ---------
    Sprite anhCo(coTex);
    Sprite anhCay(cayTex);

    for (auto& o : ds_o) {
        if (o.loai == 3) { // ô cỏ
            anhCo.setPosition(o.viTri);
            cua_so.draw(anhCo);
        }
        else if (o.loai == 4) { // ô cây
            anhCay.setPosition(o.viTri);
            cua_so.draw(anhCay);
        }
    }

    // --------- Vẽ các bức tường ---------
    for (auto& t : ds_tuong) {
        t.second.ve(cua_so);
    }
}

// Trả về danh sách tường (để xử lý va chạm)
map<pair<int, int>, Wall>& Map::layDanhSach() {
    return ds_tuong;
}
