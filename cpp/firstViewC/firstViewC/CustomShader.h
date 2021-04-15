#pragma once
#ifndef CUSTOM_SHADER_H
#define CUSTOM_SHADER_H

#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#include "Util.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

class CustomShader {
	private:
	public:
		const GLchar* code;
		GLuint shaderObject;
		


		CustomShader(const GLchar* shaderFilePath) {
			this->openFile(shaderFilePath);
			this->compile();
		}

		void openFile(const GLchar* shaderFilePath) {
			std::ifstream shaderFile;
			std::stringstream shaderStream;

			shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit );
			try {
				shaderFile.open(shaderFilePath);
				shaderStream << shaderFile.rdbuf();
				std::cout << shaderFile.rdbuf() << std::endl;
				shaderFile.close();
				this->code = shaderStream.str().c_str();
			}
			catch (std::ifstream::failure e) {
				std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
				exit(-1);
			}
		}
		void compile() {
			GLint success;
			GLchar infoLog[512];

			this->shaderObject = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(this->shaderObject, 1, &this->code, NULL);
			glCompileShader(this->shaderObject);
			glGetShaderiv(this->shaderObject, GL_COMPILE_STATUS, &success);

			if (!success) {
				glGetShaderInfoLog(this->shaderObject, 512, NULL, infoLog);
				std::cout << "ERROR::COMPILING VERTEX SHADER : " << infoLog << std::endl;
				exit(-1);
			}
		}
};

#endif // !CUSTOM_SHADER_H