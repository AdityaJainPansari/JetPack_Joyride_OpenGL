#include "main.h"
#include "timer.h"
// #include "ball.h"
#include "player.h"
#include "floor.h"
#include "coin.h"
#include "segmentdisplay.h"
#include "firebeam.h"
#include "boomerang.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Player player;
vector<Floor> tilesB;
vector<Floor> tilesW;
// std::vector<std::array<Coin, 9>> coins;
// std::vector< Coin[9] > coins;
std::vector<Coin*> coins ;//= std::vector<Coin*>();
// vector<Coin> coins[9];
vector<Firebeam> firebeams;
Boomerang boomerang;
Segmentdisplay score;
Segmentdisplay dist;
// Ball ball1;
// Ball ball2;
// bounding_box_t box,box1,box2;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float WALL=3.5;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    /*
    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    */
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    player.draw(VP);
    score.draw(VP);
    dist.draw(VP);
    for(int i=0;i<tilesB.size();i++)
    {
        if((screen_center_x - 4 / screen_zoom)-1 < tilesB[i].position.x && tilesB[i].position.x < (screen_center_x + 4 / screen_zoom)+1)
            tilesB[i].draw(VP);
    }
    for(int i=0;i<tilesW.size();i++)
    {
        if((screen_center_x - 4 / screen_zoom)-1 < tilesW[i].position.x && tilesW[i].position.x < (screen_center_x + 4 / screen_zoom)+1)
            tilesW[i].draw(VP);
    }
    for(int i=0;i<coins.size();i++)
    {
        for(int j=0;j<9;j++)
        {
            if((screen_center_x - 4 / screen_zoom)-1 < coins[i][j].position.x && coins[i][j].position.x < (screen_center_x + 4 / screen_zoom)+1)
                if(coins[i][j].visible)
                {
                    coins[i][j].draw(VP);
                }
        }
    }
    for(int i=0;i<firebeams.size();i++)
    {
        if((screen_center_x - 4 / screen_zoom)-1 < firebeams[i].position.x && firebeams[i].position.x < (screen_center_x + 4 / screen_zoom)+1)
            if(firebeams[i].visible)
            {
                firebeams[i].draw(VP);
            }
    }
    boomerang.draw(VP);
    // ball1.draw(VP);
    // ball2.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    if (left) {
        player.velocity.x-=4.0/100;
        dist.add(-4.0/100);
        //cout << "x" << player.position.x << "\n" << "y" << player.position.y << "\n" << endl;
    }
    if (right) {
        player.velocity.x+=4.0/100;
        dist.add(4.0/100);
        //cout << "x" << player.position.x << "\n" << "y" << player.position.y << "\n" << endl;
    }
    if (up) {
        player.acceleration.y=(0.4/100);
        //cout << "x" << player.position.x << "\n" << "y" << player.position.y << "\n" << endl;
    }
}

