#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
using namespace sf;
using namespace std;

// ===== Cau truc luu ten va diem nguoi choi =====
struct PlayerScore {
    string name;   // Ten nguoi choi
    int score;     // So diem dat duoc
};

// ===== Lop quan ly diem va bang xep hang =====
class Diem {
private:
    int points;                 // Diem hien tai cua nguoi choi
    string playerName;          // Ten nguoi choi hien tai
    Font font;                  // Font chu hien thi
    Text text;                  // Chu hien thi diem
    vector<PlayerScore> bangXepHang;  // Danh sach top 5 diem

public:
    Diem();                                      // Ham khoi tao
    void setPlayerName(const string &name);      // Gan ten nguoi choi
    void add(int p);                             // Cong them diem
    int get();                                   // Lay diem hien tai
    void draw(RenderWindow &window);             // Ve diem len man hinh
    void save(const string &filename);           // Luu diem (cap nhat bang)
    void reset();                                // Dat lai diem khi choi lai
    bool daLuu = false;                          // Co kiem tra da luu chua

    // Cac ham lien quan bang xep hang
    void capNhatBangXepHang();                   // Cap nhat top diem moi
    void veBangXepHang(RenderWindow &window);    // Ve bang xep hang
    void docBangXepHang(const string &filename); // Doc bang tu file
    void ghiBangXepHang(const string &filename); // Ghi bang ra file
};

// Bien toan cuc (toan bo tro choi dung chung)
extern Diem diemGame;
