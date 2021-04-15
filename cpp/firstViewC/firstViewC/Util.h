#pragma once
#ifndef UTIL_H
#define UTIL_H

#define GLEW_STATIC
#include"glew.h"
#include"glfw3.h"
#include<iostream>
#include <typeinfo>

class Util {
	public:
	
		static GLint vertexAttrAlloweds() {
			GLint numVertexAttribs;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numVertexAttribs);
			std::cout << numVertexAttribs << std::endl;
			return 0;
		}

		static void log(const char * message) {
			std::cout << message << std::endl;
		}

};

#endif // !UTIL_H