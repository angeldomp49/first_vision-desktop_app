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
void listeningESCKey(GLFWwindow* window);

GLFWwindow* window;

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

    Shape* sh = new Shape(vertices, 9, indices, 6);

    sh->prepare();

    while (!glfwWindowShouldClose(window)) {
        
        p->use();
        sh->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    sh->clean();
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

void listeningESCKey(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void render() {
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}