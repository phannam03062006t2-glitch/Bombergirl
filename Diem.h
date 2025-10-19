#pragma once

#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Diem {
private:
    int points;
    Font font;
    Text text;

public:
    Diem();
    void add(int p);
    int get();
    void draw(RenderWindow& window);
    void save(const string& filename);
    void reset();
};


extern Diem diemGame;


