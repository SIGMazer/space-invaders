#include "defs.h"

Image playerImage = {0};
static Sound shootingSound = {0};
Player spwanPlayer(){
    playerImage = (playerImage.data == NULL) ? LoadImage("assets/player.png") : playerImage;
    Texture2D playerTexture = LoadTextureFromImage(playerImage);
    GameObject playerObject = spawnGameObject((Vector2){screenWidth/2.0, screenHeight - 50}, (Vector2){50, 50}, playerTexture);
    Player player = {playerObject};

    return player;
}

void movePlayer(Player *player){
    Vector2 direction = {0,0};
    if(IsKeyDown(KEY_A)){
        direction.x = -1;
    }
    if(IsKeyDown(KEY_D)){
        direction.x = 1;
    }

    player->base.pos.x = Clamp(player->base.pos.x, 0, screenWidth - player->base.size.x);

    moveGameObject(&player->base, direction, playerVelocity);
}
static RenderTexture2D bulletTexture = {0};

void playerBullet(){
    bulletTexture = LoadRenderTexture(5, 10);
    BeginTextureMode(bulletTexture);
        ClearBackground(RED);
    EndTextureMode();
}

void playerShoot(Player *player){

    if(bulletTexture.texture.id == 0){
        playerBullet();
    }

    Bullet bullet = {
        .base ={
            .pos = (Vector2){player->base.pos.x + player->base.size.x/2, player->base.pos.y},
            .size = (Vector2){5, 10},
            .texture = bulletTexture.texture,
        },
        PLAYER
    };
    PlaySound(shootingSound);
    da_append(&bullets, bullet);
} 
