#ifndef SHAPE_CPP
#define SHAPE_CPP
#pragma once

#define GLEW_STATIC

#include "glew.h"

class Shape {
public:
	const GLfloat* points[100];
	const GLuint* indexes[100];
	GLuint vertexArrayObject, vertexBufferObject, elementBufferObject;
	GLint drawType;
	GLint polygonMode;
	GLint figureType;

	Shape(const GLfloat points[], const GLuint indexes[], GLint figureType) {
		glGenVertexArrays(1, &this->vertexArrayObject);
		glGenBuffers(1, &this->vertexBufferObject);
		glGenBuffers(1, &this->elementBufferObject);

		this->drawType = GL_STATIC_DRAW;
		this->polygonMode = GL_FILL;
		this->figureType = figureType;

		*this->points = points;
		*this->indexes = indexes;
	}

	Shape(const GLfloat points[], const GLuint indexes[]) {
		glGenVertexArrays(1, &this->vertexArrayObject);
		glGenBuffers(1, &this->vertexBufferObject);
		glGenBuffers(1, &this->elementBufferObject);

		this->drawType = GL_STATIC_DRAW;
		this->polygonMode = GL_FILL;
		this->figureType = GL_TRIANGLES;

		*this->points = points;
		*this->indexes = indexes;
	}

	void prepare() {
		this->bindBuffers();
		this->loadPoints();
		this->enable();
	}

	void bindBuffers() {
		glBindVertexArray(this->vertexArrayObject);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);
	}

	void loadPoints() {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indexes), this->indexes, this->drawType );
	}

	void enable() {
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	void render() {
		glPolygonMode(GL_FRONT_AND_BACK, this->polygonMode);
		glBindVertexArray(this->vertexArrayObject);
		glDrawElements(this->figureType, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void clean() {
		glDeleteVertexArrays(1, &this->vertexArrayObject);
		glDeleteBuffers(1, &this->vertexBufferObject);
	}
};

#endif // !SHAPE_CPP