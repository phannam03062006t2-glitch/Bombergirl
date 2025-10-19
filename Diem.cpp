#include "Diem.h"
#include <string>
#include <fstream>
#include <stdexcept>
using namespace std;
Diem diemGame;
Diem::Diem() {
    points = 0;
    if (!font.loadFromFile("arial.ttf")) {
        throw runtime_error("Font arial.ttf not found!");
    }
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color::Red);
    text.setPosition(10, 10);
}

void Diem::add(int p) {
    points += p;
}

int Diem::get() {
    return points;
}

void Diem::draw(RenderWindow &window) {
    text.setString("Score: " + to_string(points));
    text.setPosition(840,70);
    window.draw(text);
}

void Diem::save(const string &filename) {
    ofstream fout(filename.c_str());
    if (!fout) throw runtime_error("Khong the viet file diem!");
    fout << points;
    fout.close();
}

void Diem::reset() {
	points=0;
}
