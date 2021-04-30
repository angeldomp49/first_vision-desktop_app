#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#include "Util.h"
#include "Shader.cpp"
#include <iostream>
#include"GContainer.cpp"

class ShaderProgram {
	public:
		GContainer<GLuint>* shaders;
		GLuint program;

		ShaderProgram() {
			this->program = glCreateProgram();
			this->shaders = new GContainer<GLuint>(100);
		}
		
		void addShader(GLuint cshader) {
			this->shaders->push(cshader);
		}

		void link() {
			this->attachShaders();
			glLinkProgram(this->program);
			this->deleteShaders();
		}

		void use() {
			glUseProgram(this->program);
		}

		void clean() {
			glDeleteProgram(this->program);
		}

		void attachShaders() {
			for (unsigned int i = 0; i < this->shaders->size; i++) {
				glAttachShader(this->program, this->shaders->get(i));
			}
		}

		void deleteShaders() {
			for (GLuint i = 0; i < this->shaders->size; i++) {
				glDeleteShader(this->shaders->get(i));
			}
			
			free(this->shaders);
		}
};
#endif