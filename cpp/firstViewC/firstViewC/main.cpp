#define GLEW_STATIC
#include"glew.h"
#include "glfw3.h"

#include<iostream>

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }

    //glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );

    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (nullptr == window)
    {
        glfwTerminate();
        std::cout << "Failed to create Window object" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);


    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glViewport(200, 100, 800, 600);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}