#include "QLAmThanh.h"
#include <bits/stdc++.h>
using namespace std;
using namespace sf;

QLAmThanh amThanh;

void QLAmThanh::napAm(const string& ten, const string& duongdan) {
    SoundBuffer buffer;
    if (!buffer.loadFromFile(duongdan)) {
        cout << "Khong the tai am thanh: " << duongdan << endl;
        return;
    }
    buffers[ten] = buffer; // Luu buffer vao map
}

void QLAmThanh::phatAm(const string& ten) {
    auto it = buffers.find(ten);
    if (it != buffers.end()) {
        sounds.emplace_back();       // Tao mot am thanh moi
        Sound& s = sounds.back();    // Lay am thanh vua them
        s.setBuffer(it->second);     // Gan buffer tu map
        s.play();                    // Phat am thanh
    }
}

void QLAmThanh::phatNhacNen(const string& duongdan) {
    static Music nhacNen; // Chi co mot nhac nen chay lap lai
    if (!nhacNen.openFromFile(duongdan)) {
        cout << "Khong the tai nhac nen!" << endl;
        return;
    }
    nhacNen.setLoop(true); // Lap vo han
    nhacNen.play();        // Bat dau phat nhac nen
    
}
//Dung am thanh
	void QLAmThanh::dungTatCaAmThanh() {
		for(auto& s : sounds) {
			s.stop();
		}
	} 
void QLAmThanh::capNhat() {
    // Xoa cac am thanh da ket thuc
    sounds.erase(remove_if(sounds.begin(), sounds.end(),
        [](const Sound& s) { return s.getStatus() == Sound::Stopped; }),
        sounds.end());
}

void QLAmThanh::tamDungTatCaAmThanh() {
    for (auto& s : sounds) 
    	if (s.getStatus() == Sound::Playing)
        	s.pause();
        	
    if(nhacNen.getStatus() == Music::Playing)
    	nhacNen.pause();
}

void QLAmThanh::tiepTucTatCaAmThanh() {
    for (auto& s : sounds)
    if (s.getStatus() == Sound::Paused)
        s.play();
        
    if(nhacNen.getStatus()==Music::Paused)
    	nhacNen.play();
}
