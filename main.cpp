#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Player{
	private:
	sf::Texture P_tt;
	sf::Sprite P_sp;	
	int health;
	int x, y;
	bool alive;
	
	public:
		Player(){
		  health = 3;
		  x = 0; y = 0;
		  alive  = true;
		  P_tt.loadFromFile("C:\Users\OS\OneDrive\Pictures\Screenshots\hero.png");
		sprite.setTexture(texture);    
        sprite.setPosition(x, y);   
		};
		
	  void	move(int dx, int dy){
	  	x+=dx;
	  	y+=dy;
	  	if(alive == true){sprite.move(dx,dy);}
	  	else{}
	  }
	  
	  void die(){
	  	alive = false;
	  }
	  
	  void take_damge(){
	  	health--;
	  	if(health == 0){die();}
	  }
	  void draw(sf::RenderWindow &window) {
        window.draw(sprite);
    }
	  
	  
};

int main(){
	  sf::RenderWindow window(sf::VideoMode(800, 600), "My Game");
	
	Player Nam;
	while(1){
		int ch = getch();
		if(ch == 'a'){Nam.move(-30, 0);}
		else if(ch == 'd'){Nam.move(30, 0);}
		else if(ch ==  's'){Nam.move(0,30);}
		else if(ch == 'w'){Nam.move(0,-30);}
	}
	getch();
	
}
