#include "defs.h"

GameObject spawnGameObject(Vector2 pos, Vector2 size, Texture2D texture){
    GameObject gameObject = {
        pos,
        size,
        texture
    };
    return gameObject;
}

void moveGameObject(GameObject *gameObject, Vector2 velocity){
    gameObject->pos.x += velocity.x*GetFrameTime();
    gameObject->pos.y += velocity.y*GetFrameTime();
}

void renderGameObject(GameObject *gameObject){
    DrawTexture(gameObject->texture, gameObject->pos.x, gameObject->pos.y, WHITE);
}



