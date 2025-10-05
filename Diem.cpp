#include "Diem.h"
#include<fstream>
#include<stdexcept>
using namespace std;
Diem::Diem() {
	points=0;
	if(!font.loadFromFile("arial.ttf")) {
		throw runtime_error("Font arial.ttf not found!");
	}
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color::Red);
	text.setPosition(10,10);
}
void Diem::add(int p) {
	points += p;
}
int Diem::get() {return points; }

void Diem::draw(RenderWindow& window) {
	text.setString("Score: "+to_string(points));
	window.draw(text);
}

void Diem::save(const string& filename) {
	ofstream fout(filename);
	if(!fout) throw runtime_error("Khong the viet file diem!");
	fout<<points;
	fout.close();
}
