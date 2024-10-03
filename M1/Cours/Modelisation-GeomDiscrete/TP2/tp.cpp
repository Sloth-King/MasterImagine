// -------------------------------------------
// gMini : a minimal OpenGL/GLUT application
// for 3D graphics.
// Copyright (C) 2006-2008 Tamy Boubekeur
// All rights reserved.
// -------------------------------------------

// -------------------------------------------
// Disclaimer: this code is dirty in the
// meaning that there is no attention paid to
// proper class attribute access, memory
// management or optimisation of any kind. It
// is designed for quick-and-dirty testing
// purpose.
// -------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <GL/glut.h>
#include <float.h>
#include "src/Vec3.h"
#include "src/Camera.h"
#include "src/FastNoiseLit.h"


struct Triangle {
    inline Triangle () {
        v[0] = v[1] = v[2] = 0;
    }
    inline Triangle (const Triangle & t) {
        v[0] = t.v[0];   v[1] = t.v[1];   v[2] = t.v[2];
    }
    inline Triangle (unsigned int v0, unsigned int v1, unsigned int v2) {
        v[0] = v0;   v[1] = v1;   v[2] = v2;
    }
    unsigned int & operator [] (unsigned int iv) { return v[iv]; }
    unsigned int operator [] (unsigned int iv) const { return v[iv]; }
    inline virtual ~Triangle () {}
    inline Triangle & operator = (const Triangle & t) {
        v[0] = t.v[0];   v[1] = t.v[1];   v[2] = t.v[2];
        return (*this);
    }
    // membres :
    unsigned int v[3];
};


struct Mesh {
    std::vector< Vec3 > vertices;
    std::vector< Vec3 > normals;
    std::vector< Triangle > triangles;
    std::vector< Vec3 > colors;
};

struct Point {
    float x;
    float y;
    float z = 0;
};

Point point;

Mesh mesh;

//Meshes to generate
Mesh unit_sphere;
Mesh tesselation;

bool display_normals;
bool display_loaded_mesh;
bool display_unit_sphere;
bool display_tesselation;

// -------------------------------------------
// OpenGL/GLUT application code.
// -------------------------------------------

static GLint window;
static unsigned int SCREENWIDTH = 1600;
static unsigned int SCREENHEIGHT = 900;
static Camera camera;
static bool mouseRotatePressed = false;
static bool mouseMovePressed = false;
static bool mouseZoomPressed = false;
static int lastX=0, lastY=0, lastZoom=0;
static bool fullScreen = false;
static FastNoiseLite noise;

Vec3 crossProduct(Vec3& a, Vec3& b) {
    return Vec3(
        a[1] * b[2] - a[2] * b[1],
        a[2] * b[0] - a[0] * b[2],
        a[0] * b[1] - a[1] * b[0]
    );
}

float factorial(float n)
{
    if (n == 0.0f || n == 1.0f)
        return 1;
    return n * factorial(n - 1);
}


//To complete for Exercice 1
void setUnitSphere( Mesh & o_mesh, int nX=20, int nY=20 )
{

}

void drawCurve(std::vector<Vec3> TabPointsOfCurve , long nbPoints){
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0F, 1.0F, 0.0F);
    for(int i = 0 ; i < nbPoints ; i++){
        glVertex3f(TabPointsOfCurve[i][0] , TabPointsOfCurve[i][1] , TabPointsOfCurve[i][2]);
    }
    glEnd();  
}

std::vector<Vec3> hermiteCubicCurve(Vec3 P0, Vec3 P1 , Vec3 V0 , Vec3 V1 , long nbU){
    std::vector<Vec3> pointList;
    float f1,f2,f3,f4,pu_x,pu_y,pu_z;
    float step = 1/(float)nbU;
    for (float i = 0.0f ; i <= 1.0f ; i+=step){

        f1 = 2*pow(i,3);
        f2 = -2*pow(i,3) + 3*pow(i,2);
        f3 = pow(i,3) - 2*pow(i,2) + i;
        f4 = pow(i,3) - pow(i,2);

        pu_x = f1*P0[0] + f2*P1[0] + f3*V0[0] + f4*V1[0];
        pu_y = f1*P0[1] + f2*P1[1] + f3*V0[1] + f4*V1[1];
        pu_z = f1*P0[2] + f2*P1[2] + f3*V0[2] + f4*V1[2];
        pointList.push_back(Vec3(pu_x,pu_y,pu_z));
    }
    return pointList;
}


