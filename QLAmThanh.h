#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <vector>
#include <string>
using namespace std;
using namespace sf;

// Lop quan ly am thanh trong game
class QLAmThanh {
private:
    map<string, SoundBuffer> buffers; // Luu cac tep am da nap
    vector<Sound> sounds;             // Danh sach cac am dang phat

public:
    // Nap am thanh tu tep vao bo nho
    void napAm(const string& ten, const string& duongdan);

    // Phat mot am thanh ngan theo ten da nap
    void phatAm(const string& ten);

    // Phat nhac nen (loop vo han)
    void phatNhacNen(const string& duongdan);

    // Cap nhat, xoa cac am thanh da phat xong
    void capNhat();
};

