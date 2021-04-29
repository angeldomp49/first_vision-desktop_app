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

int main(void) {
	init();
	
    CustomProgram* p = new CustomProgram();
	CustomShader* vshader = new CustomShader("vertex.vert");
	CustomShader* fshader = new CustomShader("fragment.frag");

	p->addShader(*vshader);
	p->addShader(*fshader);

    p->link();

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    GLuint indices[] = {
        0,1,3,
        1,2,3
    };


    ///////////////////////////////////////////////////////////////////////
    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &elementBufferObject);

    drawType = GL_STATIC_DRAW;
    polygonMode = GL_FILL;
    figureType = GL_TRIANGLES;

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, drawType);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, drawType);



    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    ///////////////////////////////////////////////////////////////////////

    while (!glfwWindowShouldClose(window)) {
        
        p->use();
        glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
        glBindVertexArray(vertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &elementBufferObject);
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