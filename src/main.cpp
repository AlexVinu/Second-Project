#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/ShaderProgram.h"
#include "buffers/vbo.h"
#include "resources/ResourceManager.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "C:/OpenGL/Second-Project/res/stb_image.h"

extern "C" {
    _declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;    // For NVidia
    // __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1; // For AMD
}



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

    //Buffers::VertexBufferObject vbo;

    Buffers::VertexBufferObject vbo;
    ResourceManager res(argv[0]);
    auto pFirst_ShaderProgram = res.load_shader("First_ShaderProgram", "res/Shaders/vertexShader.txt", "res/Shaders/fragmentShader.txt");
    glBindVertexArray(0);

    GLuint textures = 0;
    glGenTextures(1, &textures);
    glBindTexture(GL_TEXTURE_2D, textures);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int width;
    int height;
    int channels;
    auto image = res.load_texture("res/textures/brick.png", width, height, channels);

    if (!image) {
        std::cerr << "Image don`t downloaded\n";
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, textures);
        pFirst_ShaderProgram->use_ShaderProgram();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}