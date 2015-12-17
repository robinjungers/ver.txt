#pragma once

#include <GL/glew.h>
#include "glimac/glm.hpp"
#include "glimac/Program.hpp"

using namespace glimac;
using namespace glm;

class Light {

  protected:
    GLint uPos;
    GLint uIntensity;

    vec4 m_vect;
    vec3 m_intensity;

  public:
    Light( float x = 0.0, float y = 0.0, float z = 0.0 );
    virtual void setPosition( float x, float y, float z );
    void setIntensity( float r, float g, float b );
    int  getUniformLocations( Program &program );
    void sendUniformLocations( mat4 ViewMatrix );
};

class PointLight : public Light{

  public:
    PointLight( float x, float y, float z );
    void setPosition( float x, float y, float z );   
};

class DirectionLight : public Light{

  public:
    DirectionLight( float x, float y, float z );
    void setPosition( float x, float y, float z );   
};