// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLM
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GL/glut.h>

using namespace glm;
using Vec3 = glm::vec3;

#include "src/shader.hpp"
#include "src/objloader.hpp"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::vec3 camera_position   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 camera_target = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 camera_up    = glm::vec3(0.0f, 1.0f,  0.0f);

// timing
float deltaTime = 0.1f;	// time between current frame and last frame
float lastFrame = 0.0f;

//rotation
float angle = 0.;
float zoom = 1.;
float rotation_angle;
float angleHorizontal = 0.0f; 
float angleVertical = 0.0f;   
float radius = glm::length(camera_position-camera_target);  
float angle_terre = 0.f;    
float angle_terre_ellememe = 0.f;
float angle_lune = 0.f;
float angle_lune_ellememe = 0.f;


static GLint window;
static bool mouseRotatePressed = false;
static bool mouseMovePressed = false;
static bool mouseZoomPressed = false;
static int lastX=0, lastY=0, lastZoom=0;
static bool fullScreen = false;


GLuint programID;
GLuint VertexArrayID;
GLuint vertexbuffer;
GLuint elementbuffer;
GLuint LightID;
GLuint colorbuffer;


std::vector<unsigned short> indices; //Triangles concaténés dans une liste
std::vector<std::vector<unsigned short> > triangles;
std::vector<glm::vec3> indexed_vertices;


glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 0 );
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;


	// Right vector
glm::vec3 rightVector() {
    return glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f),
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
}

// Direction : Spherical coordinates to Cartesian coordinates conversion
glm::vec3 directionVector() {
    return glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );
}

void computeMatricesFromInputs(float moveX, float moveY);
void initLight ();
void init ();
void draw ();
void display ();
void idle ();
void key (unsigned char keyPressed, int x, int y);
void mouse (int button, int state, int x, int y);
void motion (int x, int y);
void reshape(int w, int h);
int main (int argc, char ** argv);
void printMatrix(const glm::mat4& mat);

// ------------------------------------

void printMatrix(const glm::mat4& mat) {
    std::cout << mat[0][0] << " " << mat[1][0] << " " << mat[2][0] << " " << mat[3][0] << "\n" << mat[0][1] << " " << mat[1][1] << " " << mat[2][1] << " " << mat[3][1] << "\n" << mat[0][2] << " " << mat[1][2] << " " << mat[2][2] << " " << mat[3][2] << "\n" << mat[0][3] << " " << mat[1][3] << " " << mat[2][3] << " " << mat[3][3] << std::endl;
}

