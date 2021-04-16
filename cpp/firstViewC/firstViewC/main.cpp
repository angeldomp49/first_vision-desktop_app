#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#include "Shape.h"
#include "Util.h"
#include <iostream>

void init(void);
void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode);

int fillColor(void);
int changeColor(void);

void test1(void);
void test2(void);


GLFWwindow* window;

GLuint fragmentShader;
GLuint shaderProgram;

int main(void)
{
    test2();
    return 0;
}

void init() {

    if (!glfwInit()) {
        throw new std::exception("Railed to initializing GLFW");
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

    if (nullptr == window)
    {
        glfwTerminate();
        throw new std::exception("Error creating window");
    }

    glfwMakeContextCurrent(window);


    if (GLEW_OK != glewInit()) {
        throw new std::exception("Failed to initialize GLEW");
    }

    glViewport(0, 0, 800, 600);

    glfwSetKeyCallback(window, closeOnEsc);
}
void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int fillColor() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    return 0;
}
int changeColor() {
    GLfloat timeSeconds = glfwGetTime();
    GLfloat greenValue = (sin(timeSeconds) / 2) + 0.5;
    GLint vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
    return 0;
}

void test1() {
    init();

    GLuint indicesRectangle[] = {
    0,1,3,
    1,2,3
    };
    GLfloat verticesRectangle[] = {
     0.5f,    0.5f,   0.0f,
     0.5f,   -0.5f,   0.0f,
    -0.5f,   -0.5f,   0.0f,
    -0.5f,    0.5f,   0.0f
    };

    Shape* rectangle = new Shape(verticesRectangle, indicesRectangle);
    rectangle->prepare();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        fillColor();
        changeColor();
        rectangle->render();
        glfwSwapBuffers(window);
    }
    rectangle->clean();

    glfwTerminate();
}

void test2() {
    Util::test();
}