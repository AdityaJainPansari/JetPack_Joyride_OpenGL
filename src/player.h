#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player() {}
    Player(float x, float y, color_t color);
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec3 acceleration;
    float rotation;
    int score;
    bool shield;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    bool tick(bool magnet,int sign,bool safe,float ring_x);
    bool base();
    bool roof();
    bounding_box_t box;
    bool frontwall();
    bool backwall();
    void jump();
    bool motion(bool magnet,int sign,bool safe,float ring_x);
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
    VAO *object8;
    VAO *object9;
};

#endif // PLAYER_H
