#pragma once
#ifndef CUSTOM_PROGRAM_H
#define CUSTOM_PROGRAM_H

#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#include "Util.h"
#include "CustomShader.h"
#include <iostream>

class CustomProgram {
	public:
		GLuint* shaders;
		unsigned int numberShaders;
		GLuint program;

		CustomProgram() {
			this->numberShaders = 0;
			this->shaders = nullptr;
		}
		
		void attachShader(CustomShader *cshader) {
			GLuint * container;
			try {
			this->numberShaders++;
			container = this->container(this->numberShaders);
			
			container[this->numberShaders -1] = cshader->shaderObject;
			this->shaders = container;
			}
			catch () {

			}
		}

		void link() {
			this->attachShaders();
			glLinkProgram(this->program);
			this->deleteShaders();
		}

		void use() {
			glUseProgram(this->program);
		}

		void cleanProgram() {
			glDeleteProgram(this->program);
		}

		void attachShaders() {
			for (unsigned int i = 0; i < this->numberShaders -1; i++) {
				glAttachShader(this->program, this->shaders[i]);
			}
		}

		void deleteShaders() {
			for (unsigned int i = 0; i < this->numberShaders -1; i++) {
				glDeleteShader(this->shaders[i]);
			}
		}

		void test() {
			CustomShader* vertex = new CustomShader("vertex.vert");
			this->attachShader(vertex);

			CustomShader* fragment = new CustomShader("fragment.frag");
			this->attachShader(fragment);

			this->link();
		}

		GLuint* container(unsigned int size) {
			GLuint* container;
			container = (GLuint*)malloc(size + 1);
			container[size] = '\0';
			return container;
		}

};
#endif