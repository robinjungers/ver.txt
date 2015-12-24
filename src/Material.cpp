#include "Material.hpp"

using namespace glimac;
using namespace glm;

GLint Material::m_uKd = 0;
GLint Material::m_uKs = 0;
GLint Material::m_uShininess = 0;

Material::Material( vec3 diffuseColor, vec3 specularColor, int shininess ):
m_diffuseColor( diffuseColor ), m_specularColor( specularColor ), m_shininess( shininess ) {}

void Material::getUniformLocations( Program &program ) {
	m_uKd = glGetUniformLocation( program.getGLId(), "uKd" );
	m_uKs = glGetUniformLocation( program.getGLId(), "uKs" );
	m_uShininess = glGetUniformLocation( program.getGLId(), "uShininess" );
}

void Material::sendUniformValues() {
	glUniform3f(m_uKd, m_diffuseColor.r, m_diffuseColor.g, m_diffuseColor.b);
    glUniform3f(m_uKs, m_specularColor.r, m_specularColor.g, m_specularColor.b);
    glUniform1f(m_uShininess, m_shininess);
}

void Material::setDiffuseColor( vec3 diffuseColor ){
	m_diffuseColor = diffuseColor;
}

void Material::setSpecularColor( vec3 specularColor ){
	m_specularColor = specularColor;
}

void Material::setShininess( int shininess ){
	m_shininess = shininess;
}
