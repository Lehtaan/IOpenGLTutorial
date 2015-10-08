//
//  main.cpp
//  IOpenGLTutorial
//
//  Created by Janis Böhm on 18/09/15.

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <ctime>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "main.h"
#include "IMesh.h"

using namespace std;

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    cout << "Initializing GLFW..." << endl;
    if (!glfwInit())
        exit(EXIT_FAILURE);
    
    cout << "Creating Window..." << endl;
    
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // We dont want resizing windows
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

    srand((uint)time(0));
    
    int title = rand() % 5;
    printf("%d", title);
    std::string windowtitle = "Mario: The Sequel";
    
    switch (title) {
        case 0:
            windowtitle = "Realistic Alien-Kill-O-Tron";
            break;
            
        case 1:
            windowtitle = "Witty Window Title";
            break;
            
        case 2:
            windowtitle = "First Game of its kind";
            break;
            
        case 3:
            windowtitle = "DON'T CLOSE";
            break;
            
        case 4:
            windowtitle = "Aliendefense 9000";
            break;
    }
    
    
    
    
    window = glfwCreateWindow(640, 480, windowtitle.c_str(), NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    cout << "Initializing OpenGL..." << endl;
    
    GLuint program = createProgram();
    
    
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
    //Setting up a vertex buffer to store all the verticies so that I dont load that much memory for each mesh
    
    GLuint vbo = setupVBO(program);
    
    const char* files[13] =
    {   "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/space2.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/ship.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/start.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/gun.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/UFO.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/gas1.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/planet1.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/planet2.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/ship2.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/ship3.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/fire1.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/fire2.png",
        "/Users/janis/Documents/IOpenGLTutorial/IOpenGLTutorial/bubbles.png"
    };
    
    GLuint* tex = genTextures(13, files);
    
    IMesh* background = new IMesh(vbo, elements, sizeof(elements), (sizeof(elements)/sizeof(elements[0])), program, tex[0]);
    
    background->getScale()->x = 6;
    background->getScale()->y = 6;
    background->getScale()->z = 1;
    
    IMesh* ship = new IMesh(vbo, elements2, sizeof(elements2), (sizeof(elements2)/sizeof(elements2[0])), program, tex[1]);
    
    ship->getScale()->x = 0.75;
    ship->getScale()->y = 0.75;
    
    ship->getPos()->y = -1.4;

    IMesh* start = new IMesh(vbo, elements2, sizeof(elements2), (sizeof(elements2)/sizeof(elements2[0])), program, tex[2]);
    
    vector<IMesh*> lasers;
    vector<IMesh*> ufos;
    vector<IMesh*> planets;
    vector<IMesh*> exp;
    
    glBindVertexArray(0);
    
    glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
    
    double timeShot = glfwGetTime();
    double timeUFO = glfwGetTime();
    double timePlanet = glfwGetTime();
    m_ratio = ship->getRatio();
    
    m = 1.0;
    
    while (!glfwWindowShouldClose(window))
    {
        key_callback();
        
        //Spawning
        
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) && !running)
        if (glfwGetKey(window, GLFW_KEY_1)) ship->setTex(tex[1]);
        if (glfwGetKey(window, GLFW_KEY_2)) ship->setTex(tex[8]);
        if (glfwGetKey(window, GLFW_KEY_3)) ship->setTex(tex[9]);
        
        if ((glfwGetKey(window, GLFW_KEY_SPACE)  || glfwGetMouseButton(glfwGetCurrentContext(), GLFW_MOUSE_BUTTON_1)) && running && glfwGetTime()-timeShot >= 0.2)
        {
            IMesh* laser = new IMesh(vbo, elements3, sizeof(elements3), (sizeof(elements3)/sizeof(elements3[0])), program, tex[3]);
            laser->getScale()->x = 0.1;
            laser->getScale()->y = 0.1;
            
            laser->getPos()->y = -0.9;
            laser->getPos()->x = ship_pos.x;
            
            lasers.push_back(laser);
            timeShot = glfwGetTime();
        }
        
        if (rand() % (long)(70-(m*5)) == 1 && glfwGetTime()-timeUFO >= 0.8 && running)
        {
            IMesh* ufo = new IMesh(vbo, ufoments, sizeof(ufoments), (sizeof(ufoments)/sizeof(ufoments[0])), program, tex[4]);
            ufo->getScale()->x = 0.5;
            ufo->getScale()->y = 0.5;
            
            ufo->getPos()->y = 2+0.125;
            ufo->getPos()->x = ((float)(rand() % 300)/100)-1.5;
            printf("%f:%f\n", ufo->getPos()->x, ufo->getPos()->y);
            ufos.push_back(ufo);
            timeUFO = glfwGetTime();
        }
        
        if (rand() % (long)(200-(m*10)) == 1 && glfwGetTime() - timePlanet >= 1.5) {
            int i = rand() % 3;
            IMesh* planet = nullptr;
            if (i == 0) planet = new IMesh(vbo, elements2, sizeof(elements2), (sizeof(elements2)/sizeof(elements2[0])), program, tex[5]);
            if (i == 1) planet = new IMesh(vbo, elements2, sizeof(elements2), (sizeof(elements2)/sizeof(elements2[0])), program, tex[6]);
            if (i == 2) planet = new IMesh(vbo, elements2, sizeof(elements2), (sizeof(elements2)/sizeof(elements2[0])), program, tex[7]);
            
            if (planet != NULL)
            {
                planet->getPos()->y = 2.25;
                planet->getPos()->x = ((float)(rand() % 400)/100)-2;
                planet->getScale()->x = 0.5;
                planet->getScale()->y = 0.5;
                planets.push_back(planet);
                timePlanet = glfwGetTime();
            }
        
        }
        
        if (background->getPos()->y <= -4) background->getPos()->y = -0.01 * m;
        else background->getPos()->y = background->getPos()->y - 0.01 * m;
        

        for (int i = 0; i < planets.size(); i++) {
            planets[i]->getRelativePos()->x = ship_pos.x/18.0f;
        }
        
        
        background->getPos()->x = ship_pos.x/10.0f;
        ship->getPos()->x = ship_pos.x;
        ship->getPos()->y = ship_pos.y;
        
        //Movements
        
        for (int i = 0; i < lasers.size(); i++)
        {
            
            for (int k = 0; k < ufos.size(); k++)
            {
                float a = (ufos[k]->getPos()->x - 0.25) - (lasers[i]->getPos()->x + 0.025/2);
                float b = (ufos[k]->getPos()->x + 0.25) - (lasers[i]->getPos()->x - 0.025/2);
                
                float c = (ufos[k]->getPos()->y - 0.125) - (lasers[i]->getPos()->y + 0.01/2);
                float d = (ufos[k]->getPos()->y + 0.125) - (lasers[i]->getPos()->y - 0.01/2);
                
                if (a < 0) a *= -1;
                if (b < 0) b *= -1;
                if (c < 0) c *= -1;
                if (d < 0) d *= -1;
                
                if (a + b < .55 && c + d < .6)
                {
                    lasers[i]->~IMesh();
                    lasers.erase(lasers.begin() + i);
                    
                    IMesh* ex = new IMesh(vbo, elements2, sizeof(elements2), (sizeof(elements2)/sizeof(elements2[0])), program, tex[10]);
                    ex->getScale()->x = 0.5;
                    ex->getScale()->y = 0.5;
                    
                    ex->getPos()->x = ufos[k]->getPos()->x;
                    ex->getPos()->y = ufos[k]->getPos()->y;
                    
                    ufos[k]->~IMesh();
                    ufos.erase(ufos.begin() + k);
                    
                    exp.push_back(ex);
                    
                    printf("Hit\n");
                }
                
                
            }
        }
        
        
        
        //Drawing
        
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(program);
        
        background->Bind();
        background->Draw();
        
        for (int i = 0; i < planets.size(); i++) {
            
            if (planets[i]->getPos()->y <= -2.25) {
                planets[i]->~IMesh();
                planets.erase(planets.begin() + i);
            }
            else planets[i]->getPos()->y -= 0.012 * m;
            
            planets[i]->Bind();
            planets[i]->Draw();
            
        }
        
        ship->Bind();
        ship->Draw();
        
        for (int i = 0; i < lasers.size(); i++)
        {
            if (lasers[i]->getPos()->y >= 2) {
                lasers[i]->~IMesh();
                lasers.erase(lasers.begin()+i);
            }
            else
            {
                lasers[i]->getPos()->y += 0.03;
            }
            
            lasers[i]->getRelativePos()->x = ship_pos.x/22.0f;
            
            lasers[i]->Bind();
            lasers[i]->Draw();
        }
        
        for (int i = 0; i < ufos.size(); i++)
        {
            if (ufos[i]->getPos()->y <= -1.4) {
                running = false;
                m = 1.0;
                ship_pos.x = 0;
                ufos[i]->~IMesh();
                ufos.erase(ufos.begin() + i);
            }
            else
            {
                ufos[i]->getPos()->y -= 0.0075 * m;
            }
            
            ufos[i]->getRelativePos()->x = ship_pos.x/22.0f;
            
            ufos[i]->Bind();
            ufos[i]->Draw();
        }
        
        for (int i = 0; i < exp.size(); i++)
        {
            if (glfwGetTime() - exp[i]->getTime() >= 0.4) {
                exp[i]->setTex(tex[11]);
            }
            if (glfwGetTime() - exp[i]->getTime() >= 0.8) {
                exp[i]->~IMesh();
                exp.erase(exp.begin() + i);
            }
            
            exp[i]->Bind();
            exp[i]->Draw();
            
        }
        
        if (!running)
        {
            
            for (int i = 0; i < lasers.size(); i++) {
                lasers[i]->~IMesh();
                lasers.erase(lasers.begin()+i);
            }
            
            for (int i = 0; i < ufos.size(); i++) {
                ufos[i]->~IMesh();
                ufos.erase(ufos.begin()+i);
            }
            
            ship_pos.y = tan(glfwGetTime() * 0.5f) * 0.6f;
            
            start->getPos()->y = sin(glfwGetTime() * 5.0f) * 0.1f;
            
            start->Bind();
            start->Draw();
            
        }
        
        //swaping backbuffers and stuff
        
        if (running && m <= 4.5) m += 0.001;
        if (m >= 5) printf("%f\n", m);
        
        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

