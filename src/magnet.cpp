#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    // this->velocity = glm::vec3(0, 0, 0);
    // this->rotation = 0;
    this->box.x = x;
    this->box.y = y;
    this->box.width = 0.50f;
    this->box.height = 0.50f;
    this->visible = false;
    // this->collision = false;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static  GLfloat vertex_buffer_data1[] = {

        .75f,0.4f,.0f,
        .75f,.0f,.0f,
        .25f,0.4f,.0f,
        
        .75f,.0f, .0f,
        .25f,.0f, .0f,
        .25f,0.4f,.0f,
    };

    static  GLfloat vertex_buffer_data2[] = {

        -.75f,0.4f,.0f,
        -.75f,.0f,.0f,
        -.25f,0.4f,.0f,
        
        -.75f,.0f, .0f,
        -.25f,.0f, .0f,
        -.25f,0.4f,.0f,
    };

    static  GLfloat vertex_buffer_data3[] = {

        .75f,1.0f,.0f,
        .75f,.0f,.0f,
        .25f,1.0f,.0f,
        
        .75f,.0f, .0f,
        .25f,.0f, .0f,
        .25f,1.0f,.0f,
    };

    static  GLfloat vertex_buffer_data4[] = {

        -.75f,1.0f,.0f,
        -.75f,.0f,.0f,
        -.25f,1.0f,.0f,
        
        -.75f,.0f, .0f,
        -.25f,.0f, .0f,
        -.25f,1.0f,.0f,
    };
    
    int n = 100;
	GLfloat vertex_buffer_data0[1000];
	int k = 0;
	for(int i = (n/4)-1;i<=3*(n/4);i++)
	{
		vertex_buffer_data0[k++] = 0.0f;
		vertex_buffer_data0[k++] = 0.0f;
		vertex_buffer_data0[k++] = 0.1f;

		vertex_buffer_data0[k++] = 0.0f + (0.75)*(sin(2*M_PI/n*i));
		vertex_buffer_data0[k++] = 0.0f + (0.75)*(cos(2*M_PI/n*i));
		vertex_buffer_data0[k++] = 0.1f;

		vertex_buffer_data0[k++] = 0.0f + (0.75)*(sin(2*M_PI/n*(i+1)));
		vertex_buffer_data0[k++] = 0.0f + (0.75)*(cos(2*M_PI/n*(i+1)));
		vertex_buffer_data0[k++] = 0.1f;
	}
    
    for(int i=0;i<k;i++)
    {
        vertex_buffer_data0[i]/=2.5;
    }

    for(int i=0; i<18 ; i++)
    {
        if(i%3==1)
        {
            vertex_buffer_data1[i]+=1.0;
            vertex_buffer_data2[i]+=1.0;
        }
        if(i%3==2)
        {
            vertex_buffer_data1[i]-=.1;
            vertex_buffer_data2[i]-=.1;
            vertex_buffer_data3[i]-=.1;
            vertex_buffer_data4[i]-=.1;
        }
        vertex_buffer_data1[i]/=2.5;
        vertex_buffer_data2[i]/=2.5;
        vertex_buffer_data3[i]/=2.5;
        vertex_buffer_data4[i]/=2.5;
    }

    this->object0 = create3DObject(GL_TRIANGLES, ((3*(n/4))-((n/4)-1)+1)*3, vertex_buffer_data0, COLOR_MAGNET, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_BLUE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_MAGNET, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, COLOR_MAGNET, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object0);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::tick() {
    // this->motion();
    // this->box.x=this->position.x;
    // this->box.y=this->position.y;
    // this->rotation += this->angular_velocity;
    // this->position.x -= speed;
    // this->position.y += speed/100;
}

void Magnet::motion() {
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