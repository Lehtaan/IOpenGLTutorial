//
//  Header.h
//  IOpenGLTutorial
//
//  Created by Janis Böhm on 18/09/15.
//  Copyright (c) 2015 Janis Böhm. All rights reserved.
//

#ifndef IOpenGLTutorial_Header_h
#define IOpenGLTutorial_Header_h

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool running = false;
float m_ratio;
float m;

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

glm::vec2 ship_pos = glm::vec2(0.0, 0.0);

void key_callback()
{
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) || glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_1))
    {
        if (!running) {
            running = true;
            ship_pos.x = 0;
            ship_pos.y = -1.4;
        }

    }
    
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_ESCAPE)) {
        running = false;
        m = 1.0;
        ship_pos.x = 0;
    }
    
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) && running)
    {
        if (ship_pos.x >= (-m_ratio)-0.25) ship_pos.x -= 0.04;
    }
    
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) && running)
    {
        if (ship_pos.x <=  m_ratio + 0.25) ship_pos.x += 0.04;
    }
}

#pragma Buffer_Data

GLuint elements[] = {
    6, 7, 8, 9
};
GLuint elements2[] = {
    0, 1, 2, 3
};
GLuint elements3[]  = {
    10, 11, 12, 13
};

GLuint ufoments[] = {
    14,15,16,17
};

/*
 
 -1.0f,  1.0f,   1.0f, 1.0f, 1.0f,   0.0f, -0.5f, // Top-left-Top 6
  1.0f,  1.0f,   1.0f, 1.0f, 1.0f,   2.0f, -0.5f, // top-right-top 7
  1.0f, -1.0f,   1.0f, 1.0f, 1.0f,   2.0f,  1.5f, // bot-right-bot 8
*/


float vertices[] = {
    //Position      //Color             //Texture
    -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, // Top-left 0
     0.5f,  0.5f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f, // Top-right 1
     0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   1.0f,  1.0f, // Bottom-right 2
    -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f, // Bottom-left 3
     0.0f,  0.5f,   1.0f, 1.0f, 1.0f,   0.5f,  0.0f, // Top 4
     0.0f, -0.5f,   1.0f, 1.0f, 1.0f,   0.5f,  1.0f, // Bottom 5
    -1.0f,  1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, // Top-left-Top 6
     1.0f,  1.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f, // top-right-top 7
     1.0f, -1.0f,   1.0f, 1.0f, 1.0f,   1.0f,  1.0f, // bot-right-bot 8
    -1.0f, -1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f, // bot-left-bot 9
     0.25,  1.0f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f, // top-right-gun 10
     0.25, -1.0f,   1.0f, 1.0f, 1.0f,   1.0f,  1.0f, // bot-right-gun 11
    -0.25, -1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f, // bot-left-gun 12
    -0.25,  1.0f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, // top-right-gun 13
    -0.5f, 0.25f,   1.0f, 1.0f, 1.0f,   0.0f,  0.0f, // Top-left 14
     0.5f, 0.25f,   1.0f, 1.0f, 1.0f,   1.0f,  0.0f, // Top-right 15
     0.5f,-0.25f,   1.0f, 1.0f, 1.0f,   1.0f,  1.0f, // Bottom-right 16
    -0.5f,-0.25f,   1.0f, 1.0f, 1.0f,   0.0f,  1.0f, // Bottom-left 17
    
};

GLuint* genTextures(int n, const char** files)
{
    GLuint* textures = new GLuint[n];
    glGenTextures(n, textures);
    
    for (int i = 0; i < n; i++) {
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        
        int width1, height1, comp;
        unsigned char* data = stbi_load(files[i], &width1, &height1, &comp, 4);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width1, height1, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        
        glGenerateMipmap(GL_TEXTURE_2D);
        
        stbi_image_free(data);
    }
    
    return textures;
}

const char* fromFile(const char* filename)
{
    FILE* fs;
    long length;
    char* buffer;
    
    fs = fopen(filename, "r");
    if( !fs ) {perror(filename);return NULL;}
    
    fseek(fs, 0L, SEEK_END);
    length = ftell(fs);
    rewind(fs);
    
    buffer = (char*)calloc(1, length+1);
    if( !buffer ) {fclose(fs);fputs("memory alloc fails",stderr);return NULL;}
    
    if( 1!=fread( buffer , length, 1 , fs) ) {fclose(fs);free(buffer);fputs("entire read fails",stderr); return NULL;}
    
    
    fclose(fs);
    return buffer;
}

GLuint setupVBO(GLuint program)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLint posAttrib = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
    
    GLint colAttrib = glGetAttribLocation(program, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    
    GLint texAttrib = glGetAttribLocation(program, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    
    return vbo;
}

GLuint createProgram()
{
    const char* vertexShader = fromFile("/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/shader.vsh");
    const char* fragmentShader = fromFile("/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/shader.fsh");
    
    
    std::cout << "Creating Program..." << std::endl;
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
    
    GLint status;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(vs, 512, NULL, buffer);
        printf("%s", buffer);
    }
    
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
    
    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        char buffer[512];
        glGetShaderInfoLog(fs, 512, NULL, buffer);
        printf("%s", buffer);
    }
    
    
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glBindFragDataLocation(program, 0, "outColor");
    
    glLinkProgram(program);
    
    
    return program;
}

#endif