std::vector<Vec3> bezierCurveByBernstein(std::vector<Vec3> TabControlPoint, long nbControlPoint, long nbU) {
    float step = 1.0f / (float)(nbU - 1);
    std::vector<Vec3> pointList;

    for (float u = 0.0f; u <= 1.0f; u += step) {
        float px = 0.0f , py = 0.0f ,pz = 0.0f; 
        for (int i = 0; i < nbControlPoint; i++) {
            int n = nbControlPoint - 1; 
            float B = (factorial(n) / (factorial(i) * factorial(n - i))) * pow(u, i) * pow(1 - u, n - i);
            px += B * TabControlPoint[i][0];  
            py += B * TabControlPoint[i][1];
            pz += B * TabControlPoint[i][2];
        }
        pointList.push_back(Vec3(px, py, pz));
    }
    
    return pointList;
}


std::vector<Vec3> bezierCurveByCasteljau(std::vector<Vec3> TabControlPoint, long nbControlPoint, long nbU) {
    std::vector<Vec3> pointList;
    float step = 1.0f / (float)nbU;
    for (float u = 0.0f; u <= 1.0f; u += step) {
        std::vector<Vec3> tempPoints = TabControlPoint;
        
        for (int k = 1; k < nbControlPoint; k++) {
            for (int i = 0; i < nbControlPoint - k; i++) {
                tempPoints[i] = (1 - u) * tempPoints[i] + u * tempPoints[i + 1];
            }
            glPointSize(5.0f); 
            float r = (float)k / nbControlPoint; 
            float g = 1.0f - r;                  
            float b = (float)(nbControlPoint - k) / nbControlPoint;
            glBegin(GL_POINTS);
            glColor3f(r, g, b);  
            for (long i = 0; i < nbControlPoint - k; ++i) {
                glVertex3f(tempPoints[i][0], tempPoints[i][1], tempPoints[i][2]);
            }
            glEnd();
        }
        pointList.push_back(tempPoints[0]);
    }
    return pointList;
}





// To complete for Exercice 2
void setTesselatedSquare(Mesh & o_mesh, int nX=200, int nY=200 )
{}

bool saveOFF( const std::string & filename ,
              std::vector< Vec3 > & i_vertices ,
              std::vector< Vec3 > & i_normals ,
              std::vector< Triangle > & i_triangles,
              bool save_normals = true ) {
    std::ofstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open()) {
        std::cout << filename << " cannot be opened" << std::endl;
        return false;
    }

    myfile << "OFF" << std::endl ;

    unsigned int n_vertices = i_vertices.size() , n_triangles = i_triangles.size();
    myfile << n_vertices << " " << n_triangles << " 0" << std::endl;

    for( unsigned int v = 0 ; v < n_vertices ; ++v ) {
        myfile << i_vertices[v][0] << " " << i_vertices[v][1] << " " << i_vertices[v][2] << " ";
        if (save_normals) myfile << i_normals[v][0] << " " << i_normals[v][1] << " " << i_normals[v][2] << std::endl;
        else myfile << std::endl;
    }
    for( unsigned int f = 0 ; f < n_triangles ; ++f ) {
        myfile << 3 << " " << i_triangles[f][0] << " " << i_triangles[f][1] << " " << i_triangles[f][2];
        myfile << std::endl;
    }
    myfile.close();
    return true;
}

void openOFF( std::string const & filename,
              std::vector<Vec3> & o_vertices,
              std::vector<Vec3> & o_normals,
              std::vector< Triangle > & o_triangles,
              bool load_normals = true )
{
    std::ifstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open())
    {
        std::cout << filename << " cannot be opened" << std::endl;
        return;
    }

    std::string magic_s;

    myfile >> magic_s;

    if( magic_s != "OFF" )
    {
        std::cout << magic_s << " != OFF :   We handle ONLY *.off files." << std::endl;
        myfile.close();
        exit(1);
    }

    int n_vertices , n_faces , dummy_int;
    myfile >> n_vertices >> n_faces >> dummy_int;

    o_vertices.clear();
    o_normals.clear();

    for( int v = 0 ; v < n_vertices ; ++v )
    {
        float x , y , z ;

        myfile >> x >> y >> z ;
        o_vertices.push_back( Vec3( x , y , z ) );

        if( load_normals ) {
            myfile >> x >> y >> z;
            o_normals.push_back( Vec3( x , y , z ) );
        }
    }

    o_triangles.clear();
    for( int f = 0 ; f < n_faces ; ++f )
    {
        int n_vertices_on_face;
        myfile >> n_vertices_on_face;

        if( n_vertices_on_face == 3 )
        {
            unsigned int _v1 , _v2 , _v3;
            myfile >> _v1 >> _v2 >> _v3;

            o_triangles.push_back(Triangle( _v1, _v2, _v3 ));
        }
        else if( n_vertices_on_face == 4 )
        {
            unsigned int _v1 , _v2 , _v3 , _v4;
            myfile >> _v1 >> _v2 >> _v3 >> _v4;

            o_triangles.push_back(Triangle(_v1, _v2, _v3 ));
            o_triangles.push_back(Triangle(_v1, _v3, _v4));
        }
        else
        {
            std::cout << "We handle ONLY *.off files with 3 or 4 vertices per face" << std::endl;
            myfile.close();
            exit(1);
        }
    }

}


