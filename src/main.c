#include "defs.h"

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
