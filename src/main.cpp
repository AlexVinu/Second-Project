#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render/ShaderProgram.h"
#include "buffers/vbo.h"
#include "resources/ResourceManager.h"
#include <iostream>
#include "render/TextureProgram.h"
#define STB_IMAGE_IMPLEMENTATION
#include "C:/OpenGL/Second-Project/res/stb_image.h"

extern "C" {
    _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;    // For NVidia
    // __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; // For AMD
}

GLuint verticies[] = {
    0,1,3,
    1,2,3,
};

int WindowSizeX = 640;
int WindowSizeY = 480;

void WindowSizeCallback(GLFWwindow* window, int width, int height) {
    WindowSizeY = height;
    WindowSizeX = width;
    glViewport(0, 0, WindowSizeX, WindowSizeY);
}

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

    std::cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;

    glClearColor(1, 1, 0, 0);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint ibo = 0;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    Buffers::VertexBufferObject vbo;
    ResourceManager res(argv[0]);
    auto pFirst_ShaderProgram = res.load_shader("First_ShaderProgram", "res/Shaders/vertexShader.txt", "res/Shaders/fragmentShader.txt");
    glBindVertexArray(0);

    std::cerr << "1\n";

    auto brick = res.load_texture("brick", "res/textures/brick.png");

    std::cerr << "2\n";

    auto smile = res.load_texture("smile", "res/textures/smile.png");

    std::cerr << "end\n";



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, brick->Give_ID());
        glUniform1i(glGetUniformLocation(pFirst_ShaderProgram->Give_Id(), "ourTexture1"), 0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, smile->Give_ID());
        glUniform1i(glGetUniformLocation(pFirst_ShaderProgram->Give_Id(), "ourTexture2"), 1);

        pFirst_ShaderProgram->use_ShaderProgram();

        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
        transform = glm::rotate(transform, (GLfloat)glfwGetTime() * 5.0f, glm::vec3(1.0f, 1.0f, 1.0f));
        // Get matrix's uniform location and set matrix
        GLint transformLoc = glGetUniformLocation(pFirst_ShaderProgram->Give_Id(), "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &ibo);

    glfwTerminate();
    return 0;
}