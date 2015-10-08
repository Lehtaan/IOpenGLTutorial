//
//  IMesh.cpp
//  IOpenGLTutorial
//
//  Created by Janis Böhm on 19/09/15.
//  Copyright (c) 2015 Janis Böhm. All rights reserved.
//

#include "IMesh.h"


IMesh::IMesh(GLuint vbo, GLuint* elements, GLuint sizeElements, GLint numElements, GLuint program, GLuint tex):_numElements(numElements), _tex(tex)
{
    //////////////////////
    ////VERTEX BUFFERS////
    //////////////////////
    
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    
    std::cout << "Creating Mesh " << _vao << " ..." << std::endl;
    
    _vbo = vbo;
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    
    /*
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeVerticies, verticies, GL_STATIC_DRAW);*/
    
    GLint posAttrib = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
    
    GLint colAttrib = glGetAttribLocation(program, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    
    GLint texAttrib = glGetAttribLocation(program, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    
    glGenBuffers(1, &_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeElements, elements, GL_STATIC_DRAW);
    
    
    ////////////////
    ////UNIFORMS////
    ////////////////
    
    _trans = glm::mat4();
    _scale = glm::vec3(1.0, 1.0, 1.0);
    _pos = glm::vec3(0.0f, 0.0f, 0.0f);
    
    _transLocation = glGetUniformLocation(program, "trans");
    glUniformMatrix4fv(_transLocation, 1, GL_FALSE, glm::value_ptr(_trans));
    
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
    _ratio = (float)width / (float) height;
    
    _ratioLocation = glGetUniformLocation(program, "ratio");
    
    _posLocation = glGetUniformLocation(program, "pos");
    
    _time = glfwGetTime();
    
}

void IMesh::Bind()
{
    glUniform1f(_ratioLocation, _ratio);
    glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(glm::scale(_trans, _scale)));
    glUniform3f(_posLocation, _pos.x + _rpos.x, _pos.y + _rpos.y, _pos.z + _rpos.z);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _tex);
}

void IMesh::Draw()
{
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLE_FAN, _numElements, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

IMesh::~IMesh()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_ebo);
}