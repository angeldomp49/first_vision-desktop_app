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
	private:
	public:
		std::string code;
		GLuint obj;

		Shader(const GLchar* shaderFilePath) {
			this->obj = 0;

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
				shaderFile.close();

				this->code = shaderStream.str();
			}
			catch (std::ifstream::failure e) {
				throw new std::exception("Error opening file");
			}
			catch (std::exception e) {
				throw new std::exception("unknown error: ");
			}
		}

		void compile() {
			GLint success;
			GLchar infoLog[512];
			const GLchar* scode = this->code.c_str();

			this->obj = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(this->obj, 1, &scode, NULL);
			glCompileShader(this->obj);
			glGetShaderiv(this->obj, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(this->obj, 512, NULL, infoLog);
				throw new std::exception("Error compiling shader");
			}
		}

		GLuint getObject() {
			return this->obj;
		}
};

#endif // !CUSTOM_SHADER_H