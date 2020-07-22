#include "main.h"

#ifndef FLOOR_H
#define FLOOR_H


class Floor {
public:
    Floor() {}
    Floor(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 velocity;
    // glm::vec3 acceleration;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    // bool base();
    // bool roof();
    // bool frontwall();
    // bool backwall();
    // void jump();
    void motion();
private:
    VAO *object;
};

#endif // FLOOR_H
