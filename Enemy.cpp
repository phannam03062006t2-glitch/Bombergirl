#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

class Enemy {
protected:
    RectangleShape hinh;
    Vector2f vanToc;
    float tocDo = 1.0f;
    Clock doiHuongClock;

public:
    Enemy(float x, float y, Color mau) {
        hinh.setSize(Vector2f(64, 64));
        hinh.setFillColor(mau);
        hinh.setPosition(x, y);
        srand(time(0));
        datHuongNgauNhien();
    }

    virtual void datHuongNgauNhien() {
        int huong = rand() % 4;
        switch (huong) {
            case 0: vanToc = Vector2f(-tocDo, 0); break;  // trai
            case 1: vanToc = Vector2f(tocDo, 0); break;   // phai
            case 2: vanToc = Vector2f(0, -tocDo); break;  // len
            case 3: vanToc = Vector2f(0, tocDo); break;   // xuong
        }
    }

    virtual void capNhat(RenderWindow& cuaSo) {
        if (doiHuongClock.getElapsedTime().asSeconds() > 1.5f) {
            datHuongNgauNhien();
            doiHuongClock.restart();
        }

        hinh.move(vanToc);

        // gioi han cua so
        if (hinh.getPosition().x < 0 || hinh.getPosition().x + hinh.getSize().x > cuaSo.getSize().x) {
            vanToc.x = -vanToc.x;
        }
        if (hinh.getPosition().y < 0 || hinh.getPosition().y + hinh.getSize().y > cuaSo.getSize().y) {
            vanToc.y = -vanToc.y;
        }
    }

    virtual void ve(RenderWindow& cuaSo) {
        cuaSo.draw(hinh);
    }

    virtual ~Enemy() {}
};

// loai quai 1
class Enemy1 : public Enemy {
public:
    Enemy1(float x, float y) : Enemy(x, y, Color::Red) {}
};

// loai quai 2
class Enemy2 : public Enemy {
public:
    Enemy2(float x, float y) : Enemy(x, y, Color::Blue) {}
};

// loai quai 3
class Enemy3 : public Enemy {
public:
    Enemy3(float x, float y) : Enemy(x, y, Color::Green) {}
};

