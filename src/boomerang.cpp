#include "boomerang.h"
#include "main.h"

Boomerang::Boomerang(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->velocity = glm::vec3(-(1.0/10), 0, 0);
    this->rotation = 0;
    this->box.x = x;
    this->box.y = y;
    this->box.width = 0.50f;
    this->box.height = 0.50f;
    this->collision = false;
    this->angular_velocity = 5;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat vertex_buffer_data1[] = {

        .40f, .40f,.0f,
        -.40f,-.40f,.0f,
        -.40f, .40f,.0f, 
    };
    GLfloat vertex_buffer_data3[] = {

        .40f, .40f,.0f,
        .20f, .20f,.0f,
        .20f, .40f,.0f, 
    };
    GLfloat vertex_buffer_data4[] = {

        -.20f, -.20f,.0f,
        -.40f,-.40f,.0f,
        -.40f, -.20f,.0f, 
    };
    GLfloat vertex_buffer_data2[] = {
        
        .35f, .35f, .0f,
        -.35f,-.35f, .0f,
        -.20f,.20f,.0f,
        
    };
    for(int i=0; i<9 ; i++)
    {
        vertex_buffer_data1[i]/=1.5;
        vertex_buffer_data3[i]/=1.5;
        vertex_buffer_data4[i]/=1.5;
        vertex_buffer_data2[i]/=1.5;
    }

    this->object1 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data1, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data3, COLOR_BROWN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data4, COLOR_BROWN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data2, COLOR_BACKGROUND, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object2);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {
    this->motion();
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    this->rotation += this->angular_velocity;
    // this->position.x -= speed;
    // this->position.y += speed/100;
}

void Boomerang::motion() {
    this->position.x += this->velocity.x;//+this->acceleration*glm::vec3(0.5,0.5,0.5);
    // this->velocity += this->acceleration;
    float temp = ((this->position.x-(WALL*3))/(WALL*3));
    if(temp >= 1 || temp <= (-1))
    {
        temp=1;
    }
    // std::cout << this->position.x << "  " << this->position.y << "  " << temp << std::endl;
    this->position.y= sqrt((2.5*2.5)*(1-(temp*temp)));
    if(this->velocity.x>=0)
        this->position.y *= (-1);
    if(this->position.y==0)
    {
        this->velocity.x *= (-1);
    }
}