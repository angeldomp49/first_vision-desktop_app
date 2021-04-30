#pragma once
#ifndef CUSTOM_SHADER_H
#define CUSTOM_SHADER_H

#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

class Shader {
	
	public:

		GLuint type;
		GLuint obj;
		std::string code;

		Shader(const GLchar* shaderFilePath, GLint type) {
			this->type = type;
			this->openFile(shaderFilePath);
			this->compile();
		}

		void openFile(const GLchar* shaderFilePath) {
			std::ifstream shaderFile(shaderFilePath);
			std::string content;

			shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit );
			try {
				content.assign(
				(std::istreambuf_iterator<char>(shaderFile)),
				(std::istreambuf_iterator<char>())
				);
				
				this->code = content;

				shaderFile.close();
			}
			catch (std::ifstream::failure e) {
				std::cout << "Error reading file" << std::endl;
			}
			catch (std::exception e) {
				std::cout << "Error unknown: " << std::endl;
			}
		}

		void compile() {

			GLint success;
			GLchar infoLog[512];
			GLuint obj = glCreateShader(this->type);
			const GLchar* f = this->code.c_str();
			
			glShaderSource(obj, 1, &f, NULL);
			glCompileShader(obj);

			glGetShaderiv(obj, GL_COMPILE_STATUS, &success);

			if (!success) {
				glGetShaderInfoLog(obj, 512, NULL, infoLog);
				std::cout << "Error compiling shader: \n" << infoLog << std::endl;
			}

			if (GL_FALSE == glIsShader(obj)) {
				std::cout << "obj is not shader: "<<std::hex <<this->type << std::endl;
			}

			this->obj = obj;
			free((void*)f);
		}
};

#endif // !CUSTOM_SHADER_H