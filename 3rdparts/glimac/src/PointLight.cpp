#include "glimac/PointLight.hpp"

using namespace glimac;
using namespace glm;


PointLight::PointLight( float x, float y, float z ) {
  pos = vec4( x, y, z, 1.0 );
  intensity = vec3( 1.0, 1.0, 1.0 );
}


void PointLight::setPosition( float x, float y, float z ) {
  pos = vec4( x, y, z, 1.0 );
}

void PointLight::setIntensity( float r, float g, float b ) {
  intensity = vec3( r, g, b );
}


int PointLight::getUniformLocations( Program &program ) {
  uPos = glGetUniformLocation(program.getGLId(), "uLightPos_vs");
  uIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");

  if ( !uPos || !uIntensity ) return 1;
  return 0;
}

void PointLight::sendUniformLocations( glm::mat4 ViewMatrix ) {
  pos = ViewMatrix * pos;
  glUniform3f( uPos, pos.x, pos.y, pos.z );
  glUniform3f( uIntensity, intensity.x, intensity.y, intensity.z );
}
