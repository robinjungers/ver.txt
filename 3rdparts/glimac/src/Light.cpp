#include "glimac/Light.hpp"

using namespace glimac;
using namespace glm;

void Light::setIntensity( float r, float g, float b ) {
  m_intensity = vec3( r, g, b );
}

int Light::getUniformLocations( Program &program ) {
  uPos = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
  uIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");

  if ( !uPos || !uIntensity ) return 1;
  return 0;
}

void Light::sendUniformLocations( glm::mat4 ViewMatrix ) {
  m_vect = ViewMatrix * m_vect;
  glUniform3f( uPos, m_vect.x, m_vect.y, m_vect.z );
  glUniform3f( uIntensity, m_intensity.x, m_intensity.y, m_intensity.z );
}

PointLight::PointLight( float x, float y, float z ) {
  m_vect = vec4( x, y, z, 1.0 );
  m_intensity = vec3( 1.0, 1.0, 1.0 );
}

void PointLight::setPosition( float x, float y, float z ) {
  m_vect = vec4( x, y, z, 1.0);
}

DirectionLight::DirectionLight( float x, float y, float z ) {
  m_vect = vec4( x, y, z, 0.0 );
  m_intensity = vec3( 1.0, 1.0, 1.0 );
}

void DirectionLight::setPosition( float x, float y, float z ) {
  m_vect = vec4( x, y, z, 0.0 );
}