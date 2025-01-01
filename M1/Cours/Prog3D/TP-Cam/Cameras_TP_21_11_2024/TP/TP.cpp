// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

// Include GLM
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// Include TP
#include <TP/Actor/Actor.hpp>
#include <TP/Actor/ObjController.hpp>
#include "TP/Camera/Camera.hpp"
#include "common/quaternion_utils.hpp"

using namespace glm;

#include <common/shader.hpp>
#include <common/objloader.hpp>
#include <common/vboindexer.hpp>
#include <common/texture.hpp>

#ifdef _WINDOWS

#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

bool globalInit();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* initWindow();
void windowSetup();
void initImgui();
void updateLightPosition(GLuint _lightID);

int main(void)
{
    if (!globalInit())
    {
        return -1;
    }
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    GLuint programID = LoadShaders("vertex_shader.glsl", "fragment_shader.glsl");
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
    GLuint colorID = glGetUniformLocation(programID, "color_Mesh");

    /****************************************/  


    //Chargement du fichier de maillage
    ObjController map;
    Actor target;

    map.loadObj("obj/myMap2.obj", glm::vec3(0.6f, 0.5f, 0.3f), colorID);
    target.load("obj/cameraTarget.obj", glm::vec3(0.8f, 0.5f, 0.4f), colorID);


    glUseProgram(programID);

    // Init ImGUI
    initImgui();

    // Init Camera
    Camera myCamera;
    //[Camera] Aller plus loin : loader une position, rotation et fov ?
    myCamera.init();

    // For speed computation
    double lastTime = glfwGetTime();
    int nbFrames = 0;

    //VSync - avoid having 3000 fps
    glfwSwapInterval(1);


    
    /*__________________UPDATE__________________*/
    do {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //input
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            glm::quat camRotation = myCamera.getRotation();
            target.moveGround(camRotation , window , deltaTime);
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            glm::quat camRotation = myCamera.getRotation();
            target.moveGround(camRotation , window , deltaTime);
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            glm::quat camRotation = myCamera.getRotation();
            target.moveGround(camRotation , window , deltaTime);
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            glm::quat camRotation = myCamera.getRotation();
            target.moveGround(camRotation , window , deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            target.jumpUpdate(window , deltaTime);
        }

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        //Imgui 
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Update
        target.update(deltaTime, window, myCamera.getRotation());
    
        if(myCamera.isAttachedToTarget()){
            //TEST1
            glm::vec3 offset(0.0f, 2.0f, -6.0f); 
            glm::vec3 cameraPosition = target.getPosition() + offset;
            myCamera.setPosition(cameraPosition);
            glm::vec3 direction = glm::normalize(target.getPosition() - cameraPosition);
        
            glm::quat lookAtRotation = QuaternionUtils::LookAt(direction, target.getPosition());        
            myCamera.setRotation(lookAtRotation);



            //TEST2
            // glm::vec3 offset = glm::quat(myCamera.getEulerAngle()) * glm::vec3(0.0f, 0.0f, -myCamera.getDist());
            // glm::vec3 cameraPosition = target.getPosition() - offset;
            // myCamera.setPosition(cameraPosition);

            // glm::vec3 forward = glm::normalize(target.getPosition() - cameraPosition);
            // glm::vec3 right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), forward));
            // if (glm::length(right) < 0.001f)
            // {
            //     right = glm::normalize(glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), forward));
            // }
            // glm::vec3 up = glm::cross(forward, right);

            // glm::mat4 lookAtMatrix = glm::lookAt(cameraPosition, target.getPosition(), up);
            // myCamera.setRotation(glm::quat_cast(lookAtMatrix));

        }
        
        myCamera.update(deltaTime, window);


        glm::mat4 viewMatrix = myCamera.getViewMatrix();
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);

        //View
        updateLightPosition(LightID);

        map.updateViewAndDraw(myCamera, MatrixID, ModelMatrixID);
        target.updateViewAndDraw(myCamera, MatrixID, ModelMatrixID); 

        // Renders the ImGUI elements
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);


        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    // Deletes all ImGUI instances
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // Cleanup VBO and shader

    glDeleteProgram(programID);
    //glDeleteTextures(1, &Texture);
    glDeleteVertexArrays(1, &VertexArrayID);
    map.deleteBuffer();
    target.destroy();
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

bool globalInit()
{
    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return false;
    }

    window = initWindow();
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return false;
    }

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return false;
    }

    windowSetup();
    return true;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

GLFWwindow* initWindow()
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // Open a window and create its OpenGL context
    GLFWwindow* createdWindow = glfwCreateWindow(1500, 1000, "TP Camera", NULL, NULL);
    if (createdWindow != NULL) {
        glfwMakeContextCurrent(createdWindow);
        glfwSetFramebufferSizeCallback(createdWindow, framebuffer_size_callback);
    }

    return createdWindow;
}

void windowSetup()
{
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    //  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set the mouse at the center of the screen
    glfwPollEvents();
    //glfwSetCursorPos(window, 1024 / 2, 768 / 2);

    // Dark blue background
    glClearColor(0.8f, 0.8f, 0.8f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
}

void initImgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void updateLightPosition(GLuint _lightID)
{
    const glm::vec3 lightPos = glm::vec3(4.f, 90.f, 4.f);
    glUniform3f(_lightID, lightPos.x, lightPos.y, lightPos.z);
}