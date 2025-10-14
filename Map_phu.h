#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;


class Wall{
   public:
     float x, y;
	static Texture TEXTURE;
	 Sprite SPRITE;
	Wall(float x, float y);	
	void Ve(RenderWindow &window);
};

class Wall2 : public Wall{
	public:
		static Texture TEXTURE;
		Wall2(float x, float y) : Wall(x, y){
			TEXTURE.loadFromFile("assets/wall2.png");
	         SPRITE.setTexture(TEXTURE);
		}
};

void input_map();
void veWall(RenderWindow &window);
