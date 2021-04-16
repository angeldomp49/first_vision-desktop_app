#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#include "Util.h"
#include "CustomProgram.h"
#include <iostream>

int init(void);
void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode);

int prepare(void);
int prepareVertexArrayObjects(void);
int prepareVertexBufferObjects(void);
int prepareElementBufferObjects(void);

int sendBufferData(void);

void render(void);
int fillColor(void);
int changeColor(void);

int clean(void);


GLFWwindow* window;

GLuint vertexBufferObject;
GLuint vertexArrayObject;
GLuint vertexShader;
GLuint elementBufferObject;
GLuint fragmentShader;
GLuint shaderProgram;

CustomProgram* cp;

GLfloat vertices[] = {
-0.5f,  -0.5f,  0.0f,
 0.5f,  -0.5f,  0.0f,
 0.0f,   0.5f,  0.0f
};
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

int main(void)
{
    init();
    prepare();

    while (!glfwWindowShouldClose(window))
    {
        render();
    }
    clean();

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

    glViewport(0, 0, 800, 600);

    glfwSetKeyCallback(window, closeOnEsc);
    return 0;
}
void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int prepare() {
    prepareVertexArrayObjects();
    prepareVertexBufferObjects();
    sendBufferData();
    prepareElementBufferObjects();

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    return 0;
}
int prepareVertexArrayObjects() {
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    return 0;
}
int prepareVertexBufferObjects() {
    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    return 0;
}
int prepareElementBufferObjects() {
    glGenBuffers(1, &elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesRectangle), indicesRectangle, GL_STATIC_DRAW);
    return 0;
}

int sendBufferData() {
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesRectangle), verticesRectangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    return 0;
}

void render() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glfwPollEvents();
    fillColor();
    changeColor();
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glfwSwapBuffers(window);
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
int clean() {
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    return 0;
}