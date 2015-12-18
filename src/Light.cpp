#include "Light.hpp"

using namespace glimac;
using namespace glm;


void Light::setIntensity( vec3 rgb ) {
  m_intensity = rgb;
}

int Light::getUniformLocations( Program &program ) {

  uPos = glGetUniformLocation(program.getGLId(), "uLightPos");
  uIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");

  if ( !uPos || !uIntensity ) return 1;
  return 0;
}

void Light::sendUniformValues( glm::mat4 ViewMatrix ) {

  vec4 vect = ViewMatrix * m_vect;
  glUniform3f( uPos, vect.x, vect.y, vect.z );
  glUniform3f( uIntensity, m_intensity.x, m_intensity.y, m_intensity.z );

}


PointLight::PointLight( vec3 xyz ) {

  m_vect = vec4( xyz, 1.0 );
  m_intensity = vec3( 1.0, 1.0, 1.0 );

}

void PointLight::setPosition( vec3 xyz ) {
  m_vect = vec4( xyz, 1.0);
}


DirectionLight::DirectionLight( vec3 xyz ) {

  m_vect = vec4( xyz, 0.0 );
  m_intensity = vec3( 1.0, 1.0, 1.0 );

}

void DirectionLight::setPosition( vec3 xyz ) {
  m_vect = vec4( xyz, 0.0 );
}
