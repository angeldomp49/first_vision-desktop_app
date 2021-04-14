#pragma once
#ifndef UTIL_H
#define UTIL_H

#define GLEW_STATIC
#include"glew.h"
#include"glfw3.h"
#include<iostream>

class Util {
	public:
	
		static GLint vertexAttrAlloweds() {
			GLint numVertexAttribs;
			glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numVertexAttribs);
			std::cout << numVertexAttribs << std::endl;
			return 0;
		}

};

#endif // !UTIL_H