// ------------------------------------

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
    camera.resize (SCREENWIDTH, SCREENHEIGHT);
    initLight ();
    glCullFace (GL_BACK);
    glEnable (GL_CULL_FACE);
    glDepthFunc (GL_LESS);
    glEnable (GL_DEPTH_TEST);
    glClearColor (0.2f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_COLOR_MATERIAL);

    display_normals = false;
    display_unit_sphere = false;
    display_loaded_mesh = true;
    display_tesselation = false;
}




// ------------------------------------
// rendering.
// ------------------------------------


void drawVector( Vec3 const & i_from, Vec3 const & i_to ) {

    glBegin(GL_LINES);
    glVertex3f( i_from[0] , i_from[1] , i_from[2] );
    glVertex3f( i_to[0] , i_to[1] , i_to[2] );
    glEnd();
}

void drawTriangleMesh( Mesh const & i_mesh ) {
    glBegin(GL_TRIANGLES);
    bool okNormals = (i_mesh.normals.size() == i_mesh.vertices.size());
    bool okColors = (i_mesh.colors.size() == i_mesh.vertices.size());

    Vec3 p0, p1, p2;
    Vec3 n0, n1, n2;
    Vec3 c0 = Vec3(1, 1, 1), c1 = Vec3(1, 1, 1), c2 = Vec3(1, 1, 1);
    for(unsigned int tIt = 0 ; tIt < i_mesh.triangles.size(); ++tIt) {
        p0 = i_mesh.vertices[i_mesh.triangles[tIt][0]];
        p1 = i_mesh.vertices[i_mesh.triangles[tIt][1]];
        p2 = i_mesh.vertices[i_mesh.triangles[tIt][2]];

        if (okNormals) {
            n0 = i_mesh.normals[i_mesh.triangles[tIt][0]];
            n1 = i_mesh.normals[i_mesh.triangles[tIt][1]];
            n2 = i_mesh.normals[i_mesh.triangles[tIt][2]];
        }
        if (okColors) {
            c0 = i_mesh.colors[i_mesh.triangles[tIt][0]];
            c1 = i_mesh.colors[i_mesh.triangles[tIt][1]];
            c2 = i_mesh.colors[i_mesh.triangles[tIt][2]];
        }

        glNormal3f( n0[0] , n0[1] , n0[2] );
        glColor3f( c0[0], c0[1], c0[2]);
        glVertex3f( p0[0] , p0[1] , p0[2] );
        
        glNormal3f( n1[0] , n1[1] , n1[2] );
        glColor3f( c1[0], c1[1], c1[2]);
        glVertex3f( p1[0] , p1[1] , p1[2] );
        
        glNormal3f( n2[0] , n2[1] , n2[2] );
        glColor3f( c2[0], c2[1], c2[2]);
        glVertex3f( p2[0] , p2[1] , p2[2] );
    }
    glEnd();

    if(display_normals){
        glLineWidth(1.);
        glColor3f(1.,0.,0.);
        for(unsigned int pIt = 0 ; pIt < i_mesh.normals.size() ; ++pIt) {
            Vec3 to = i_mesh.vertices[pIt] + 0.02*i_mesh.normals[pIt];
            drawVector(i_mesh.vertices[pIt], to);
        }

    }

}


