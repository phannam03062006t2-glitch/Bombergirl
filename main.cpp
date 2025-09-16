#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
using namespace sf;
using namespace std;

// map  ? x ? : 1 ô = ? bit

// --------------------------------1-------------------------------------
      /*
            - Class :Bomb, Player (có animation đơn giản)
            - Sử dụng tính kế thừa, đa hình (CLO2)
			- (set, map, queue,...) quản lý bomb, (CLO3)
      */

//---------------------------------2-------------------------------------
      /*
            - Class : Enermy (2 -> 3 loại quái) (có animation đơn giản)
            - Sử dụng tính kế thừa, đa hình (CLO2)
      */
   
//---------------------------------3------------------------------------
      /*
            - Class : Wall
            - (set, map, queue,...) Tính điểm số (CLO3)
            - Vào ra file (map, cấu hình), tạo map, ngoại lệ (CLO4)
      */

int main(){
	// tạo cửa sổ
	RenderWindow window(VideoMode(800, 600), "Muslim");
	
	Player a;
	
	while(window.isOpen()){
		//-------------------------------Sự kiện---------------------------------------------------------
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{window.close();}
			
		}
	    //------------------------------Cập nhập-------------------------------------------------------

		
		//-------------------------------Vẽ------------------------------------------------------------
		window.clear();
		window.display();
		
	}
	return 0;
}


