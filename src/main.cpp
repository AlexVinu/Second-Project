#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "C:/OpenGL/Second-Project/res/stb_image.h"

#include "render/ShaderProgram.h"
#include "buffers/vbo.h"
#include "resources/ResourceManager.h"
#include <iostream>
#include "render/TextureProgram.h"
#include "camera/camera.h"

extern "C" {
    _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;    // For NVidia
    // __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; // For AMD
}

GLfloat deltaTime = 0.0f;	// Время, прошедшее между последним и текущим кадром
GLfloat lastFrame = 0.0f;  	// Время вывода последнего кадра

GLfloat last_mouse_x = 400.0f;
GLfloat last_mouse_y = 300.0f;

Camera camera;

bool keys[1024];
bool firstMouseInit = true;

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  -10.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};

int WindowSizeX = 800;
int WindowSizeY = 600;


void WindowSizeCallback(GLFWwindow* window, int width, int height) {
    WindowSizeY = height;
    WindowSizeX = width;
    glViewport(0, 0, WindowSizeX, WindowSizeY);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main(int argc, char* argv[])
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!\n";
        return -1;
    }
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(WindowSizeX, WindowSizeY, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "can`t load glad" << std::endl;
        return -1;
    }
    glfwSetWindowSizeCallback(window, WindowSizeCallback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);

    std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

    glClearColor(1, 1, 0, 0);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    Buffers::VertexBufferObject vbo;
    ResourceManager res(argv[0]);
    auto pFirst_ShaderProgram = res.load_shader("First_ShaderProgram", "res/Shaders/vertexShader.txt", "res/Shaders/fragmentShader.txt");
    glBindVertexArray(0);

    std::cerr << "1\n";

    auto brick = res.load_texture("brick", "res/textures/brick.png");

    std::cerr << "2\n";

    auto smile = res.load_texture("smile", "res/textures/smile.png");

    auto wood = res.load_texture("wood", "res/textures/wood.png");

    std::cerr << "end\n";
    res.getObjects_Textures();
    res.getObjects_Shaders();


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        pFirst_ShaderProgram->use_ShaderProgram();

        
        glm::mat4 projection(1.0f);

       

        glm::mat4 view;
        view = camera.viewMatrix();


        projection = glm::perspective(camera.fov, (GLfloat)WindowSizeX/ (GLfloat)WindowSizeY, 0.1f, 100.0f);


        GLint modelLoc = glGetUniformLocation(pFirst_ShaderProgram->Give_Id(), "model");

        GLint viewLoc = glGetUniformLocation(pFirst_ShaderProgram->Give_Id(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        GLint projectionLoc = glGetUniformLocation(pFirst_ShaderProgram->Give_Id(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(vao);
        for (int i = 0; i < 10; i++) {
            if (i < 6) {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, wood->Give_ID());
                glUniform1i(glGetUniformLocation(pFirst_ShaderProgram->Give_Id(), "ourTexture1"), 0);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, smile->Give_ID());
                glUniform1i(glGetUniformLocation(pFirst_ShaderProgram->Give_Id(), "ourTexture2"), 1);

                glm::mat4 model(1.0f);
                model = glm::translate(model, cubePositions[i]);
                GLfloat angle = i - 2.0f;
                model = glm::rotate(model, (GLfloat)glfwGetTime() * angle, glm::vec3(1.0f, 0.0f, 1.0f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            }
            else {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, brick->Give_ID());
                glUniform1i(glGetUniformLocation(pFirst_ShaderProgram->Give_Id(), "ourTexture1"), 0);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, smile->Give_ID());
                glUniform1i(glGetUniformLocation(pFirst_ShaderProgram->Give_Id(), "ourTexture2"), 1);

                glm::mat4 model(1.0f);
                model = glm::translate(model, cubePositions[i]);
                GLfloat angle = i - 2.0f;
                model = glm::rotate(model, (GLfloat)glfwGetTime() * angle, glm::vec3(1.0f, 0.0f, 1.0f));
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            }
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
        
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        camera.keyboard_move(deltaTime, keys);
    }
    glDeleteVertexArrays(1, &vao);
    glfwTerminate();
    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouseInit) {
        last_mouse_x = xpos;
        last_mouse_y = ypos;
        firstMouseInit = false;
    }
    GLfloat xoffset = xpos - last_mouse_x;
    GLfloat yoffset = last_mouse_y - ypos;
    last_mouse_x = xpos;
    last_mouse_y = ypos;
    camera.mouse_move(xoffset, yoffset);
}

void mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.mouse_scroll(yoffset);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else if (key == GLFW_KEY_F2 && action == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else if (action == GLFW_PRESS) {
        keys[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        keys[key] = false;
    }
}