void initLight () {
    GLfloat light_position1[4] = {22.0f, 16.0f, 50.0f, 0.0f};
    GLfloat direction1[3] = {-52.0f,-16.0f,-50.0f};
    GLfloat color1[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat ambient[4] = {0.3f, 0.3f, 0.3f, 0.5f};

    glLightfv (GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv (GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, color1);
    glLightfv (GL_LIGHT1, GL_SPECULAR, color1);
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);
}

void init () {
    // camera.resize (SCREENWIDTH, SCREENHEIGHT);
    initLight ();
    // glCullFace (GL_BACK);
    // glEnable (GL_CULL_FACE);
    glDepthFunc (GL_LESS);
    glEnable (GL_DEPTH_TEST);
    glClearColor (0.2f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_COLOR_MATERIAL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return;
    }

}




// ------------------------------------
// rendering.
// ------------------------------------

void draw () {
    glUseProgram(programID);
    // Model matrix : an identity matrix (model will be at the origin) then change
    glm::mat4 transformations = glm::mat4(1.0f);
    transformations = glm::scale(transformations,glm::vec3(0.5f*zoom,0.5f*zoom,0.5f*zoom));
    transformations = glm::translate(transformations,glm::vec3(-1.f,-2.f,0.f));
    // View matrix : camera/view transformation lookat() utiliser camera_position camera_target camera_up
    
    glm::mat4 ViewMatrix = glm::lookAt(camera_position,camera_target,camera_up);
    // Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(45.f),4.f/3.f,0.1f,100.f);
    // Send our transformation to the currently bound shader,
    GLuint transformationsLoc = glGetUniformLocation(programID,"transformations");
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformations[0][0]);

    // in the "Model View Projection" to the shader uniformsc
    GLuint projectionMatrixLoc = glGetUniformLocation(programID, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, &ProjectionMatrix[0][0]);

    GLuint viewMatrixLoc = glGetUniformLocation(programID, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &ViewMatrix[0][0]);

    //obtenir les couleur
    GLuint colorLoc = glGetUniformLocation(programID,"objet_couleur");
    
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
                0,                  // attribute
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
                );

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

    // Draw the triangles !
    // glDrawElements(
    //             GL_TRIANGLES,      // mode
    //             indices.size(),    // count
    //             GL_UNSIGNED_SHORT,   // type
    //             (void*)0           // element array buffer offset
    //             );

    // Afficher une seconde chaise
    glm::mat4 transformations2 = glm::mat4(1.0f);
    transformations2 = glm::scale(transformations2,glm::vec3(-0.5f*zoom,0.5f*zoom,0.5f*zoom));
    transformations2 = glm::translate(transformations2,glm::vec3(-1.f,-2.f,0.f));
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformations2[0][0]);
    // glDrawElements(
    //             GL_TRIANGLES,      // mode
    //             indices.size(),    // count
    //             GL_UNSIGNED_SHORT,   // type
    //             (void*)0           // element array buffer offset
    //             );

    // Afficher une troisieme chaise/souzanne ! (passer!)
    glm::mat4 transformations3 = glm::mat4(1.0f);
    glm::vec3 vec_repere_monde = glm::vec3(1.f,1.f,1.f);
    glm::vec3 vec_personnage = glm::vec3(0.f,1.f,0.f);
    glm::vec3 rotation_axe = glm::cross(vec_repere_monde,vec_personnage);
    transformations3 = glm::rotate(transformations3, glm::radians(angle), rotation_axe);
    transformations3 = glm::scale(transformations3,glm::vec3(zoom,zoom,zoom));
    transformations3 = glm::translate(transformations3,vec3(0.f,0.f,0.f)); 
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformations3[0][0]);
    //glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,(void*)0);
    
    
    // I. afficher le soleil !
    glm::mat4 transformation_soleil = glm::mat4(1.0f);
    glUniform3f(colorLoc,1.f,0.3f,0.f);//orange
    transformation_soleil = glm::scale(transformation_soleil,glm::vec3(0.7f,0.7f,0.7f));
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformation_soleil[0][0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,(void*)0);

    //II. afficher la terre
    glm::mat4 transformation_terre = glm::mat4(1.0f);
    glUniform3f(colorLoc,0.f,0.3f,0.7f);//bleu
    glm::vec3 vec_up = glm::vec3(0.f,1.f,0.f);
    transformation_terre = glm::rotate(transformation_terre,glm::radians(angle_terre),vec_up);
    transformation_terre = glm::scale(transformation_terre,glm::vec3(0.3f,0.3f,0.3f));
    transformation_terre = glm::translate(transformation_terre,glm::vec3(7.f,0.f,0.f));
    transformation_terre = glm::rotate(transformation_terre,glm::radians(angle_terre_ellememe),vec3(sin(glm::radians(23.4f)),cos(glm::radians(23.4f)),0.f));
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformation_terre[0][0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,(void*)0);
    
    //III. afficher la lune
    glm::mat4 transformation_lune = glm::mat4(1.0f);
    glUniform3f(colorLoc,0.7f,0.7f,0.7f);//gris
    glm::vec3 position_terre = glm::vec3(transformation_terre[3]);
    transformation_lune = glm::translate(transformation_lune,position_terre);
    transformation_lune = glm::rotate(transformation_lune,glm::radians(angle_terre_ellememe),vec3(sin(glm::radians(6.7f)),cos(glm::radians(6.7f)),0.f));
    transformation_lune = glm::scale(transformation_lune,glm::vec3(0.1f,0.1f,0.1f));
    transformation_lune = glm::translate(transformation_lune,glm::vec3(5.f,0.f,0.f));
    //transformation_lune = glm::rotate(transformation_lune,glm::radians(angle_lune_ellememe),vec3(sin(glm::radians(6.7f)),cos(glm::radians(6.7f)),0.f));
    glUniformMatrix4fv(transformationsLoc,1,GL_FALSE,&transformation_lune[0][0]);
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,(void*)0);

    //fin
    glDisableVertexAttribArray(0);
}


