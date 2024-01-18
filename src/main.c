#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

const size_t screenWidth = 800;
const size_t screenHeight = 600;
const size_t playerVelocity = 200;
const size_t bulletVelocity = 400;

typedef struct Player{
    Vector2 pos;
    Vector2 size;
    Texture2D texture;
} Player;

typedef struct Bullet{
    Vector2 pos;
    Vector2 size;
    Rectangle rect;
} Bullet;

typedef struct {
    Bullet *items;
    size_t size;
    size_t capacity;
} BulletArray;

Player spwanPlayer(){
    Image playerImage = LoadImage("assets/player.png");
    Texture2D playerTexture = LoadTextureFromImage(playerImage);
    Player player = {
        (Vector2){(float)screenWidth/2.0, screenHeight - playerTexture.height*2},
        (Vector2){playerTexture.width, playerTexture.height},
        playerTexture
    };
    return player;
}

void movePlayer(Player *player){
    float dt = GetFrameTime();
    if(IsKeyDown(KEY_A)){
        player->pos.x -= playerVelocity*dt; 
    }
    if(IsKeyDown(KEY_D)){
        player->pos.x += playerVelocity*dt;
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

BulletArray bullets = {0};


void playerShoot(Player *player){
    Bullet bullet = {
        (Vector2){player->pos.x + player->size.x/2, player->pos.y},
        (Vector2){5, 10},
        (Rectangle){player->pos.x + player->size.x/2, player->pos.y, 5, 10}
    };
    da_append(&bullets, bullet);
} 

void bulletMove(Bullet *bullet){
    bullet->pos.y -= bulletVelocity*GetFrameTime();
    bullet->rect.y -= bulletVelocity*GetFrameTime();
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


int main(void){
    
    InitWindow(screenWidth, screenHeight, "space invaders");
    SetTargetFPS(60);
    Player player = spwanPlayer();
    Color bg = {18, 18, 18, 255};
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(bg);
        DrawTexture(player.texture, player.pos.x, player.pos.y, WHITE);
        movePlayer(&player);
        if(IsKeyPressed(KEY_SPACE)){
            playerShoot(&player);
        }
        bulletRender();
        EndDrawing();
    }
    return 0;
}
