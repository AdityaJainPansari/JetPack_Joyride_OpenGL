#include "safe_ring.h"
#include "main.h"

Safe_Ring::Safe_Ring(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->velocity = glm::vec3(-(3.0/100), 0, 0);
    // this->rotation = 0;
    this->box.x = x-0.9f;
    this->box.y = y+(0.65/2.0);
    this->box.width = 0.2f;
    this->box.height = 0.65f;
    this->using_rn = false;
    // this->collision = false;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static  GLfloat vertex_buffer_data1[] = {

        -1.0f,.65f,.2f,
        -1.0f,.0f,.2f,
        -.8f,.65f,.2f,
        
        -1.0f,.0f, .2f,
        -.8f,.0f, .2f,
        -.8f,.65f,.2f,
    };

    int n = 100;
	GLfloat vertex_buffer_data0[1000];
	int k = 0;
	for(int i = 0;i<(n/4);i++)
	{
		vertex_buffer_data0[k++] = 5.0f;
		vertex_buffer_data0[k++] = 0.0f;
		vertex_buffer_data0[k++] = -0.4f;

		vertex_buffer_data0[k++] = 5.0f + (5)*(sin(2*M_PI/n*i));
		vertex_buffer_data0[k++] = 0.0f + (5)*(cos(2*M_PI/n*i));
		vertex_buffer_data0[k++] = -0.4f;

		vertex_buffer_data0[k++] = 5.0f + (5)*(sin(2*M_PI/n*(i+1)));
		vertex_buffer_data0[k++] = 0.0f + (5)*(cos(2*M_PI/n*(i+1)));
		vertex_buffer_data0[k++] = -0.4f;
	}
	for(int i = 3*(n/4);i<=n;i++)
	{
		vertex_buffer_data0[k++] = 5.0f;
		vertex_buffer_data0[k++] = 0.0f;
		vertex_buffer_data0[k++] = -0.4f;

		vertex_buffer_data0[k++] = 5.0f + (5)*(sin(2*M_PI/n*i));
		vertex_buffer_data0[k++] = 0.0f + (5)*(cos(2*M_PI/n*i));
		vertex_buffer_data0[k++] = -0.4f;

		vertex_buffer_data0[k++] = 5.0f + (5)*(sin(2*M_PI/n*(i+1)));
		vertex_buffer_data0[k++] = 0.0f + (5)*(cos(2*M_PI/n*(i+1)));
		vertex_buffer_data0[k++] = -0.4f;
	}
    
	GLfloat vertex_buffer_data2[1000];
	k = 0;
	for(int i = 0;i<(n/4);i++)
	{
		vertex_buffer_data2[k++] = 5.0f;
		vertex_buffer_data2[k++] = 0.0f;
		vertex_buffer_data2[k++] = -0.5f;

		vertex_buffer_data2[k++] = 5.0f + (6)*(sin(2*M_PI/n*i));
		vertex_buffer_data2[k++] = 0.0f + (6)*(cos(2*M_PI/n*i));
		vertex_buffer_data2[k++] = -0.5f;

		vertex_buffer_data2[k++] = 5.0f + (6)*(sin(2*M_PI/n*(i+1)));
		vertex_buffer_data2[k++] = 0.0f + (6)*(cos(2*M_PI/n*(i+1)));
		vertex_buffer_data2[k++] = -0.5f;
	}
	for(int i = 3*(n/4);i<=n;i++)
	{
		vertex_buffer_data2[k++] = 5.0f;
		vertex_buffer_data2[k++] = 0.0f;
		vertex_buffer_data2[k++] = -0.5f;

		vertex_buffer_data2[k++] = 5.0f + (6)*(sin(2*M_PI/n*i));
		vertex_buffer_data2[k++] = 0.0f + (6)*(cos(2*M_PI/n*i));
		vertex_buffer_data2[k++] = -0.5f;

		vertex_buffer_data2[k++] = 5.0f + (6)*(sin(2*M_PI/n*(i+1)));
		vertex_buffer_data2[k++] = 0.0f + (6)*(cos(2*M_PI/n*(i+1)));
		vertex_buffer_data2[k++] = -0.5f;
	}
    
    // for(int i=0; i<18 ; i++)
    // {
    //     if(i%3==2)
    //     {
    //         vertex_buffer_data1[i]-=.1;
    //     }
    //     vertex_buffer_data1[i]/=2.5;
    // }

    this->object0 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data0, COLOR_BACKGROUND, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, k/3, vertex_buffer_data2, COLOR_GREEN, GL_FILL);
}

void Safe_Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    // Matrices.model *= (translate * rotate);
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object1);
    draw3DObject(this->object0);
}

void Safe_Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Safe_Ring::tick() {
    this->motion();
    this->box.x=this->position.x;
}

void Safe_Ring::motion() {
    this->position.x+=this->velocity.x;//+this->acceleration.x*(0.5);
    this->velocity.x=-(3.0/100);//+=this->acceleration.x;
}
/*
void Safe_Ring::tick() {
    // this->motion();
    // this->box.x=this->position.x;
    // this->box.y=this->position.y;
    // this->rotation += this->angular_velocity;
    // this->position.x -= speed;
    // this->position.y += speed/100;
}

void Safe_Ring::motion() {
    // // this->position.x += this->velocity.x;//+this->acceleration*glm::vec3(0.5,0.5,0.5);
    // // this->velocity += this->acceleration;
    // float temp = ((this->position.x-(WALL*3))/(WALL*3));
    // if(temp >= 1 || temp <= (-1))
    // {
    //     temp=1;
    // }
    // // std::cout << this->position.x << "  " << this->position.y << "  " << temp << std::endl;
    // this->position.y= sqrt((2.5*2.5)*(1-(temp*temp)));
    // if(this->velocity.x>=0)
    //     this->position.y *= (-1);
    // if(this->position.y==0)
    // {
    //     this->velocity.x *= (-1);
    // }
}

*/