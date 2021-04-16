#ifndef UTIL_H
#define UTIL_H
#pragma once
class Util
{
	public:
		static GLint vertexAttrAlloweds(void);
		static GLuint* createArr(GLuint arrTest[]);
		static unsigned int getSize(GLuint arr[]);
		static GLuint* pointerFromSize(unsigned int size);
		static void test();
};
#endif // !UTIL_H