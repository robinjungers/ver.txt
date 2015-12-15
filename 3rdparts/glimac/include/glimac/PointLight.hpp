#pragma once

#include <GL/glew.h>
#include "glimac/glm.hpp"
#include "glimac/Program.hpp"

using namespace glimac;
using namespace glm;

class PointLight {

  private:
    GLint uPos;
    GLint uIntensity;

    vec4 pos;
    vec3 intensity;

  public:
    PointLight( float x = 0.0, float y = 0.0, float z = 0.0 );

    void setPosition( float x, float y, float z );
    void setIntensity( float r, float g, float b );

    int  getUniformLocations( Program &program );
    void sendUniformLocations( mat4 ViewMatrix );

};
