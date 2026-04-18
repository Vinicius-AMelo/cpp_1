#include <graphics/vbo.h>

VBO::VBO() {
	glGenBuffers(1, &ID);
}

void VBO::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::setData(GLsizeiptr size, const void* data, GLenum usage) const {
	glBufferData(GL_ARRAY_BUFFER, size, data, usage);
}

void VBO::terminate() const {
	glDeleteBuffers(1, &ID);
}
