


///////////////////////////////////////////////////////////////////////
glGenVertexArrays(1, &vertexArrayObject);
glGenBuffers(1, &vertexBufferObject);
glGenBuffers(1, &elementBufferObject);

drawType = GL_STATIC_DRAW;
polygonMode = GL_FILL;
figureType = GL_TRIANGLES;

glBindVertexArray(vertexArrayObject);
glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);


glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, drawType);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, drawType);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);

glBindBuffer(GL_ARRAY_BUFFER, 0);

glBindVertexArray(0);

///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
glBindVertexArray(vertexArrayObject);
glDrawArrays(GL_TRIANGLES, 0, 6);
glBindVertexArray(0);

///////////////////////////////////////////////////////////////////////