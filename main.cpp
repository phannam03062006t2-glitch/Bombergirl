#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
using namespace sf;
using namespace std;

// map  ? x ? : 1 ô = ? bit

// --------------------------------1-------------------------------------
      /*
            - Class : Player (có animation đơn giản)
            - Sử dụng tính kế thừa, đa hình (CLO2)
      */

//---------------------------------2-------------------------------------
      /*
            - Class : Enermy (2 -> 3 loại quái) (có animation đơn giản)
            - Sử dụng tính kế thừa, đa hình (CLO2)
      */
   
//---------------------------------3------------------------------------
      /*
            - Class : Bomb, Wall
            - Sử dụng (set, map, queue,...) quản lý bomb, điểm số (CLO3)
            - Vào ra file (map, cấu hình), ngoại lệ (CLO4)
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

