#include <graphics/ebo.h>

EBO::EBO() {
	glGenBuffers(1, &ID);
}

void EBO::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::setData(GLsizeiptr size, const void* data, GLenum usage) const {
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
}

void EBO::terminate() const {
	glDeleteBuffers(1, &ID);
}
