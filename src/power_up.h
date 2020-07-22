#include "main.h"

#ifndef POWER_UP_H
#define POWER_UP_H


class Power_Up {
public:
    Power_Up() {}
    Power_Up(float x, float y, color_t color, int type);
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    int type;
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

#endif // POWER_UP_H
