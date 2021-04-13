#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"

#include<iostream>

int init();
void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode);
int fillColor(void);
int drawTriangle(void);
int vertexAndBufferInit(void);
int howManyVertexAttrs(void);
int prepareTriangle(void);
int drawTriangle2(void);
int clean(void);
int enable(void);

GLFWwindow* window;
GLuint VBO;
GLuint VAO;
GLuint vertexShader;
GLuint fragmentShader;
GLuint shaderProgram;
GLfloat vertices[] = {
-0.5f, -0.5f, 0.0f,
0.5f,  -0.5f, 0.0f,
0.0f,  0.5f,  0.0f
};
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main(void)
{
    init();
    prepareTriangle();
    vertexAndBufferInit();
    enable();

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        fillColor();
        drawTriangle2();
        glfwSwapBuffers(window);
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

    glViewport(200, 100, 800, 600);

    glfwSetKeyCallback(window, closeOnEsc);
    return 0;
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

int drawTriangle() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    return 0;
}

int vertexAndBufferInit() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    return 0;
}

int howManyVertexAttrs() {
    GLint numAttrs;
    glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &numAttrs );
    std::cout << "" << numAttrs << std::endl;
    return 0;
}

int prepareTriangle() {
    
    vertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader( shaderProgram, vertexShader );
    glAttachShader( shaderProgram, fragmentShader );
    glLinkProgram( shaderProgram );

    glDeleteShader( vertexShader );
    glDeleteShader( fragmentShader );
    return 0;
}

int drawTriangle2() {
    glUseProgram( shaderProgram );
    glBindVertexArray( VAO );
    glDrawArrays( GL_TRIANGLES, 0, 3 );
    return 0;
}

int enable() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return 0;
}

int clean() {
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    glDeleteProgram( shaderProgram );
    return 0;
}