void tick_elements() {

    player.tick();
    dist.add(3.0/100);
    score.add(0);
    for(int i=0;i<tilesB.size();i++)
    {
        tilesB[i].tick();
        if(tilesB[i].position.x<(-1)*WALL-2)
        {
            tilesB.erase(tilesB.begin()+i);
            i--;
        }
    }
    for(int i=0;i<tilesW.size();i++)
    {
        tilesW[i].tick();
        if(tilesW[i].position.x<(-1)*WALL-2)
        {
            tilesW.erase(tilesW.begin()+i);
            i--;
        }
    }
    for(int i=0;i<coins.size();i++)
    {
        for(int j=0;j<9;j++)
        {
            if(coins[i][j].visible)
            {
                coins[i][j].tick();
            }
        }
        if(coins[i][8].position.x<(-1)*WALL-2)
        {
            coins.erase(coins.begin()+i);
            i--;
        }
    }
    for(int i=0;i<firebeams.size();i++)
    {
        if(firebeams[i].visible)
        {
            firebeams[i].tick();
        }
        if(firebeams[i].position.x<(-1)*WALL-2)
        {
            firebeams.erase(firebeams.begin()+i);
            i--;
        }
    }
    boomerang.tick();
    cout << "Boomerang " << "x : " << boomerang.position.x << "y : " << boomerang.position.y << endl ;
    for(int i=0;i<coins.size();i++)
    {
        for(int j=0;j<9;j++)
        {
            if(coins[i][j].visible!=false && detect_collision(player.box,coins[i][j].box,0))
            {
                cout << "coin collision" << endl;
                coins[i][j].visible=false;
                player.score+=10;
                score.add(10);
                cout << "score : " << player.score << endl ;
            }            
        }
    }
    for(int i=0;i<firebeams.size();i++)
    {
        if(firebeams[i].visible!=false && detect_collision(player.box,firebeams[i].box,firebeams[i].rotation) )
        {
            if(firebeams[i].rotation==90)
            {
                if(firebeams[i].collision!=true)
                {
                    cout << "fire collision : -60" << endl;
                    // firebeams[i].visible=false;
                    firebeams[i].collision=true;
                    player.score-=60;
                    score.add(-60);
                    cout << "score : " << player.score << endl ;
                }
            }
            else
            {
                if(firebeams[i].collision!=true)
                {
                    cout << "fire collision : -20" << endl;
                    // firebeams[i].visible=false;
                    firebeams[i].collision=true;
                    player.score-=20;
                    score.add(-20);
                    cout << "score : " << player.score << endl ;
                }
            }
        }
        else if(firebeams[i].visible!=false)
        {
            firebeams[i].collision=false;
        }
    }
    // ball1.tick();
    // ball2.tick();
    // box1.x=ball1.position.x;
    // box1.y=ball1.position.y;
    // box2.x=ball2.position.x;
    // box2.y=ball2.position.y;
    // if(detect_collision(box1,box2))
    // {
    // 	ball1.speed *=-1;
    // 	ball2.speed *=-1;
    // }
    // if(!(detect_collision(box1,box)))
    // {
    // 	ball1.speed *=-1;
    // }
    // if(!(detect_collision(box,box2)))
    // {
    // 	ball2.speed *=-1;
    // }
    //camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    player       = Player(-2.5, -3.2, COLOR_GREEN);
    int temp= static_cast <int> (rand()) / (static_cast <int> (RAND_MAX/5));
    for(int i=0;i<100;i++)
    {
        tilesB.push_back(Floor((i*4)-6,-3.5, COLOR_BLACK));
        tilesW.push_back(Floor((i*4)-4,-3.5, COLOR_WHITE));
        if(temp!=0)
        {
            float rotation= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/M_PI));
            rotation/= (M_PI / 180.0f);
            firebeams.push_back(Firebeam(12*i,temp/2.0,COLOR_RED,rotation));
            temp--;
        }
        else
        {
            float pos_y= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5.0));
            firebeams.push_back(Firebeam(12*i,2.5,COLOR_RED,90));
            temp= static_cast <int> (rand()) / (static_cast <int> (RAND_MAX/5));
            // temp= static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/M_PI));
        }
    }
    for(int i=0;i<50;i++)
    {
        float r=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);//random_int float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        Coin temp[9];
        for(int j=0;j<9;j++)
        {
            temp[j]=Coin(10*i+j%3,(r*3)-(j/3),COLOR_COIN);
        }
        coins.push_back(temp);
    }
    boomerang = Boomerang(WALL*2,4,COLOR_BOOMERANG);
    // ball1       = Ball(0, 3, COLOR_GREEN);
    // ball2       = Ball(0, -3, COLOR_RED);
    // ball1.speed = -1;
    // ball2.speed = 1;
    // box1.width=2;
    // box2.width=2;
    // box1.height=2;
    // box2.height=2;
    // box.x=0;
    // box.y=0;
    // box.width=4;
    // box.height=4;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    score.set_position(0,3.5);
    dist.set_position(-6,3.5);
    score.update(0);
    dist.update(0);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

/*
bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}
*/

bool detect_collision(bounding_box_t a, bounding_box_t b, float rotation) {
    if(rotation == 0)
    {
        return (abs(a.x - b.x) * 2 < (a.width + b.width)) && (abs(a.y - b.y) * 2 < (a.height + b.height));
    }
    else if (rotation > 0)
    {
        float b_x_new = b.x - cos(rotation * M_PI / 180.0f) * (a.y-b.y);
        float b_width_new = abs(cos(rotation * M_PI / 180.0f) * b.width);
        return (abs(a.x - b_x_new) * 2 < (a.width + b.width)) && (abs(a.y - b.y) * 2 < (a.height + b.height));
    }
    else if (rotation < 0)
    {
        float b_x_new = b.x + cos(rotation * M_PI / 180.0f) * (a.y-b.y);
        float b_width_new = abs(cos(rotation * M_PI / 180.0f) * b.width);
        return (abs(a.x - b_x_new) * 2 < (a.width + b.width)) && (abs(a.y - b.y) * 2 < (a.height + b.height));
   }
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    score.set_position(0+WALL-3.5,3.5);
    dist.set_position(-6-WALL+3.5,3.5);
    WALL=right-0.5;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    cout << top << " " << bottom << " " << left << " " << right << endl ;
}
