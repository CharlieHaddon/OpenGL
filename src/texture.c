#include "texture.h"

GLuint textureCreate(GLchar* imagePath){
    /* Load image */
    int texWidth, texHeight;
    unsigned char* image = SOIL_load_image (imagePath, &texWidth, &texHeight, 
            0, SOIL_LOAD_RGB);

    /* Bind texture */
    GLuint texture;
    glGenTextures (1, &texture);
    glBindTexture (GL_TEXTURE_2D, texture);

    /* Texture parameters */
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Send texture data */
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB,
            GL_UNSIGNED_BYTE, image);
    glGenerateMipmap (GL_TEXTURE_2D);

    /* Cleanup */
    SOIL_free_image_data (image);
    glBindTexture (GL_TEXTURE_2D, 0);
    glActiveTexture (0);

    return texture;
}
