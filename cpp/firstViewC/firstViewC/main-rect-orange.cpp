
#define GLEW_STATIC

#include"glew.h"
#include"glfw3.h"

//#include "Shape.cpp"

#include<iostream>

void init(void);
void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode);

GLFWwindow* window;

int main() {
    init();

    ///////////////////////////////////////////////////////////////////////////////////////////////

    const char* vertexShaderSource = "#version 330 core\n"
        "in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    ///////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////

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

    //Shape* rectangle = new Shape();

    GLuint vertexArrayObject, vertexBufferObject, elementBufferObject;
    GLint drawType;
    GLint polygonMode;
    GLint figureType;

    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &elementBufferObject);

    drawType = GL_STATIC_DRAW;
    polygonMode = GL_FILL;
    figureType = GL_TRIANGLES;

    //rectangle->points = new GContainer<GLfloat>(vertices, 12);
    //rectangle->indices = new GContainer<GLuint>(indices, 6);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, drawType);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, drawType);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    ////////////////////////////////////////////////////////////////////////////////////////////////

    //rectangle->prepare();

    while (!glfwWindowShouldClose(window)){
        //rectangle->render();

        glUseProgram(shaderProgram);

        glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
        glBindVertexArray(vertexArrayObject);
        glDrawElements(figureType, 6, GL_UNSIGNED_INT, 0);               //////////////////////////////numero de elementos
        glBindVertexArray(0);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    //rectangle->clean();

    glfwTerminate();
    return 0;
}

void init() {
    if (!glfwInit()) {
        return;
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

    if (nullptr == window)
    {
        glfwTerminate();
        std::cout << "Failed to create Window object" << std::endl;
        return;
    }

    glfwMakeContextCurrent(window);


    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return;
    }

    glViewport(0, 0, 800, 600);

    glfwSetKeyCallback(window, closeOnEsc);
}

void closeOnEsc(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}