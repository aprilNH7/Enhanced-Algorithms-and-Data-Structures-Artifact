#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <glad/glad.h>
#include <glm.hpp>

class Buffer {
public:
    Buffer(GLenum type);
    ~Buffer();

    void bind();
    void unbind();
    void setData(const void* data, GLsizeiptr size, GLenum usage);

private:
    GLuint ID;
    GLenum bufferType;
};

class Object3D {
public:
    Object3D(float* vertices, float* colors, unsigned int* indices, size_t vertexSize, size_t colorSize, size_t indexSize);
    ~Object3D();

    void draw(GLuint shaderProgram);

private:
    Buffer VBO;
    Buffer CBO;
    Buffer EBO;
    unsigned int indicesCount;
};

#endif
