#include "Enemy2.h"

Enemy2::Enemy2(float x_, float y_) : Enemy(x_, y_) {
    SPRITE.setTexture(TEXTURES[1]);
    tocDo = 2.0f; // nhanh hon Enemy1
}

