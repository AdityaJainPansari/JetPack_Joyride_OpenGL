#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float rotation;
    float angular_velocity;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    bool collision;
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
    VAO *object3;
    VAO *object4;
};

#endif // BOOMERANG_H
