#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu() {
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Khong the tai font arial.ttf\n";
    }

    if (!bgTexture.loadFromFile("assets/anhnen.png")) {
        cerr << "Khong the tai anh nen assets/anhnen.png\n";
    }

    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(1700.0f / bgTexture.getSize().x, 900.0f / bgTexture.getSize().y);

    
    startText.setFont(font);
    startText.setString("PRESS ENTER TO START");
    startText.setCharacterSize(40);
    startText.setFillColor(Color::White);
    startText.setPosition(580, 400);

    exitText.setFont(font);
    exitText.setString("PRESS ESC TO EXIT");
    exitText.setCharacterSize(40);
    exitText.setFillColor(Color::White);
    exitText.setPosition(610, 470);
}

bool Menu::hienMenu(RenderWindow &window) {
    Clock blinkClock;
    bool visible = true;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return) return true;
                if (event.key.code == Keyboard::Escape) return false;
            }
        }

        if (blinkClock.getElapsedTime().asSeconds() > 0.5f) {
            visible = !visible;
            blinkClock.restart();
        }

        window.clear();
        window.draw(bgSprite);
        window.draw(title);
        if (visible) window.draw(startText);
        if (visible) window.draw(exitText);
        window.display();
    }
    return false;
}

// =========================
// MENU TAM DUNG (PAUSE)
// =========================
int Menu::hienPause(RenderWindow &window) {
    RectangleShape nenMo(Vector2f(1700, 900));
    nenMo.setFillColor(Color(0, 0, 0, 180));

    Text pauseText, tiepTucText, thoatText;
    pauseText.setFont(font);
    pauseText.setString("GAME PAUSED");
    pauseText.setCharacterSize(60);
    pauseText.setFillColor(Color::Yellow);
    pauseText.setPosition(650, 250);

    tiepTucText.setFont(font);
    tiepTucText.setString("CONTINUE (ENTER)");
    tiepTucText.setCharacterSize(40);
    tiepTucText.setFillColor(Color::White);
    tiepTucText.setPosition(680, 400);

    thoatText.setFont(font);
    thoatText.setString("EXIT (ESC)");
    thoatText.setCharacterSize(40);
    thoatText.setFillColor(Color::White);
    thoatText.setPosition(750, 480);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return) return 0; // tiep tuc
                if (event.key.code == Keyboard::Escape) return 1; // thoat
            }
        }

        window.clear();
        window.draw(nenMo);
        window.draw(pauseText);
        window.draw(tiepTucText);
        window.draw(thoatText);
        window.display();
    }
    return 1;
}
// menu game over
bool Menu::hienGameOver(RenderWindow &window, int diem) {
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Khong the tai font arial.ttf\n";
    }

    Text gameOverText, diemText, enterText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(600, 250);

    diemText.setFont(font);
    diemText.setString("Diem cua ban: " + to_string(diem));
    diemText.setCharacterSize(50);
    diemText.setFillColor(Color::White);
    diemText.setPosition(600, 350);

    enterText.setFont(font);
    enterText.setString("Nhan ENTER de choi lai");
    enterText.setCharacterSize(40);
    enterText.setFillColor(Color::White);
    enterText.setPosition(550, 450);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return)
                    return true;  // Chõi l?i
                if (event.key.code == Keyboard::Escape)
                    return false; // Thoát
            }
        }

        window.clear();
        window.draw(gameOverText);
        window.draw(diemText);
        window.draw(enterText);
        window.display();
    }
    return false;
}
 

