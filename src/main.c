#include "defs.h"
#include <raylib.h>

static GameState state = MENU;
static size_t score = 0;

void bulletMove(Bullet *bullet){
    if(bullet->type == PLAYER){
        bullet->base.pos.y -= bulletVelocity * GetFrameTime();
    } else {
        bullet->base.pos.y += bulletVelocity * GetFrameTime();
    }
}

void bulletRender(){
    for(size_t i = 0; i < bullets.size; i++){
        DrawRectangle(bullets.items[i].base.pos.x, bullets.items[i].base.pos.y, bullets.items[i].base.size.x, bullets.items[i].base.size.y, WHITE);
        bulletMove(&bullets.items[i]);
        if(bullets.items[i].base.pos.y < 0){
            da_remove(&bullets, i);
        }
    }
}

bool checkCollision(GameObject *obj1, GameObject *obj2) {
    if(obj1->pos.x >= obj2->pos.x + obj2->size.x ||
       obj1->pos.x + obj1->size.x <= obj2->pos.x ||
       obj1->pos.y >= obj2->pos.y + obj2->size.y ||
       obj1->pos.y + obj1->size.y <= obj2->pos.y) {
        return false;
    }
    return true;
}

void gameOver(){
    state = END;
}

// detect collision between player and enemy or enemy bullet and player bullet
void detectCollision(Player player){
    for(size_t i = 0; i < enemies.size; i++){
        if(enemies.items[i].active){
            for(size_t j = 0; j < bullets.size; j++){
                if(bullets.items[j].type == PLAYER){
                    if(checkCollision(&enemies.items[i].base, &bullets.items[j].base)){
                        if (enemies.items[i].type == ENEMY_RED){
                            score += 10;
                        } else if(enemies.items[i].type == ENEMY_GREEN){
                            score += 20;
                        } else {
                            score += 30;
                        }
                        enemies.items[i].active = false;
                        enemies.actives--;
                        da_remove(&bullets, j);
                    }
                }
                if(bullets.items[j].type == ENEMY){
                    if(checkCollision(&player.base, &bullets.items[j].base)){
                        da_remove(&bullets, j);
                        gameOver();
                    }
                }
                if(checkCollision(&player.base, &enemies.items[i].base)){
                    gameOver();
                }
            }
        }
    }
}


BulletArray bullets = {NULL, 0, 0};

void DrawScore(){
    DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
}

void menu(){
    Color bg = {18, 18, 18, 255};
    ClearBackground(bg);
    DrawText("Space invaders", screenWidth/2 - MeasureText("Space invaders", 50)/2, screenHeight/2 - 100, 50, WHITE);
    DrawText("Press enter to start", screenWidth/2 - MeasureText("Press enter to start", 20)/2, screenHeight/2, 20, WHITE);
}

int main(void){
    srand(time(NULL));
    InitWindow(screenWidth, screenHeight, "Space invaders");
    SetTargetFPS(60);
    Player player = spwanPlayer();
    Color bg = {18, 18, 18, 255};
    InitAudioDevice();
    Music music = LoadMusicStream("assets/main.mp3");
    if(IsMusicReady(music))
        PlayMusicStream(music);
    Sound shooting = LoadSound("assets/alienshoot1.wav");
    SetSoundVolume(shooting, 0.4f);
    initEnemies();
    while(!WindowShouldClose()){
        BeginDrawing();
        UpdateMusicStream(music);
        if(state == MENU){
            menu();
            if(IsKeyPressed(KEY_ENTER)){
                state = GAME;
            }
            EndDrawing();
            continue;
        }

        if (state == END || state == WIN){
            if(IsKeyPressed(KEY_ENTER)){
                state = GAME;
                enemies.size = 0;
                enemies.actives = 0;
                score = 0;
                player = spwanPlayer();
                initEnemies();
                bullets.size = 0;
            }
        }
        if(state == WIN){
            ClearBackground(bg);
            DrawText("YOU WIN", screenWidth/2 - MeasureText("YOU WIN", 50)/2, screenHeight/2 - 50, 50, WHITE);
            DrawText("Press enter to restart", screenWidth/2 - MeasureText("Press enter to restart", 20)/2, screenHeight/2, 20, WHITE);
            EndDrawing();
            continue;
        }

        if(state == END){
            ClearBackground(bg);
            DrawText("GAME OVER", screenWidth/2 - MeasureText("GAME OVER", 50)/2, screenHeight/2 - 50, 50, WHITE);
            DrawText("Press enter to restart", screenWidth/2 - MeasureText("Press enter to restart", 20)/2, screenHeight/2, 20, WHITE);
            EndDrawing();
            continue;
        }
        ClearBackground(bg);
        renderEnemies();
        renderGameObject(&player.base);
        movePlayer(&player);
        if(IsKeyPressed(KEY_SPACE)){
            playerShoot(&player);
            PlaySound(shooting);
        }
        for(size_t i = 0; i < enemies.size; i++){
            if(enemies.items[i].active){
                if(rand() % 800 == 0){
                    enemyShoot(&enemies.items[i]);
                }
            }
        }
        if(score == 800)
            state = WIN;
        detectCollision(player);
        enemyPattern();
        bulletRender();
        DrawScore();
        EndDrawing();

    }
    CloseWindow();
    return 0;
}
