#include "main.h"

#ifndef DRAGON_H
#define DRAGON_H


class Dragon {
public:
    Dragon() {}
    Dragon(float x, float y, color_t color);
    glm::vec3 position;
    // glm::vec3 velocity;
    // glm::vec3 acceleration;
    float rotation;
    int score;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    // bool base();
    // bool roof();
    bounding_box_t box;
    // bool frontwall();
    // bool backwall();
    // void jump();
    // bool motion(bool magnet,int sign,bool safe,float ring_x);
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
};

#endif // DRAGON_H
