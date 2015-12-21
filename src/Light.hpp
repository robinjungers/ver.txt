#pragma once

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>

using namespace glimac;
using namespace glm;

class Light {

  protected:
    GLint uPos;
    GLint uIntensity;

    vec4 m_vect;
    vec3 m_intensity;

  public:
    virtual ~Light() {};
    virtual void setPosition( vec3 xyz ) = 0;
    void setIntensity( vec3 rgb );
    int  getUniformLocations( Program &program );
    void sendUniformValues( mat4 ViewMatrix );

};

class PointLight : public Light {

  public:
    PointLight();
    ~PointLight() {};
    PointLight( vec3 xyz );
    void setPosition( vec3 xyz );

};

class DirectionLight : public Light {

  public:
    DirectionLight();
    ~DirectionLight() {};
    DirectionLight( vec3 xyz );
    void setPosition( vec3 xyz );

};
