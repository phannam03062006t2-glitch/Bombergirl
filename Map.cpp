#include "Map.h"
#include<bits/stdc++.h>
using namespace std;
Map::Map():hang(0),cot(0) {}

void Map::napFile(const string& tenfile) {
	ifstream fin(tenfile);
	if(!fin) throw runtime_error("Khong mo duoc file map!");
	
	fin>>hang>>cot;
	for(int i=0; i<hang;i++) {
		for(int j=0;j<cot;j++) {
			int loai;
			fin>>loai;
			if(loai==1) {
				ds_tuong[{i,j}]=Wall(Vector2f(j*64,i*64), true,"wall.png");
			} else if(loai==2) {
				ds_tuong[{i,j}] = Wall(Vector2f(j*64, i*64),false, "wall2.png");
			}
		}
	}
	fin.close();
}

void Map::ve(RenderWindow& cua_so) {
	for(auto& t : ds_tuong) {
		t.second.ve(cua_so);
	}
}
map<pair<int,int>, Wall>& Map::layDanhSach() {return ds_tuong; }
