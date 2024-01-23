#ifndef DEFS_H
#define DEFS_H

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <raymath.h>
#include <time.h>

#define screenWidth  800
#define screenHeight  600
#define playerVelocity  200
#define bulletVelocity  400


typedef enum {
    PLAYER,
    ENEMY,
} ObjectType;

typedef enum {
    ENEMY_RED,
    ENEMY_GREEN,
    ENEMY_YELLOW,
} EnemyType;

typedef enum {
    MENU,
    GAME,
    END,
    WIN,
} GameState;

typedef struct {
    Vector2 pos;
    Vector2 size;
    Texture2D texture;
} GameObject;

typedef struct Player{
    GameObject base;
} Player;

typedef struct {
    GameObject base;
    bool active;
    EnemyType type;
} Enemy;

typedef struct {
    Enemy *items;
    size_t size;
    size_t capacity;
    size_t actives;
} EnemyArray;

typedef struct {
    GameObject base;
    ObjectType type;
} Bullet;

typedef struct {
    Bullet *items;
    size_t size;
    size_t capacity;
} BulletArray;

// dynamic array
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


// game object
GameObject spawnGameObject(Vector2 pos, Vector2 size, Texture2D texture);
void moveGameObject(GameObject *gameObject, Vector2 direction, float velocity);
void renderGameObject(GameObject *gameObject);

// player
Player spwanPlayer();
void movePlayer(Player *player);
void playerShoot(Player *player);

// Enemy
void initEnemies();
void renderEnemies();
void enemyPattern();
void enemyShoot(Enemy *enemy);

extern BulletArray bullets;
extern EnemyArray enemies;


#endif // DEFS_H

