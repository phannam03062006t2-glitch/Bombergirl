#include "ThanhMau.h"
#include <iostream>

ThanhMau::ThanhMau(int maxHearts) {
    soTimToiDa = maxHearts;

    if (!heartTexture.loadFromFile("assets/heart.png")) {
        std::cerr << "Khong the tai assets/heart.png\n";
    }

    // N?n t?i m? phía sau thanh máu
    background.setSize(Vector2f(180, 60));
    background.setFillColor(Color(0, 0, 0, 120)); // ðen trong su?t
    background.setPosition(1500, 10); // góc ph?i trên

    hearts.resize(maxHearts);
    for (int i = 0; i < maxHearts; i++) {
        hearts[i].setTexture(heartTexture);
        hearts[i].setScale(0.1f, 0.1f);
        hearts[i].setPosition(1510 + i * 55, 20);
    }
}

void ThanhMau::capNhat(int mauHienTai) {
    for (int i = 0; i < soTimToiDa; i++) {
        if (i < mauHienTai)
            hearts[i].setColor(Color::White);
        else
            hearts[i].setColor(Color(100, 100, 100, 150)); // m? khi m?t tim
    }
}

void ThanhMau::ve(RenderWindow &window) {
    window.draw(background);
    for (auto &h : hearts)
        window.draw(h);
}

