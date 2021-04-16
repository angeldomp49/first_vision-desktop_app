#ifndef SHAPE_H
#define SHAPE_H
#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#pragma once
class Shape
{
public:
	GLfloat points[100];
	GLuint vertexArrayObject, vertexBufferObject, elementBufferObject;
	GLint type;

	Shape(GLfloat points[], GLuint indexes[], GLint figureType);
	Shape(GLfloat points[], GLuint indexes[]);
	void prepare(void);
	void bindBuffers(void);
	void loadPoints(void);
	void enable(void);
	void render(void);
	void clean(void);
};

#endif // !SHAPE_H