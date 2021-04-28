#define GLEW_STATIC
#include"glew.h"
#include"glfw3.h"
#include"CustomShader.h"
#include"CustomProgram.h"
#include <iostream>
#include"GContainer.cpp"
#include "Shape.cpp"

int init();
void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode);
void render();

GLFWwindow* window;

int main(void){
    init();

    GLfloat v[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    GLuint i[] = {
        0, 1, 3,
        1, 2, 3
    };

	GContainer<GLfloat>* vertices = new GContainer<GLfloat>(v,9);
    GContainer<GLuint>* indices = new GContainer<GLuint>(i, 6);

    Shape* rectangle = new Shape(vertices, indices);
    rectangle->prepare();

    CustomShader* vshader = new CustomShader("vertex.vert");
    CustomShader* fshader = new CustomShader("fragment.frag");

    CustomProgram* p = new CustomProgram();

    p->addShader(*vshader);
    p->addShader(*fshader);

    p->link();

    while (!glfwWindowShouldClose(window))
    {
        p->use();
        rectangle->render();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    rectangle->clean();
    p->cleanProgram();

    glfwTerminate();
    return 0;

}

int init() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
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

    glfwSetKeyCallback(window, closeOnEsc);
    return 0;
}

void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void render() {
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}