void display () {
    glLoadIdentity ();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // camera.apply ();
    draw ();
    glFlush ();
    glutSwapBuffers ();
}

void idle () {
    glutPostRedisplay ();
    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.f;
    deltaTime = time - lastFrame;
    lastFrame = time;

    angle_terre += 1.f * deltaTime*10;         
    angle_terre_ellememe += 36.5f * deltaTime*10; 
    // angle_lune += 15.0f * deltaTime*10;           
    // angle_lune_ellememe += 36.5f * deltaTime*10;  

    if (angle_terre >= 360.0f) angle_terre -= 360.0f;
    if (angle_terre_ellememe >= 360.0f) angle_terre_ellememe -= 360.0f;
    if (angle_lune >= 360.0f) angle_lune -= 360.0f;
    if (angle_lune_ellememe >= 360.0f) angle_lune_ellememe -= 360.0f;
}

void key (unsigned char keyPressed, int x, int y) {
    float cameraSpeed = 100. * deltaTime;
    switch (keyPressed) {
    case 'f':
        if (fullScreen == true) {
            glutReshapeWindow (SCR_WIDTH, SCR_HEIGHT);
            fullScreen = false;
        } else {
            glutFullScreen ();
            fullScreen = true;
        }
        break;

    case 's':
        camera_position -= cameraSpeed * glm::vec3(0.f,0.f,-1.f);
        radius = glm::length(camera_position - camera_target);
        break;
    case 'q':
    {
        //camera_position += glm::normalize(glm::cross(camera_target - camera_position, camera_up)) * cameraSpeed;
        angleHorizontal -= glm::radians(5.0f);
        camera_position.x = camera_target.x+radius * cos(angleVertical) * sin(angleHorizontal);
        camera_position.y = camera_target.y+radius * sin(angleVertical);
        camera_position.z = camera_target.z+radius * cos(angleVertical) * cos(angleHorizontal);
        break;
    }
        
    case 'z':
        camera_position += cameraSpeed * glm::vec3(0.f,0.f,-1.f);
        radius = glm::length(camera_position - camera_target);
        break;
    case 'd':
    {   //camera_position -= glm::normalize(glm::cross(camera_target - camera_position, camera_up)) * cameraSpeed;
        angleHorizontal += glm::radians(5.0f);
        camera_position.x = camera_target.x+radius * cos(angleVertical) * sin(angleHorizontal);
        camera_position.y = camera_target.y+radius * sin(angleVertical);
        camera_position.z = camera_target.z+radius * cos(angleVertical) * cos(angleHorizontal);
        break;
    }
    case '+':
        zoom+=0.1f;
        break;
    case '-':
        zoom-=0.1f;
        if(zoom<0.1f)zoom = 0.1f;
        break;
    case 'y'://haut
        position+=glm::vec3(0.,0.1f,0.);
        break;

    case 'h'://bas
        position-=glm::vec3(0.,0.1f,0.);
        break;
    case 'g'://gauche
        position-=glm::vec3(0.1f,0.,0.);
        break;
    case 'j'://droit
        position+=glm::vec3(0.1f,0.,0.);
        break;
    case 'a'://angle +
        angle+=1.f;
        if(angle>=360.f) angle = 0.f;
        break;
    case 'A'://angle -
        angle-=1.f;
        if(angle>=360.f) angle = 0.f;
        break;

    case 't'://angle_terre , angle_terre_ellememe
        angle_terre+=1.f;
        angle_lune+=15.f;
        angle_terre_ellememe+=36.5f;
        angle_lune_ellememe+=36.5f;
        if(angle_terre>=360.f) {angle_terre = 0.f;}
        if(angle_terre_ellememe>=360.f) {angle_terre_ellememe = 0.f;}
        if(angle_lune>=360.f) {angle_lune = 0.f;}
        if(angle_lune_ellememe>=360.f) {angle_lune_ellememe = 0.f;}
        break;

    case 'T'://angle_terre , angle_terre_ellememe
        angle_terre-=1.f;
        angle_lune-=15.f;
        angle_terre_ellememe-=36.5f;
        angle_lune_ellememe-=36.5f;
        if(angle_terre>=360.f) {angle_terre = 0.f;}
        if(angle_terre_ellememe>=360.f) {angle_terre_ellememe = 0.f;}
        if(angle_lune>=360.f) {angle_lune = 0.f;}
        if(angle_lune_ellememe>=360.f) {angle_lune_ellememe = 0.f;}
        break;
          
    default:
        break;
    }
    //TODO add translations
    idle ();
}

