#pragma once
#ifndef CUSTOM_PROGRAM_H
#define CUSTOM_PROGRAM_H

#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#include "Util.h"
#include "CustomShader.h"
#include <iostream>
#include"GContainer.cpp"

class CustomProgram {
	public:
		GContainer<CustomShader>* shaders;
		GLuint program;

		CustomProgram() {
			this->shaders = new GContainer<CustomShader>(10);
		}
		
		void addShader(CustomShader cshader) {
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

		void cleanProgram() {
			glDeleteProgram(this->program);
		}

		void attachShaders() {
			for (unsigned int i = 0; i < this->shaders->size; i++) {
				glAttachShader(this->program, this->shaders->get(i).getObject());
			}
		}

		void deleteShaders() {
			this->shaders = nullptr;
		}
};
#endif