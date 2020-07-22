#include "main.h"

#ifndef DRAGON_BULLET_H
#define DRAGON_BULLET_H


class Dragon_Bullet {
public:
    Dragon_Bullet() {}
    Dragon_Bullet(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 velocity;
    // glm::vec3 acceleration;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    // int collisions;
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

#endif // DRAGON_BULLET_H
