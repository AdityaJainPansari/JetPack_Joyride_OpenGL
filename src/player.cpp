#include "player.h"
#include "main.h"

Player::Player(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->velocity = glm::vec3(0, 0, 0);
    this->acceleration = glm::vec3(0,0, 0);
    this->rotation = 0;
    this->score = 0;
    this->box.x=x;
    this->box.y=y;
    this->box.width=0.60f;
    this->box.height=0.60f;
    this->shield = false;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {

        .30f, .30f,.0f,
        -.30f,-.30f,.0f,
        -.30f, .30f,.0f, 

        .30f, .30f, .0f,
        .30f,-.30f, .0f,
        -.30f,-.30f,.0f,
        
    };
    static const GLfloat vertex_buffer_data3[] = {

        -.10f, .20f,.0f,
        -.20f,.10f,.0f,
        -.20f, .20f,.0f, 

        -.10f, .20f, .0f,
        -.10f,.10f, .0f,
        -.20f,.10f,.0f,
        
    };
    static const GLfloat vertex_buffer_data4[] = {

        .20f, .20f,.0f,
        .10f,.10f,.0f,
        .10f, .20f,.0f, 

        .20f, .20f, .0f,
        .20f,.10f, .0f,
        .10f,.10f,.0f,
        
    };
    static const GLfloat vertex_buffer_data5[] = {

        .025f, .10f,.0f,
        -.025f,-.10f,.0f,
        -.025f, .10f,.0f, 

        .025f, .10f, .0f,
        .025f,-.10f, .0f,
        -.025f,-.10f,.0f,
        
    };
    static const GLfloat vertex_buffer_data2[] = {

        .15f, -.50f,.0f, 
        .0f,-.30f,.0f,
        .30f, -.30f,.0f,
        
        -.15f, -.50f, .0f,
        .0f,-.30f, .0f,
        -.30f,-.30f,.0f,

    };

    static const GLfloat vertex_buffer_data6[] = {

        .39f, .39f,.0f,
        -.39f,-.39f,.0f,
        -.39f, .39f,.0f, 

        .39f, .39f, .0f,
        .39f,-.39f, .0f,
        -.39f,-.39f,.0f,
        
    };

    static const GLfloat vertex_buffer_data7[] = {

        .35f, .35f,.0f,
        -.35f,-.35f,.0f,
        -.35f, .35f,.0f, 

        .35f, .35f, .0f,
        .35f,-.35f, .0f,
        -.35f,-.35f,.0f,
        
    };

    static const GLfloat vertex_buffer_data8[] = {

        .43f, .43f,.0f,
        -.43f,-.43f,.0f,
        -.43f, .43f,.0f, 

        .43f, .43f, .0f,
        .43f,-.43f, .0f,
        -.43f,-.43f,.0f,
        
    };

    static const GLfloat vertex_buffer_data9[] = {

        .47f, .47f,.0f,
        -.47f,-.47f,.0f,
        -.47f, .47f,.0f, 

        .47f, .47f, .0f,
        .47f,-.47f, .0f,
        -.47f,-.47f,.0f,
        
    };

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_BLACK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_WHITE, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data4, COLOR_WHITE, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data5, COLOR_BOOMERANG, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_FIRE, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data6, COLOR_RED, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data7, COLOR_BACKGROUND, GL_FILL);
    this->object8 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data8, COLOR_WHITE, GL_FILL);
    this->object9 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data9, COLOR_BLUE, GL_FILL);
}

void Player::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->shield)
    {
        draw3DObject(this->object9);
        draw3DObject(this->object8);
        draw3DObject(this->object6);
        draw3DObject(this->object7);
    }
    draw3DObject(this->object1);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    if(this->acceleration.y >= (0.2/100))
    {
        // std::cout << this->acceleration.y << std::endl;
        draw3DObject(this->object2);
    }
}

void Player::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