void specialKeys(int key, int x, int y) {
    if(key == GLUT_KEY_LEFT)
		position -= rightVector() * deltaTime * speed;
    else if(key == GLUT_KEY_RIGHT)
		position += rightVector() * deltaTime * speed;
    else if(key == GLUT_KEY_DOWN)
		position -= directionVector() * deltaTime * speed;
    else if(key == GLUT_KEY_UP)
        position += directionVector() * deltaTime * speed;
}

void mouse (int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        mouseMovePressed = false;
        mouseRotatePressed = false;
        mouseZoomPressed = false;
    } else {
        if (button == GLUT_LEFT_BUTTON) {
            //camera.beginRotate (x, y);
            mouseMovePressed = false;
            mouseRotatePressed = true;
            mouseZoomPressed = false;
            lastX = x;
            lastY = y;
        } else if (button == GLUT_RIGHT_BUTTON) {
            lastX = x;
            lastY = y;
            mouseMovePressed = true;
            mouseRotatePressed = false;
            mouseZoomPressed = false;
        } else if (button == GLUT_MIDDLE_BUTTON) {
            if (mouseZoomPressed == false) {
                lastZoom = y;
                mouseMovePressed = false;
                mouseRotatePressed = false;
                mouseZoomPressed = true;
            }
        }
    }
    idle ();
}

void motion (int x, int y) {
    if (mouseRotatePressed == true) {
        computeMatricesFromInputs(x - lastX, y - lastY);
        lastX = x;
        lastY = y;
    }
    else if (mouseMovePressed == true) {
    }
    else if (mouseZoomPressed == true) {
    }
}

void computeMatricesFromInputs(float moveX, float moveY){
    std::cout << moveX << " " << moveY << std::endl;
	// Compute new orientation
	horizontalAngle += mouseSpeed * moveX / 10.f;
	verticalAngle   += mouseSpeed * moveY / 10.f;

	// Up vector
	glm::vec3 up = glm::cross( rightVector(), directionVector() );

	float FoV = initialFoV;

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);

	// Camera matrix
	ViewMatrix       = glm::lookAt(
								camera_position,           // Camera is here
								camera_position + directionVector(), // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );
}


void reshape(int w, int h) {
    // camera.resize (w, h);
}

int main (int argc, char ** argv) {
    if (argc > 2) {
        exit (EXIT_FAILURE);
    }
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (SCR_WIDTH, SCR_HEIGHT);
    window = glutCreateWindow ("TP HAI719I");

    init ();
    glutIdleFunc (idle);
    glutDisplayFunc (display);
    glutKeyboardFunc (key);
    glutReshapeFunc (reshape);
    glutMotionFunc (motion);
    glutMouseFunc (mouse);
    glutSpecialFunc(specialKeys);
    key ('?', 0, 0);

    computeMatricesFromInputs(0.f, 0.f);

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "vertex_shader.glsl", "fragment_shader.glsl" );

    //Chargement du fichier de maillage
    std::string filename("data/sphere.off");
    loadOFF(filename, indexed_vertices, indices, triangles );

    // Load it into a VBO

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);

    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

    glutMainLoop ();

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);


    return EXIT_SUCCESS;
}
