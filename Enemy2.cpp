#include "Enemy2.h"

Enemy2::Enemy2(float x_, float y_) : Enemy(x_, y_, 1) {  // thêm type = 1
    SPRITE.setTexture(TEXTURES[1]);
    tocDo = 2.0f;
}
