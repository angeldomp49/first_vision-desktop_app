#ifndef UTIL_CPP
#define UTIL_CPP		

#define GLEW_STATIC
#include"glew.h"
#include<iostream>
#include<vector>

class Util {
public:

	static GLint vertexAttrAlloweds() {
		GLint numVertexAttribs;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numVertexAttribs);
		std::cout << numVertexAttribs << std::endl;
		return 0;
	}

	static GLuint* createArr( GLuint arrTest[] ) {
		unsigned int size = getSize(arrTest);
		GLuint* container = pointerFromSize(size);
	}

	static unsigned int getSize(GLuint arr[]) {
		unsigned int size;
		size = sizeof(arr);
		return size;
	}

	static GLuint* pointerFromSize(unsigned int size) {
		return (GLuint*)malloc(size);
	}

};


#endif // !UTIL_CPP