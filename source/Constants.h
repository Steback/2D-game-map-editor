#ifndef CONSTANTS_H
#define CONSTANTS_H

const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;

const unsigned int NUM_LAYERS = 7;

const float MAX_WINDOW_GL_WIDTH = 100.0f;
const float MAX_WINDOW_GL_HEIGHT = 60.0f;

enum LayerType {
    TILEMAP_LAYER = 0,
    VEGETATION_LAYER = 1,
    ENEMY_LAYER = 2,
    OBSTACLE_LAYER = 3,
    PLAYER_LAYER = 4,
    PROJECTILE_LAYER = 5,
    UI_LAYER = 6
};

enum CollisionType {
    NO_COLLISION,
    PLAYER_ENEMY_COLLISION,
    PLAYER_PROJECTILE_COLLISION,
    ENEMY_PROJECTILE_COLLISION,
    PLAYER_VEGETATION_COLLIDER,
    PLAYER_LEVEL_COMPLETE_COLLISION
};

#endif