#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
using namespace sf;
using namespace std;

class Diem {
private:
    int points;
    Font font;
    Text text;
    vector<int> bangXepHang;

public:
    Diem();
    void add(int p);
    int get();
    void draw(RenderWindow& window);
    void save(const string& filename);
    void reset();
    bool daLuu = false;

    void capNhatBangXepHang();
    void veBangXepHang(RenderWindow&);

};


extern Diem diemGame;


