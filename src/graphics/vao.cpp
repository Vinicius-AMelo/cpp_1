#include <graphics/vao.h>

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::bind() const {
	glBindVertexArray(ID);
}

void VAO::unbind() const {
	glBindVertexArray(0);
}

void VAO::setVertexAttributes(GLuint index, GLsizeiptr size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) const {
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
	glEnableVertexAttribArray(index);
}

void VAO::terminate() const {
	glDeleteVertexArrays(1, &ID);
}