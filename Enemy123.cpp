#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"

// Enemy1
Enemy1::Enemy1(float x_, float y_) : Enemy(x_, y_, 0) {  // type = 0
    SPRITE.setTexture(TEXTURES[0]);
    tocDo = 1.0f;
}

// Enemy2
Enemy2::Enemy2(float x_, float y_) : Enemy(x_, y_, 1) {  // type = 1
    SPRITE.setTexture(TEXTURES[1]);
    tocDo = 2.0f;
}

// Enemy3
Enemy3::Enemy3(float x_, float y_) : Enemy(x_, y_, 2) {  // type = 2
    SPRITE.setTexture(TEXTURES[2]);
    tocDo = 2.5f;
}
