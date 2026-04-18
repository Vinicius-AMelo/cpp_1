#pragma once
#include <glad/glad.h>

class EBO {

public:
	unsigned int ID;

	EBO();

	void bind() const;
	void unbind() const;
	void setData(GLsizeiptr size, const void* data, GLenum usage) const;
	void terminate() const;
};