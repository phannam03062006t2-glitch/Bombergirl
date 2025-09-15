#include <SFML/Graphics.hpp>
#include <conio.h>
#include <iostream>
#include <fstream>
using namespace sf;
using namespace std;

// map  ? x ? : 1 ô = ? bit

// --------------------------------1-------------------------------------
      /*
            -Class : Player (có animation đơn giản)
            - Sử dụng tính kế thừa, đa hình (CLO2)
      */

//---------------------------------2-------------------------------------
      /*
            - Class : Enermy (2 -> 3 loại quái) (có animation đơn giản )
            - Sử dụng tính kế thừa, đa hình (CLO2)
      */
   
//---------------------------------3------------------------------------
      /*
            - Class : Bomb, Wall
            - Sử dụng (set, map, queue,...) quản lý đạn, điểm số (CLO3)
            - Vào ra file (map, cau hình), ngoại lệ (CLO4)
      */

int main(){
	// tạo màn hình window
	RenderWindow window(VideoMode(800, 600), "Muslim");
	
	while(window.isOpen()){
		//-------------------------------Sự kiện---------------------------------------------------------
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{window.close();}
			
		}
	    //------------------------------Cập nhập --------------------------------------------------------

		
		
		//-------------------------------Vẽ------------------------------------------------------------
		window.clear();
		window.display();
		
	}
	return 0;
}



