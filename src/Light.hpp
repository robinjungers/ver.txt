#pragma once

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>

using namespace glimac;
using namespace glm;

class Light {

  protected:
    static GLint m_uCoord;
    static GLint m_uIntensity;

    vec4 m_coord;
    vec3 m_intensity;

  public:
    Light( vec4 coord, vec3 intensity );
    void setCoord( vec4 coord );
    void setIntensity( vec3 intensity );
    static int getUniformLocations( Program &program );
    void sendUniformValues( mat4 ViewMatrix );

};
