#pragma once
#include <glad/glad.h>

class VAO {

public:
	unsigned int ID;

	VAO();

	void bind() const;
	void unbind() const;
	void setVertexAttributes(GLuint index, GLsizeiptr size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) const;
	void terminate() const;
};