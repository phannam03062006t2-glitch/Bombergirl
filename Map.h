#ifndef MAP_H
#define MAP_H
#include<SFML/Graphics.hpp>
#include<map>
#include "Wall.h"
using namespace std;
using namespace sf;

class Map{
	private:
		map<pair<int,int>, Wall> ds_tuong;
		int hang, cot;
		
	public:
		Map();
		void napFile(const string& tenFile);
		void ve(RenderWindow& cua_so);
		map<pair<int,int>, Wall>& layDanhSach();
};

#endif

