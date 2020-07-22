#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H


class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y, color_t color, float rotation);
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float rotation;
    float angular_velocity;
    float axial_rotation;
    float angle;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    // double ret_tan();
    void tick();
    bool visible;
    bool collision;
    bounding_box_t box;
    // bool base();
    // bool roof();
    // bool frontwall();
    // bool backwall();
    // void jump();
    void motion();
private:
    VAO *object0;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // FIREBEAM_H
