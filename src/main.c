#include "defs.h"



Player spwanPlayer(){
    Image playerImage = LoadImage("assets/player.png");
    Texture2D playerTexture = LoadTextureFromImage(playerImage);
    GameObject playerObject = spawnGameObject((Vector2){screenWidth/2.0, screenHeight - 50}, (Vector2){50, 50}, playerTexture);
    Player player = {
        playerObject,
        PLAYER
    };

    return player;
}

void movePlayer(Player *player){
    float dt = GetFrameTime();
    if(IsKeyDown(KEY_A)){
        player->base.pos.x -= playerVelocity*dt; 
    }
    if(IsKeyDown(KEY_D)){
        player->base.pos.x += playerVelocity*dt; 
    }
}


#define DA_INIT_CAPACITY 4
#define da_append(arr, item) do{\
    if((arr)->size == (arr)->capacity){\
        (arr)->capacity = ((arr)->capacity == 0)? DA_INIT_CAPACITY : (arr)->capacity*2;\
        (arr)->items = realloc((arr)->items, sizeof(*(arr)->items) * (arr)->capacity);\
    }\
    (arr)->items[(arr)->size++] = (item);\
}while(0) 

#define da_remove(arr, index) do{\
    if((index) < (arr)->size){\
        (arr)->items[(index)] = (arr)->items[--(arr)->size];\
    }\
    for(size_t i = (index); i < (arr)->size; i++){\
        (arr)->items[i] = (arr)->items[i+1];\
    }\
}while(0)



void playerShoot(Player *player){
    Texture2D bulletTexture = {0};
    Rectangle bulletRect = (Rectangle){player->base.pos.x + player->base.size.x/2, player->base.pos.y, 5, 10};
    SetShapesTexture(bulletTexture, bulletRect);

    Bullet bullet = {
        .pos = (Vector2){player->base.pos.x + player->base.size.x/2, player->base.pos.y},
        .size = (Vector2){5, 10},
        .texture = bulletTexture,
    };
    da_append(&bullets, bullet);
} 

void bulletMove(Bullet *bullet){
    bullet->pos.y -= bulletVelocity*GetFrameTime();
}
void bulletRender(){
    for(size_t i = 0; i < bullets.size; i++){
        DrawRectangle(bullets.items[i].pos.x, bullets.items[i].pos.y, bullets.items[i].size.x, bullets.items[i].size.y, WHITE);
        bulletMove(&bullets.items[i]);
        if(bullets.items[i].pos.y < 0){
            da_remove(&bullets, i);
        }
    }
}


BulletArray bullets = {NULL, 0, 0};

int main(void){
    InitWindow(screenWidth, screenHeight, "space invaders");
    SetTargetFPS(60);
    Player player = spwanPlayer();
    Color bg = {18, 18, 18, 255};
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(bg);
        DrawTexture(player.base.texture, player.base.pos.x, player.base.pos.y, WHITE);
        movePlayer(&player);
        if(IsKeyPressed(KEY_SPACE)){
            playerShoot(&player);
        }
        bulletRender();
        EndDrawing();
    }
    return 0;
}
