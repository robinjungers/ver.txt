#include "Light.hpp"

#include <iostream>
#include <string>
#include <sstream>

using namespace glimac;
using namespace glm;
using namespace std;

GLint Light::m_uNbLights = 0;
uLight Light::m_uLights[MAX_LIGHTS] = {};

Light::Light( vec4 coord, vec3 intensity ) : m_coord( coord ), m_intensity( intensity ) {}

void Light::getUniformLocations( Program &program ) {

  m_uNbLights = glGetUniformLocation(program.getGLId(), "uNbLights");

  for (unsigned i = 0; i < MAX_LIGHTS; ++i) {

    stringstream uniformIdentifierStream;
    uniformIdentifierStream << "uLights[" << i << "].coord";
    const char *uniformIdentifier = uniformIdentifierStream.str().c_str();

    m_uLights[i].coord = glGetUniformLocation(program.getGLId(), uniformIdentifier);

    uniformIdentifierStream.str( std::string() );
    uniformIdentifierStream.clear();
    uniformIdentifierStream << "uLights[" << i << "].intensity";
    uniformIdentifier = uniformIdentifierStream.str().c_str();

    m_uLights[i].intensity = glGetUniformLocation(program.getGLId(), uniformIdentifier);

  }
  
}

void Light::sendUniformNumber( int nbLights ) {
  glUniform1i( m_uNbLights, nbLights );
}

void Light::sendUniformValues( glm::mat4 ViewMatrix, int uniformIndex ) {

  vec4 coord = ViewMatrix * m_coord;
  glUniform4f( m_uLights[uniformIndex].coord, coord.x, coord.y, coord.z, coord.w );
  glUniform3f( m_uLights[uniformIndex].intensity, m_intensity.x, m_intensity.y, m_intensity.z );

}
