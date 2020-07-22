#include "firebeam.h"
#include "main.h"

Firebeam::Firebeam(float x, float y, color_t color, float rotation) {
    this->position = glm::vec3(x, y, 0);
    if(rotation==90)
    {
        this->velocity = glm::vec3(-(3.0/100),(0.1/100), 0);
        this->acceleration = glm::vec3(0,-(this->position.y/200.0),0);
    }
    else
    {
        this->velocity = glm::vec3(-(3.0/100), 0, 0);
        this->acceleration = glm::vec3(0,0,0);
    }
    this->rotation = rotation;//(static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*2;
    this->axial_rotation = 0;//(static_cast <float> (rand()) / static_cast <float> (RAND_MAX))*2;
    this->box.x=x;
    this->box.y=y;
    this->box.width=0.1f;
    this->box.height=1.0f;
    this->visible=true;
    this->collision=false;
    this->angle=1;
    this->angular_velocity=2;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
    int n = 100;
	GLfloat vertex_buffer_data0[1000];
	int k = 0;
	for(int i = 0;i<n;i++)
	{
		vertex_buffer_data0[k++] = 1.0f;
		vertex_buffer_data0[k++] = 0.0f;
		vertex_buffer_data0[k++] = 0.0f;

		vertex_buffer_data0[k++] = 1.0f + (sin(2*M_PI/n*i)/10.0);
		vertex_buffer_data0[k++] = 0.0f + (cos(2*M_PI/n*i)/10.0);
		vertex_buffer_data0[k++] = 0.0f;

		vertex_buffer_data0[k++] = 1.0f + (sin(2*M_PI/n*(i+1))/10.0);
		vertex_buffer_data0[k++] = 0.0f + (cos(2*M_PI/n*(i+1))/10.0);
		vertex_buffer_data0[k++] = 0.0f;
	}
    this->object0 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data0, COLOR_FIRE_BORDER, GL_FILL);

    static const GLfloat vertex_buffer_data1[] = {

        1.0f,.050f,.0f,
        -1.0f,.025f,.0f,
        -1.0f,.050f,.0f,
        
        1.0f,.050f, .0f,
        1.0f,.025f, .0f,
        -1.0f,.050f,.0f,
    };
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_FIRE_BORDER, GL_FILL);

    static const GLfloat vertex_buffer_data2[] = {

        1.0f,.025f,.0f,
        -1.0f,-.025f,.0f,
        -1.0f,.025f,.0f,
        
        1.0f,.025f, .0f,
        1.0f,-.025f, .0f,
        -1.0f,-.025f,.0f,
    };
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_FIRE, GL_FILL);

    static const GLfloat vertex_buffer_data3[] = {

        1.0f,-.025f,.0f,
        -1.0f,-.050f,.0f,
        -1.0f,-.025f,.0f,
        
        1.0f,-.025f, .0f,
        1.0f,-.050f, .0f,
        -1.0f,-.050f,.0f,
        
    };
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_FIRE_BORDER, GL_FILL);

	k = 0;
	for(int i = 0;i<n;i++)
	{
		vertex_buffer_data0[k++] = -1.0f;
		vertex_buffer_data0[k++] = 0.0f;
		vertex_buffer_data0[k++] = 0.0f;

		vertex_buffer_data0[k++] = -1.0f + (sin(2*M_PI/n*i)/10.0);
		vertex_buffer_data0[k++] = 0.0f + (cos(2*M_PI/n*i)/10.0);
		vertex_buffer_data0[k++] = 0.0f;

		vertex_buffer_data0[k++] = -1.0f + (sin(2*M_PI/n*(i+1))/10.0);
		vertex_buffer_data0[k++] = 0.0f + (cos(2*M_PI/n*(i+1))/10.0);
		vertex_buffer_data0[k++] = 0.0f;
	}
    this->object4 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data0, COLOR_FIRE_BORDER, GL_FILL);
}

void Firebeam::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    if(this->rotation==90)
    {
    glm::mat4 rotate1    = glm::rotate((float) (this->axial_rotation * M_PI / 180.0f), glm::vec3(sin(this->rotation * M_PI / 180.0f), cos(this->rotation * M_PI / 180.0f), 0));
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotate1);
    }
    else
    {
        Matrices.model *= (translate * rotate);
    }
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object0);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

// double Firebeam::ret_tan()
// {
//     for(int i=0;i<300;i+=3)
//     {
//         float max_x1=-999.0f;
//         float min_x1=999.0f;
//         float max_x2=-999.0f;
//         float min_x2=999.0f;
//         if(max_x2<float(this->object4.VertexBuffer[i]))
//         {
//             max_x2=float(this->object4.VertexBuffer[i]);
//         }
//     }
//     return 0;
// }

void Firebeam::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Firebeam::tick() {
    this->motion();
    // if(rotation==90)
    // {
        this->box.y=this->position.y;
    if((screen_center_x - 4 / screen_zoom)-1 < this->position.x && this->position.x < (screen_center_x + 4 / screen_zoom)+1)
        this->axial_rotation += this->angular_velocity;
    this->box.x=this->position.x;
    // }
    // this->position.x -= speed;
    // this->position.y += speed/100;
}

void Firebeam::motion() {
    this->position.x += this->velocity.x;//+this->acceleration.x*(0.5);
    this->velocity.x = -(3.0/100);//+=this->acceleration.x;
    if(rotation==90)
        if((screen_center_x - 4 / screen_zoom)-1 < this->position.x && this->position.x < (screen_center_x + 4 / screen_zoom)+1)
        {
            this->position.y += this->velocity.y+this->acceleration.y*(0.5);
            this->velocity.y += this->acceleration.y;
            if (this->position.y <= -2.5)
            {
                this->position.y = -2.5;
            }
            this->acceleration.y = -(this->position.y/1000.0);
        }
}