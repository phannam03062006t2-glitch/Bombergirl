#include "Diem.h"
#include <algorithm>
#include <fstream>
using namespace std;

Diem diemGame;

Diem::Diem() {
    points = 0;
    daLuu=false;
    
    if (!font.loadFromFile("arial.ttf")) {
        throw runtime_error("Font arial.ttf not found!");
    }
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color::Red);
    text.setPosition(10, 10);
    
    //Doc bang xep hang khi file khoi tao
    docBangXepHang("score.txt");
}

void Diem::add(int p) {
    points += p;
}

int Diem::get() {
    return points;
}

void Diem::draw(RenderWindow &window) {
    text.setString("Score: " + to_string(points));
    text.setPosition(840, 70);
    window.draw(text);
}

void Diem::save(const string &filename) {
    // Cap nhat tam trong ram
    capNhatBangXepHang();
}

void Diem::reset() {
    points = 0;
    daLuu=false;
}

// ================== BANG XEP HANG TRONG RAM ==================
void Diem::capNhatBangXepHang() {
    // Them diem hien tai
    if(daLuu) return;
    
    bangXepHang.push_back(points);
    daLuu=true;

    // Sap xep giam dan
    sort(bangXepHang.begin(), bangXepHang.end(), greater<int>());

    // Giu lai top 5
    if (bangXepHang.size() > 5)
        bangXepHang.resize(5);
        
    //Ghi lai vao file
    ghiBangXepHang("score.txt");
}

void Diem::veBangXepHang(RenderWindow& window) {
    // Tieu de
    Text title("TOP 5 SCORE", font, 50);
    title.setFillColor(Color::Yellow);
    title.setPosition(700, 150);
    window.draw(title);

    // In diem
    for (int i = 0; i < (int)bangXepHang.size(); i++) {
        Text line(to_string(i + 1) + ". " + to_string(bangXepHang[i]), font, 40);
        line.setFillColor(Color::White);
        line.setPosition(800, 230 + i * 60);
        window.draw(line);
    }

    // Goi y quay lai 
    Text note("PRESS ENTER TO RETURN", font, 25);
    note.setFillColor(Color::Cyan);
    note.setPosition(696, 600);
    window.draw(note);
}
//===== Doc va ghi file =====
void Diem::docBangXepHang(const string &filename) {
	ifstream file(filename);
	bangXepHang.clear();
	int diem;
	if (file.is_open()) {
		while(file>>diem) {
			bangXepHang.push_back(diem);
		}
		file.close();
	}
	sort(bangXepHang.begin(),bangXepHang.end(),greater<int>());
	
	// Giu lai top 5 neu co nhieu hon
	if(bangXepHang.size()>5);
	bangXepHang.resize(5);
}

void Diem::ghiBangXepHang(const string &filename) {
	ofstream file(filename);
	if(file.is_open()) {
		for(int diem : bangXepHang) {
			file<<diem<<"\n";
		}
		file.close();
	}
}
