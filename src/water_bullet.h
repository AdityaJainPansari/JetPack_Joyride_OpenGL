#include "main.h"

#ifndef WATER_BULLET_H
#define WATER_BULLET_H


class Water_Bullet {
public:
    Water_Bullet() {}
    Water_Bullet(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int collisions;
    // bool visible;
    bounding_box_t box;
    // bool base();
    // bool roof();
    // bool frontwall();
    // bool backwall();
    // void jump();
    void motion();
private:
    VAO *object1;
    VAO *object2;
};

#endif // WATER_BULLET_H
