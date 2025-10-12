#include "Enemy3.h"

Enemy3::Enemy3(float x_, float y_) : Enemy(x_, y_) {
    SPRITE.setTexture(TEXTURES[2]);
    tocDo = 2.5f; // nhanh hon Enemy2
}

