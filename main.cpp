#include <SFML/Graphics.hpp>
#include <conio.h>
using namespace sf;

// map  ? x ? : 1 ô = ? bit

// --------------------------------1-------------------------------------
      /*
            -Class : Player (co animation don gian)
            - sd tính ké thua, da hinh (CLO2)
      */

//---------------------------------2-------------------------------------
      /*
            -Class : Enermy (2 -> 3 loai quai) (co animation don gian )
            - sd tính ké thua, da hinh (CLO2)
      */
   
//---------------------------------3------------------------------------
      /*
            -Class : Bomb, Wall
            -sd (set, map, queue,...) quan ly dan, diem so (CLO3)
            - Vao ra file (map, cau hinh), ngoai le (CLO4)
      */


class Character{
	public:
		int x, y;
		int c1, c2, c3, c4;
		int r;
		int health;
		int speed;
		Texture playerTexture;
		Sprite playerSprite;
};

class Player : public Character{
	public:
	Player(){
		// chi so co ban
		x = 100;
		y = 100;
		r = 30;
		speed = 1.f;
		// xbox
		c1 = x - r;
		c2 = y - r;
		c3 = x + r;
		c4 = y + r;
		// set hinh anh
        playerTexture.loadFromFile("assets/wtf.png");
		playerSprite.setTexture(playerTexture);
		playerSprite.setPosition(100.f, 100.f);
	}
	
	void move(int dx, int dy){
		x += dx*speed;
		y += dy*speed;
		c1 = x - r;
		c2 = y - r;
		c3 = x + r;
		c4 = y + r;
		playerSprite.setPosition(x, y);
	}
	
	void player_input(){
		if(Keyboard::isKeyPressed(Keyboard::Up)){move(0, -1);}
		else if(Keyboard::isKeyPressed(Keyboard::Down)){move(0, 1);}
		else if(Keyboard::isKeyPressed(Keyboard::Right)){move(1, 0);}
		else if(Keyboard::isKeyPressed(Keyboard::Left)){move(-1, 0);}
	}
	
	void die(){}
	
	void take_damge(){
	    health--;
		if(health == 0){}
		}
	
	void bomb(){}
	
	void draw_player(RenderWindow &window){
		window.draw(playerSprite);
	}
};

int main(){
	
	RenderWindow window(VideoMode(800, 600), "Muslim");
	
	Player a;
	
	while(window.isOpen()){
		//-------------------------------UPDATE---------------------------------------------------------
		Event event;
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{window.close();}
			
		}
	    a.player_input();
		//-------------------------------Draw------------------------------------------------------------
		window.clear();
		a.draw_player(window);
		window.display();
		
	}
	return 0;
}
