#ifndef DEFS_H
#define DEFS_H

#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

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

// game object
GameObject spawnGameObject(Vector2 pos, Vector2 size, Texture2D texture);
void moveGameObject(GameObject *gameObject, Vector2 velocity);
void renderGameObject(GameObject *gameObject);

extern BulletArray bullets;

#endif // DEFS_H

