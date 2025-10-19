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
	Music nhacNen;
public:
    void napAm(const string& ten, const string& duongdan); // Nap am thanh tu tep vao bo nho
    void phatAm(const string& ten); // Phat mot am thanh ngan theo ten da nap
	void phatNhacNen(const string& duongdan);  // Phat nhac nen (lap vo han)
    void dungTatCaAmThanh(); //Dung tat ca am thanh
    void tamDungTatCaAmThanh();
	void tiepTucTatCaAmThanh();
	void capNhat(); // Cap nhat, xoa cac am thanh da phat xong
};

// Bien am thanh toan cuc de goi tu nhieu file khac nhau
extern QLAmThanh amThanh;
