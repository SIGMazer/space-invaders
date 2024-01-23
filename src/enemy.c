#include "defs.h"


// 1 row yellow, 2 row green, 3 row red, 8 columns
EnemyArray enemies = {NULL, 0, 0, 0};
static Image red = {0};
static Image green = {0};
static Image yellow = {0};

// TODO add extra enemy types
void initEnemies() {
    size_t col = 8;
    size_t row = 6;
    red = (red.data == NULL) ? LoadImage("assets/red.png") : red;
    green = (green.data == NULL) ? LoadImage("assets/green.png") : green;
    yellow = (yellow.data == NULL) ? LoadImage("assets/yellow.png") : yellow;

    for(size_t i = 0; i < row; i++) {
        for(size_t j = 0; j < col; j++) {
            if(i == 0){
                GameObject enemyObj = spawnGameObject((Vector2){j * 50 + 50, i * 50 + 50}, (Vector2){75, 75}, LoadTextureFromImage(yellow));
                Enemy enemy = {enemyObj, true, ENEMY_YELLOW};
                da_append(&enemies, enemy);
            } else if(i == 1 || i == 2) {
                GameObject enemyObj = spawnGameObject((Vector2){j * 50 + 50, i * 50 + 50}, (Vector2){75, 75}, LoadTextureFromImage(green));
                Enemy enemy = {enemyObj, true, ENEMY_GREEN};
                da_append(&enemies, enemy);
            } else {
                GameObject enemyObj = spawnGameObject((Vector2){j * 50 + 50, i * 50 + 50}, (Vector2){75, 75}, LoadTextureFromImage(red));
                Enemy enemy = {enemyObj, true, ENEMY_RED};
                da_append(&enemies, enemy);
            }
            enemies.actives++;
        }
    }
}

void renderEnemies() {
    for(size_t i = 0; i < enemies.size; i++) {
        if(enemies.items[i].active) {
            renderGameObject(&enemies.items[i].base);
        }
    }
}

void enemyPattern() {
    size_t width = GetScreenWidth();
    float baseEnemyVelocity = 100;
    float enemyVelocity = baseEnemyVelocity;
    if(enemies.size > 0 && enemies.actives > 0){
        enemyVelocity = baseEnemyVelocity + (enemies.size - enemies.actives) * 8;
    }
    static bool moveRight = true;

    for(size_t i = 0; i < enemies.size; i++) {
        if(enemies.items[i].active){

            enemies.items[i].base.pos.x += (moveRight ? 1 : -1) *enemyVelocity * GetFrameTime();

            if(enemies.items[i].base.pos.x >= width - enemies.items[i].base.size.x ||
                    enemies.items[i].base.pos.x <= 0) {
                moveRight = !moveRight;

                for(size_t j = 0; j < enemies.size; j++) {
                    if(enemies.items[j].active) {
                        enemies.items[j].base.pos.y += 10;
                    }
                }
            }
        }
    }
}
static RenderTexture2D bulletTexture = {0};
void enemyBullet(){
    bulletTexture = LoadRenderTexture(5, 10);
    BeginTextureMode(bulletTexture);
    ClearBackground(GREEN);
    EndTextureMode();
}

void enemyShoot(Enemy *enemy){

    if(bulletTexture.texture.id == 0){
        enemyBullet();
    }

    Bullet bullet = {
        .base ={
            .pos = (Vector2){enemy->base.pos.x + enemy->base.size.x/2, enemy->base.pos.y},
            .size = (Vector2){5, 10},
            .texture = bulletTexture.texture,
        },
        ENEMY
    };
    da_append(&bullets, bullet);
}
