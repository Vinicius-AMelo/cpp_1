#pragma once
#include <glad/glad.h>

class VBO {

public:
	unsigned int ID;

	VBO();

	void bind() const;
	void unbind() const;
	void setData(GLsizeiptr size, const void* data, GLenum usage) const;
	void terminate() const;
};