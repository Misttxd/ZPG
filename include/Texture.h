#pragma once

#include <glad/gl.h>

class Texture
{
public:
    explicit Texture(const char* path);
    explicit Texture(const char* const (&paths)[6]);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    GLuint getId() const { return id; }

private:
    GLuint id;
};

GLuint loadTexture(const char* path);
GLuint loadCubemap(const char* const (&paths)[6]);