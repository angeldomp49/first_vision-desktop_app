#ifndef SHAPE_CPP
#define SHAPE_CPP
#pragma once

#define GLEW_STATIC

#include "glew.h"
#include "GContainer.cpp"

class Shape {
public:
	const GContainer<GLfloat>* points;
	const GContainer<GLuint>* indexes;
	GLuint vertexArrayObject, vertexBufferObject, elementBufferObject;
	GLint drawType;
	GLint polygonMode;
	GLint figureType;

	Shape(GContainer<GLfloat> points[], GContainer<GLuint> indexes[], GLint figureType) {
		glGenVertexArrays(1, &this->vertexArrayObject);
		glGenBuffers(1, &this->vertexBufferObject);
		glGenBuffers(1, &this->elementBufferObject);

		this->drawType = GL_STATIC_DRAW;
		this->polygonMode = GL_FILL;
		this->figureType = figureType;

		this->points = points;
		this->indexes = indexes;
	}

	Shape(GContainer<GLfloat> points[], GContainer<GLuint> indexes[]) {
		glGenVertexArrays(1, &this->vertexArrayObject);
		glGenBuffers(1, &this->vertexBufferObject);
		glGenBuffers(1, &this->elementBufferObject);

		this->drawType = GL_STATIC_DRAW;
		this->polygonMode = GL_FILL;
		this->figureType = GL_TRIANGLES;

		this->points = points;
		this->indexes = indexes;
	}

	Shape(GLfloat points[], unsigned int numPoints, GLuint indices[], unsigned int numIndices) {
		glGenVertexArrays(1, &this->vertexArrayObject);
		glGenBuffers(1, &this->vertexBufferObject);
		glGenBuffers(1, &this->elementBufferObject);

		this->drawType = GL_STATIC_DRAW;
		this->polygonMode = GL_FILL;
		this->figureType = GL_TRIANGLES;

		this->points = new GContainer<GLfloat>(points, numPoints);
		this->indexes = new GContainer<GLuint>(indices, numIndices);
	}

	Shape() {

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
		glBufferData(GL_ARRAY_BUFFER, this->points->size, this->points->items, this->drawType);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexes->size, this->indexes->items, this->drawType);
	}

	void enable() {
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	void render() {
		glPolygonMode(GL_FRONT_AND_BACK, this->polygonMode);
		glBindVertexArray(this->vertexArrayObject);
		glDrawElements(this->figureType, this->indexes->size, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void clean() {
		glDeleteVertexArrays(1, &this->vertexArrayObject);
		glDeleteBuffers(1, &this->vertexBufferObject);
		glDeleteBuffers(1, &this->elementBufferObject);
	}
};

#endif // !SHAPE_CPP