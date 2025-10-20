#include "Diem.h"
#include <algorithm>
#include <fstream>
using namespace std;

Diem diemGame;       // Bien toan cuc
string playerName;   // Luu ten nguoi choi hien tai

// ===== Ham khoi tao =====
Diem::Diem() {
    points = 0;
    daLuu = false;

    // Nap font chu
    if (!font.loadFromFile("arial.ttf")) {
        throw runtime_error("Khong tim thay file arial.ttf!");
    }

    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color::Red);
    text.setPosition(10, 10);

    // Doc bang xep hang khi bat dau game
    docBangXepHang("score.txt");
}

// ===== Gan ten nguoi choi =====
void Diem::setPlayerName(const string &name) {
    playerName = name;
}

// ===== Cong diem =====
void Diem::add(int p) {
    points += p;
}

// ===== Lay diem hien tai =====
int Diem::get() {
    return points;
}

// ===== Ve diem tren man hinh =====
void Diem::draw(RenderWindow &window) {
    text.setString("Score: " + to_string(points));
    text.setPosition(840, 70);
    window.draw(text);
}

// ===== Luu diem (cap nhat bang xep hang) =====
void Diem::save(const string &filename) {
    capNhatBangXepHang();
}

// ===== Dat lai diem khi choi lai =====
void Diem::reset() {
    points = 0;
    daLuu = false;
}

// ===== Cap nhat bang xep hang trong RAM =====
void Diem::capNhatBangXepHang() {
    // Neu da luu roi thi khong luu lai nua
    if (daLuu) return;

    // Them diem hien tai vao danh sach
    PlayerScore ps;
    ps.name = playerName;
    ps.score = points;
    bangXepHang.push_back(ps);
    daLuu = true;

    // Sap xep giam dan theo diem
    sort(bangXepHang.begin(), bangXepHang.end(),
         [](const PlayerScore &a, const PlayerScore &b) {
             return a.score > b.score;
         });

    // Chi giu lai top 5 nguoi cao diem nhat
    if (bangXepHang.size() > 5)
        bangXepHang.resize(5);

    // Ghi lai vao file
    ghiBangXepHang("score.txt");
}

// ===== Ve bang xep hang tren man hinh =====
void Diem::veBangXepHang(RenderWindow &window) {
    // Tieu de
    Text title("TOP 5 SCORE", font, 50);
    title.setFillColor(Color::Yellow);
    title.setPosition(700, 150);
    window.draw(title);

    // Hien thi tung dong diem
    for (int i = 0; i < (int)bangXepHang.size(); i++) {
        string lineStr = to_string(i + 1) + ". " + bangXepHang[i].name + " - " + to_string(bangXepHang[i].score);
        Text line(lineStr, font, 40);
        line.setFillColor(Color::White);
        line.setPosition(700, 230 + i * 60);
        window.draw(line);
    }

    // Chu huong dan quay lai
    Text note("PRESS ENTER TO RETURN", font, 25);
    note.setFillColor(Color::Cyan);
    note.setPosition(696, 600);
    window.draw(note);
}

// ===== Doc bang xep hang tu file =====
void Diem::docBangXepHang(const string &filename) {
    ifstream file(filename);
    bangXepHang.clear();
    PlayerScore ps;

    if (file.is_open()) {
        while (file >> ps.name >> ps.score) {
            bangXepHang.push_back(ps);
        }
        file.close();
    }

    // Sap xep giam dan theo diem
    sort(bangXepHang.begin(), bangXepHang.end(),
         [](const PlayerScore &a, const PlayerScore &b) {
             return a.score > b.score;
         });

    // Chi lay top 5
    if (bangXepHang.size() > 5)
        bangXepHang.resize(5);
}

// ===== Ghi bang xep hang ra file =====
void Diem::ghiBangXepHang(const string &filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (auto &p : bangXepHang) {
            file << p.name << " " << p.score << "\n";
        }
        file.close();
    }
}
