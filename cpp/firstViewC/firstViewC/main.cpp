#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"

#include<iostream>

#include"Util.h"
#include"CustomShader.h"

int init(void);
void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode);

int prepare(void);
int prepareShaders(void);
int prepareVertexArrayObjects(void);
int prepareVertexBufferObjects(void);
int prepareElementBufferObjects(void);

int sendBufferData(void);
void errorInShader(GLuint shaderObj);

void render(void);
int fillColor(void);
int drawTriangle(void);
int drawRectangle(void);
int changeColor(void);

int clean(void);


GLFWwindow* window;

GLuint vertexBufferObject;
GLuint vertexArrayObject;
GLuint vertexShader;
GLuint elementBufferObject;
GLuint fragmentShader;
GLuint shaderProgram;

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

const char* vertexShaderSource = "#version 330 core\n"
"in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 color;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"    color = ourColor;\n"
"}\0";

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
    prepareShaders();
    prepareVertexArrayObjects();
    prepareVertexBufferObjects();
    sendBufferData();
    prepareElementBufferObjects();

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    return 0;
}
int prepareShaders() {

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);


    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindAttribLocation(shaderProgram, 0, "location");

    glLinkProgram(shaderProgram);

    errorInShader(vertexShader);
    errorInShader(fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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

void errorInShader(GLuint shaderObj) {
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderObj, 512, NULL, infoLog);
        std::cout << "error al compilar el shader: " << infoLog << std::endl;
    }
}

void render() {
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glfwPollEvents();
    fillColor();
    changeColor();
    drawRectangle();
    glfwSwapBuffers(window);
}
int fillColor() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    return 0;
}
int drawTriangle() {
    glUseProgram( shaderProgram );
    glBindVertexArray(vertexArrayObject);
    glDrawArrays( GL_TRIANGLES, 0, 3 );
    glBindVertexArray(0);
    return 0;
}
int drawRectangle() {
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
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
    glDeleteVertexArrays( 1, &vertexArrayObject);
    glDeleteBuffers( 1, &vertexBufferObject );
    glDeleteProgram( shaderProgram );
    return 0;
}
