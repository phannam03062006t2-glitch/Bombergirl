#include "Enemy1.h"

Enemy1::Enemy1(float x_, float y_) : Enemy(x_, y_, 0) {  // thêm type = 0
    SPRITE.setTexture(TEXTURES[0]);
    tocDo = 1.0f;
}
