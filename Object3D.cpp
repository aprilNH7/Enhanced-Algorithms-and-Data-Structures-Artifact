#include "Object3D.h"
#include <gtc/type_ptr.hpp>
Buffer::Buffer(GLenum type) : bufferType(type) {
    glGenBuffers(1, &ID);
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &ID);
}

void Buffer::bind() {
    glBindBuffer(bufferType, ID);
}

void Buffer::unbind() {
    glBindBuffer(bufferType, 0);
}

void Buffer::setData(const void* data, GLsizeiptr size, GLenum usage) {
    bind();
    glBufferData(bufferType, size, data, usage);
}

// Object3D Class Implementation
Object3D::Object3D(float* vertices, float* colors, unsigned int* indices, size_t vertexSize, size_t colorSize, size_t indexSize)
    : VBO(GL_ARRAY_BUFFER), CBO(GL_ARRAY_BUFFER), EBO(GL_ELEMENT_ARRAY_BUFFER), indicesCount(indexSize / sizeof(unsigned int)) {
    VBO.setData(vertices, vertexSize, GL_STATIC_DRAW);
    CBO.setData(colors, colorSize, GL_STATIC_DRAW);
    EBO.setData(indices, indexSize, GL_STATIC_DRAW);
}

Object3D::~Object3D() {}

void Object3D::draw(GLuint shaderProgram) {
    glUseProgram(shaderProgram);

    VBO.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    CBO.bind();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    EBO.bind();
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}
