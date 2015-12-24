#pragma once

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>

using namespace glimac;
using namespace glm;


#define MAX_LIGHTS 10
struct uLight {

  GLint coord;
  GLint intensity;

};


class Light {

  protected:
    static GLint m_uNbLights;
    static uLight m_uLights[MAX_LIGHTS];

    vec4 m_coord;
    vec3 m_intensity;

  public:
    Light( vec4 coord, vec3 intensity );
    static void sendUniformNumber( int nbLights );
    static void getUniformLocations( Program &program );
    void sendUniformValues( glm::mat4 ViewMatrix, int uniformIndex );

};
