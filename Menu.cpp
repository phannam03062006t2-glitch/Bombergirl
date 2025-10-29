#include "Menu.h"
#include <iostream>
#include "Diem.h"
using namespace std;

Menu::Menu() {
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Khong the tai font arial.ttf\n";
    }

    // ======= ANH NEN CHO MENU CHINH =======
    if (!bgTexture.loadFromFile("assets/anhmenu.png")) {
        cerr << "Khong the tai anh nen assets/anhmenu.png\n";
    }
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(1700.0f / bgTexture.getSize().x, 900.0f / bgTexture.getSize().y);

    // ======= ANH NEN CHO CAC MAN HINH =======
    if (!backgroundTextureMenu.loadFromFile("assets/anh_nen_menu.png")) {
        cerr << "Khong the tai anh_nen_menu.png\n";
    }
    backgroundSpriteMenu.setTexture(backgroundTextureMenu);
    backgroundSpriteMenu.setScale(1700.f / backgroundTextureMenu.getSize().x, 900.f / backgroundTextureMenu.getSize().y);

    // ======= TEXT MENU CHÍNH =======
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

// =========================
// MENU CHINH
// =========================
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
        window.draw(bgSprite); // n?n menu chính
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
    nenMo.setFillColor(Color(0, 0, 0, 150));

    Text pauseText, tiepTucText, thoatText;
    pauseText.setFont(font);
    pauseText.setString("GAME PAUSED");
    pauseText.setCharacterSize(60);
    pauseText.setFillColor(Color::Yellow);
    pauseText.setPosition(600, 250);

    tiepTucText.setFont(font);
    tiepTucText.setString("CONTINUE (ENTER)");
    tiepTucText.setCharacterSize(40);
    tiepTucText.setFillColor(Color::White);
    tiepTucText.setPosition(630, 400);

    thoatText.setFont(font);
    thoatText.setString("EXIT (ESC)");
    thoatText.setCharacterSize(40);
    thoatText.setFillColor(Color::White);
    thoatText.setPosition(700, 480);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return) return 0; // ti?p t?c
                if (event.key.code == Keyboard::Escape) return 1; // thoát
            }
        }

        window.clear();
        window.draw(backgroundSpriteMenu); // n?n ph?
        window.draw(nenMo);
        window.draw(pauseText);
        window.draw(tiepTucText);
        window.draw(thoatText);
        window.display();
    }
    return 1;
}

// =========================
// MENU GAME OVER
// =========================
bool Menu::hienGameOver(RenderWindow &window, int diem) {
    RectangleShape nenMo(Vector2f(1700, 900));
    nenMo.setFillColor(Color(0, 0, 0, 200));

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setPosition(600, 250);

    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(Color::White);
    scoreText.setString("SCORE: " + to_string(diem));
    scoreText.setPosition(727, 380);

    Text restartText, exitText, rankText; 
    restartText.setFont(font);
    restartText.setCharacterSize(40);
    restartText.setFillColor(Color::Yellow);
    restartText.setString("PRESS ENTER TO RETURN TO MENU");
    restartText.setPosition(510, 500);
    
    rankText.setFont(font);
    rankText.setCharacterSize(40);
    rankText.setFillColor(Color::Cyan);
    rankText.setString("PRESS Q TO VIEW LEADERBOARD");
    rankText.setPosition(560, 540);

    exitText.setFont(font);
    exitText.setCharacterSize(40);
    exitText.setFillColor(Color::White);
    exitText.setString("PRESS ESC TO EXIT");
    exitText.setPosition(655, 580);
	
	diemGame.capNhatBangXepHang();
	
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Return) 
                    return true; 
                if(event.key.code==Keyboard::Q) {
                	hienBangXepHang(window);
				}
                if (event.key.code == Keyboard::Escape) {
                    return false;
                }
            }
        }

        window.clear();
        window.draw(backgroundSpriteMenu); // n?n ph?
        window.draw(nenMo);
        window.draw(gameOverText);
        window.draw(scoreText);
        window.draw(restartText);
        window.draw(rankText);
        window.draw(exitText);
        window.display();
    }
    return false;
}

// =========================
// HIEN BANG XEP HANG
// =========================
bool Menu::hienBangXepHang(RenderWindow &window) {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Return) {
                return true; 
            }
        }

        window.clear();
        window.draw(backgroundSpriteMenu); // n?n ph?
        diemGame.veBangXepHang(window);
        window.display();
    }
    return false;
}

// =========================
// NHAP TEN NGUOI CHOI
// =========================
string nhapTenNguoiChoi(RenderWindow &window, Font &font) {
    string name = "";
// Anh nen
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/anh_nen_menu.png")) {
        cerr << "Khong the tai anh_nen_menu.png!\n";
    }
    Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(1700.f / backgroundTexture.getSize().x, 900.f / backgroundTexture.getSize().y);

// VUNG HIEN THI TEN
	RectangleShape inputBox(Vector2f(300, 60)); // tao o chu nhat
    inputBox.setFillColor(Color(0, 0, 0, 150)); // mau den trong suot
    inputBox.setOutlineColor(Color::Cyan);		//Vien trang
    inputBox.setOutlineThickness(3);			//do day vien
    inputBox.setPosition(800, 295);				//vi tri o nhap ten
    
// CHU HIEN TEN NGUOI CHOI
    Text textNhap("PLAYER NAME: ", font, 35);
    textNhap.setFillColor(Color::White);
    textNhap.setPosition(530, 300);

    Text textTen("", font, 35);
    textTen.setFillColor(Color::Cyan);
    textTen.setPosition(810, 300);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::TextEntered) {
                if (event.text.unicode == '\b') { 
                    if (!name.empty())
                        name.pop_back();
                } 
                else if (event.text.unicode == '\r') { 
                    if (!name.empty()) 
                        return name;
                } 
                else if (event.text.unicode < 128 && event.text.unicode >= 32) {
                    name += static_cast<char>(event.text.unicode);
                }
            }
        }

        textTen.setString(name);

        window.clear();
        window.draw(backgroundSprite); // ve anh nen  
        window.draw(textNhap);
         window.draw(inputBox);        // ve o nhap ten
        window.draw(textTen);
        window.display();
    }

    return name;
}
