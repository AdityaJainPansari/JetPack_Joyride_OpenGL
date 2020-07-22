#include "dragon_bullet.h"
#include "main.h"

Dragon_Bullet::Dragon_Bullet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->velocity = glm::vec3(-(0.3/10), 0, 0);
    // this->acceleration = glm::vec3(0,0,0);
    this->rotation = 0;
    this->box.x=x;
    this->box.y=y;
    this->box.width=0.40f;
    this->box.height=0.40f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    int n = 100;
	GLfloat vertex_buffer_data0[1000];
	int k = 0;
	for(int i = 0;i<n;i++)
	{
		vertex_buffer_data0[k++] = 0.0f;
		vertex_buffer_data0[k++] = 0.0f;
		vertex_buffer_data0[k++] = 0.0f;

		vertex_buffer_data0[k++] = 0.0f + (sin(2*M_PI/n*i)/8.0);
		vertex_buffer_data0[k++] = 0.0f + (cos(2*M_PI/n*i)/8.0);
		vertex_buffer_data0[k++] = 0.0f;

		vertex_buffer_data0[k++] = 0.0f + (sin(2*M_PI/n*(i+1))/8.0);
		vertex_buffer_data0[k++] = 0.0f + (cos(2*M_PI/n*(i+1))/8.0);
		vertex_buffer_data0[k++] = 0.0f;
	}
    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data0, COLOR_FIRE, GL_FILL);
}

void Dragon_Bullet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Dragon_Bullet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Dragon_Bullet::tick() {
    this->motion();
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    // this->position.x -= speed;
    // this->position.y += speed/100;
}

void Dragon_Bullet::motion() {
    this->position += this->velocity;//+this->acceleration*glm::vec3(0.5,0.5,0.5);
}