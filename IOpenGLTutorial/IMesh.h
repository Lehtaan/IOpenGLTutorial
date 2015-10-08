//
//  IMesh.h
//  IOpenGLTutorial
//
//  Created by Janis Böhm on 19/09/15.
//  Copyright (c) 2015 Janis Böhm. All rights reserved.
//

#ifndef __IOpenGLTutorial__IMesh__
#define __IOpenGLTutorial__IMesh__

#include <stdio.h>
#include <iostream>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class IMesh
{
public:
    
    IMesh(GLuint vbo, GLuint* elements, GLuint sizeElements, GLint numElements, GLuint program, GLuint tex);
    ~IMesh();
    
    void Draw();
    void Bind();
    
    GLuint getVAO() {return _vao;};
    GLuint getVBO() {return _vbo;};
    GLuint getEBO() {return _ebo;};
    GLuint getTex() {return _tex;};
    GLdouble getTime() {return _time;};
    
    void setTex(GLuint tex) {_tex = tex;};
    
    float getRatio() {return _ratio;};
    GLint getNumElements() {return  _numElements;};
    
    glm::vec3* getScale() {return &_scale;};
    glm::vec3* getPos() {return &_pos;};
    glm::vec3* getRelativePos() {return &_rpos;};
    
private:
    
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    GLuint _tex;
    
    GLdouble _time;
    
    float _ratio;
    glm::mat4 _trans;
    
    glm::vec3 _scale;
    glm::vec3 _pos;
    glm::vec3 _rpos;
    
    GLuint _ratioLocation;
    GLuint _transLocation;
    GLuint _posLocation;
    
    GLint _numElements;
    
};


#endif /* defined(__IOpenGLTutorial__IMesh__) */
