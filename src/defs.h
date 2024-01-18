#ifndef DEFS_H
#define DEFS_H

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <raymath.h>

#define screenWidth  800
#define screenHeight  600
#define playerVelocity  200
#define bulletVelocity  400

typedef enum {
    PLAYER,
    ENEMY,
} GameObjectType;

typedef struct {
    Vector2 pos;
    Vector2 size;
    Texture2D texture;
} GameObject;

typedef struct Player{
    GameObject base;
    GameObjectType type;
} Player;

typedef GameObject Bullet;

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


extern BulletArray bullets;

#endif // DEFS_H