bool Player::tick(bool magnet,int sign,bool safe,float ring_x) {
    bool temp = this->motion(magnet,sign,safe,ring_x);
    if(!safe)
    {
        this->roof();
        this->base();
    }
    this->frontwall();
    this->backwall();
    this->box.x=this->position.x;
    this->box.y=this->position.y;
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y += speed/100;
    return temp;
}

bool Player::backwall() {
    if(this->position.x<(-1)*(WALL))
    {
        this->position.x=(-1)*(WALL);
        /*if(this->velocity.x<0)
        {
            this->velocity.x=0;
            //this->acceleration.x=0;
        }*/
        // std::cout << "WALL : " << WALL << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::frontwall() {
    if(this->position.x>(WALL))
    {
        this->position.x=WALL;
        /*if(this->velocity.x>=0)
        {
            this->velocity.x=0;
            //this->acceleration.x=0;
        }*/
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::base() {
    if(this->position.y<=(-3.2))
    {
        this->position.y=-3.2;
        if(this->velocity.y<0)
        {
            this->velocity.y=0;
            this->acceleration.y=0;
        }
        //if(this->velocity.x>=)
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::roof() {
    if(this->position.y>=(3.2))
    {
        this->position.y=3.2;
        if(this->velocity.y>=0)
        {
            this->velocity.y=0;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::motion(bool magnet,int sign,bool safe,float ring_x) {
    this->position.x += this->velocity.x;//+this->acceleration.x*(0.5);
    if(magnet)
    {
        this->position.x -= (sign)*(3.0/100);
    }
    this->velocity.x = 0; //+= this->acceleration.x;
    if(safe)
    {
        this->acceleration.y=0;
        this->position.x -= (3.0/100);
        if(this->position.x<(-1)*(WALL))
        {
            this->position.x=(-1)*(WALL);
        }
        if(this->position.x < (ring_x-0.5f))
        {
            if(this->position.y > -3.2)
            {
                this->position.x = ring_x-0.5f ;
                this->position.y = -3.2;
                return true;
            }
            else
            {
                this->position.y = -3.2;
                return false;
            }
        }
        else if(this->position.x > (ring_x+10.5f))
        {
            if(this->position.y > -3.2)
            {
                this->position.x = ring_x+10.5f ;
                this->position.y = -3.2;
                return true;
            }
            else
            {
                this->position.y = -3.2;
                return false;
            }
        }
        else
        {
            this->position.y = sqrt((5.5*5.5)-((this->position.x-ring_x-5)*(this->position.x-ring_x-5)));
            this->position.y -= 3.2;
            if(this->position.y<=(-3.2))
            {
                this->position.y=-3.2;
            }
            return true;
        }
    }
    else
    {
        this->position.y += this->velocity.y+this->acceleration.y*(0.5);
        this->velocity.y += this->acceleration.y;
        if(!(this->base()))
        {
            this->acceleration.y=-(0.5/100);
            if(magnet)
            {
                this->acceleration.y -= (0.2/100);
            }
        }
        return false;
    }
}
/*
void Player::jump() {
    if (this->speed>0)
    {
        if(this->roof()==true)
        {
            this->speed=-(1.0/100);
            return;
        }
        float temp=this->position.y+this->speed;
        for(float i=this->position.y;i>=temp;i+=(1.0/100))
        {
            this->position.y+=(1.0/100);
            if(this->roof()==true)
            {
                this->speed=-(1.0/100);
                return;
                break;
            }
        }
        if(this->speed>0)
        {
            this->speed-=(1.0/100);            
        }
    }
    else if(this->speed<0)
    {
        if(this->base()==true)
        {
            this->speed=0;
        }
        float temp=this->position.y+this->speed;
        for(float i=this->position.y;i>=temp;i-=(1.0/100))
        {
            this->position.y-=(1.0/100);
            if(this->base()==true)
            {
                this->speed=0;
                break;
            }
        }
        if(this->speed!=0)
        {
            this->speed-=(1.0/100);            
        }
    }
    else
    {
        this->speed=0;
        if(!(this->base()==true))
        {
            this->speed-=(1.0/100);            
        }
    }
    return;
}
*/