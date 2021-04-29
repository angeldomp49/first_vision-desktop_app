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

GLFWwindow* window;
GLuint vertexArrayObject, vertexBufferObject, elementBufferObject;
GLint drawType;
GLint polygonMode;
GLint figureType;
GLuint program;

const GLchar* code;
GLuint vshaderObject;

const GLchar* code2;
GLuint fshaderObject;

int main(void) {
	init();
	
    ////////////////////////////////////////////////////////////////////////////////////
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open("vertex.vert");
        shaderStream << shaderFile.rdbuf();
        std::cout << shaderFile.rdbuf() << std::endl;
        shaderFile.close();
        code = shaderStream.str().c_str();
    }
    catch (std::ifstream::failure e) {
        throw new std::exception("Error opening file");
    }

    GLint success;
    GLchar infoLog[512];

    vshaderObject = glCreateShader(GL_VERTEX_SHADER);
    vshaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshaderObject, 1, &code, NULL);
    glCompileShader(vshaderObject);
    glGetShaderiv(vshaderObject, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vshaderObject, 512, NULL, infoLog);
        throw new std::exception("Error compiling shader");
    }
    ////////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////////
    std::ifstream shaderFile2;
    std::stringstream shaderStream2;

    shaderFile2.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile2.open("fragment.frag");
        shaderStream2 << shaderFile2.rdbuf();
        std::cout << shaderFile2.rdbuf() << std::endl;
        shaderFile2.close();
        code2 = shaderStream2.str().c_str();
    }
    catch (std::ifstream::failure e) {
        throw new std::exception("Error opening file");
    }

    GLint success2;
    GLchar infoLog2[512];

    fshaderObject = glCreateShader(GL_VERTEX_SHADER);
    fshaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fshaderObject, 1, &code2, NULL);
    glCompileShader(fshaderObject);
    glGetShaderiv(fshaderObject, GL_COMPILE_STATUS, &success2);

    if (!success) {
        glGetShaderInfoLog(fshaderObject, 512, NULL, infoLog2);
        throw new std::exception("Error compiling shader");
    }
    ////////////////////////////////////////////////////////////////////////////////////


    program = glCreateProgram();

    glAttachShader(program, vshaderObject);
    glAttachShader(program, fshaderObject);

    glLinkProgram(program);

    glDeleteShader(vshaderObject);
    glDeleteShader(fshaderObject);

    GLfloat vertices[] = {
        -0.5f,  0.5f, 0.0f, //top left
         0.5f,  0.5f, 0.0f, //top right
        -0.5f, -0.5f, 0.0f, //bottom left
         0.5f, -0.5f, 0.0f  //bottom right
    };

    GLuint indices[] = {
        0,1,2,
        1,2,3
    };

    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &elementBufferObject);

    drawType = GL_STATIC_DRAW;
    polygonMode = GL_FILL;
    figureType = GL_TRIANGLES;

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);


    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, drawType);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, drawType);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);


    while (!glfwWindowShouldClose(window)) {
        
        glUseProgram(program);

        glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
        glBindVertexArray(vertexArrayObject);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);

    glDeleteProgram(program);

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