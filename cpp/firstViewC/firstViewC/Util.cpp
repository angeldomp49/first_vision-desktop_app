#ifndef UTIL_CPP
#define UTIL_CPP		

#define GLEW_STATIC
#include"glew.h"
#include<iostream>

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

	static void test() {
		GLuint a[20];
		a[0] = 1;
		a[1] = 2;

		unsigned int size = getSize(a);

		std::cout << size << std::endl;
	}

};


#endif // !UTIL_CPP