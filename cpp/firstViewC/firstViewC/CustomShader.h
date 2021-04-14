#pragma once
#ifndef CUSTOM_SHADER_H
#define CUSTOM_SHADER_H

#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>/*61*/

class CustomShader {
	public:
		GLuint program;
		CustomShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath);
		void use();

		CustomShader(const GLchar* vertexSourcePath, const GLchar* fragmentSourcePath) {
			std::string vertexCode;
			std::string fragmentCode;
			std::ifstream vShaderFile;
			std::ifstream fShaderFile;

			vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		}
};

#endif // !CUSTOM_SHADER_H