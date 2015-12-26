#pragma once

#include <GL/glew.h>
#include <glimac/glm.hpp>
#include <glimac/Program.hpp>

using namespace glimac;
using namespace glm;

class Material {

  private:
	static GLint m_uKd;
	static GLint m_uKs;
	static GLint m_uShininess;
	vec3 m_diffuseColor;
	vec3 m_specularColor;
	int m_shininess;

  public:
	Material( vec3 diffuseColor, vec3 specularColor, int shininess );

	static void getUniformLocations( Program &program );
	void sendUniformValues();

	void setDiffuseColor( vec3 diffuseColor );
	void setSpecularColor( vec3 specularColor );
	void setShininess( int shininess );

};