void draw () {

    if( display_unit_sphere ){
        glColor3f(0.8,1,0.8);
        drawTriangleMesh(unit_sphere);
    }

    if( display_tesselation ){
        glColor3f(0.8,1,0.8);
        drawTriangleMesh(tesselation);
    }

    if( display_loaded_mesh ){
        glColor3f(0.8,0.8,1);
        drawTriangleMesh(mesh);
    }

    //Test Ex1
    /*Vec3 P0 = Vec3(0,0,0);
    Vec3 P1 = Vec3(2,0,0);
    Vec3 V1 = Vec3(1,-1,0);
    Vec3 V0 = Vec3(1,1,0);
    std::vector<Vec3> curvePoints = hermiteCubicCurve(P0,P1,V0,V1,nbU);
    long nbU = 5;

    int nbPoints = nbU;
    drawCurve(curvePoints , nbPoints);*/
    //Test Ex2
    long nbU = 30;
    long nbControlPoint = 4;
    std::vector<Vec3> bezierPoints = {
        Vec3(0.0f, 0.0f, 0.0f),  
        Vec3(1.0f, 2.0f, 0.0f),  
        Vec3(3.0f, 3.0f, 0.0f),  
        Vec3(4.0f, 0.0f, 0.0f)   
    };

    long nbControlPoint2 = 6;
    std::vector<Vec3> bezierPoints2 = {
    Vec3(0, 0, 0),   
    Vec3(2, 3, 0),    
    Vec3(4, 0, 0),    
    Vec3(2, -3, 0),
    Vec3(0, 0, 0),   
    Vec3(-2, 3, 0)   
    };

    long nbControlPoint3 = 6;
    std::vector<Vec3> bezierPoints3 = {
        Vec3(-1,1,0),
        Vec3(-0.5,-2,0),
        Vec3(0.5,-2,0),
        Vec3(0.5,0,0),
        Vec3(-1,3,0),
        Vec3(-1,0,0)
    };

    
    
    std::vector<Vec3> curvePoints = bezierCurveByCasteljau(bezierPoints3,nbControlPoint3,nbU);
    drawCurve(curvePoints,nbU);
    

}


void display () {
    glLoadIdentity ();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.apply ();
    draw ();
    glFlush ();
    glutSwapBuffers ();
}

void idle () {
    glutPostRedisplay ();
}

void key (unsigned char keyPressed, int x, int y) {
    switch (keyPressed) {
    case 'f':
        if (fullScreen == true) {
            glutReshapeWindow (SCREENWIDTH, SCREENHEIGHT);
            fullScreen = false;
        } else {
            glutFullScreen ();
            fullScreen = true;
        }
        break;


    case 'w':
        GLint polygonMode[2];
        glGetIntegerv(GL_POLYGON_MODE, polygonMode);
        if(polygonMode[0] != GL_FILL)
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
        else
            glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
        break;


    case 'n': //Press n key to display normals
        display_normals = !display_normals;
        break;

    case '1': //Toggle loaded mesh display
        display_loaded_mesh = !display_loaded_mesh;
        break;

    case '2': //Toggle unit sphere mesh display
        display_unit_sphere = !display_unit_sphere;
        break;

    case '3': //Toggle tesselation
        display_tesselation = !display_tesselation;
        break;

    default:
        break;
    }
    idle ();
}

void mouse (int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        mouseMovePressed = false;
        mouseRotatePressed = false;
        mouseZoomPressed = false;
    } else {
        if (button == GLUT_LEFT_BUTTON) {
            camera.beginRotate (x, y);
            mouseMovePressed = false;
            mouseRotatePressed = true;
            mouseZoomPressed = false;
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
        camera.rotate (x, y);
    }
    else if (mouseMovePressed == true) {
        camera.move ((x-lastX)/static_cast<float>(SCREENWIDTH), (lastY-y)/static_cast<float>(SCREENHEIGHT), 0.0);
        lastX = x;
        lastY = y;
    }
    else if (mouseZoomPressed == true) {
        camera.zoom (float (y-lastZoom)/SCREENHEIGHT);
        lastZoom = y;
    }
}


void reshape(int w, int h) {
    camera.resize (w, h);
}



int main (int argc, char ** argv) {
    if (argc > 2) {
        exit (EXIT_FAILURE);
    }
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (SCREENWIDTH, SCREENHEIGHT);
    window = glutCreateWindow ("TP HAI714I");

    init ();
    glutIdleFunc (idle);
    glutDisplayFunc (display);
    glutKeyboardFunc (key);
    glutReshapeFunc (reshape);
    glutMotionFunc (motion);
    glutMouseFunc (mouse);
    key ('?', 0, 0);

    noise.SetFractalOctaves(10);
    noise.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);
    noise.SetFractalGain(0.5);
    noise.SetFractalLacunarity(1.8f);

    //Unit sphere mesh loaded with precomputed normals
    openOFF("data/unit_sphere_n.off", mesh.vertices, mesh.normals, mesh.triangles);

    //setUnitSphere(unit_sphere);

    setTesselatedSquare(tesselation);

    //Uncomment to see other meshes
    //openOFF("data/elephant_n.off", mesh.vertices, mesh.normals, mesh.triangles);

    glutMainLoop ();
    return EXIT_SUCCESS;
}

