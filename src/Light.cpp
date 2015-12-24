#include "Light.hpp"

#include <iostream>

using namespace glimac;
using namespace glm;

GLint Light::m_uCoord = 0;
GLint Light::m_uIntensity = 0;

Light::Light( vec4 coord, vec3 intensity ) : m_coord( coord ), m_intensity( intensity ) {}

void Light::setCoord( vec4 coord ) {
  m_coord = coord;
}

void Light::setIntensity( vec3 intensity ) {
  m_intensity = intensity;
}

int Light::getUniformLocations( Program &program ) {

  m_uCoord = glGetUniformLocation(program.getGLId(), "uLightCoord");
  m_uIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");

}

void Light::sendUniformValues( glm::mat4 ViewMatrix ) {

  vec4 coord = ViewMatrix * m_coord;
  glUniform4f( m_uCoord, coord.x, coord.y, coord.z, coord.w );
  glUniform3f( m_uIntensity, m_intensity.x, m_intensity.y, m_intensity.z );

}
