#include "Object3D.hpp"
#include "tools.hpp"

#include <iostream>
#include <cmath>

using namespace std;
using namespace glimac;
using namespace glm;

Object3D::Object3D() {
  m_position = vec3( 0.0, 0.0, 0.0 );
  m_rotation = vec3( 0.0, 0.0, 0.0 );
  m_scale = vec3( 0.0, 0.0, 0.0 );
  m_morphingParameter = 0.0;
  m_fadingParameter = 1.0;
  m_currentMorphingParameter = 0.0;
  m_currentFadingParameter = 0.0;
}

void Object3D::initVertices() {

  //Création d'un VBO
  glGenBuffers( 1, &m_vbo );

  //Bindind du vbo sur la cible
  glBindBuffer( GL_ARRAY_BUFFER, m_vbo );

  //Puis on envois les données à la CG
  glBufferData( GL_ARRAY_BUFFER, m_vertices.size() * sizeof( ShapeVertex ), m_vertices.data(), GL_STATIC_DRAW );

  //Débindind du vbo de la cible pour éviter de le remodifier
  glBindBuffer( GL_ARRAY_BUFFER, 0 );

  //Création du VAO
  glGenVertexArrays( 1, &m_vao );

  //Binding du vao (un seul à la fois)
  glBindVertexArray( m_vao );

  //Dire à OpenGL qu'on utilise le VAO
  const GLuint VERTEX_ATTR_POSITION = 0;
  const GLuint VERTEX_ATTR_NORMAL = 1;
  const GLuint VERTEX_ATTR_TEXCOORDS = 2;
  glEnableVertexAttribArray( VERTEX_ATTR_POSITION );
  glEnableVertexAttribArray( VERTEX_ATTR_NORMAL );
  glEnableVertexAttribArray( VERTEX_ATTR_TEXCOORDS );

  //Indiquer à OpenGL où trouver les sommets
  //Bindind du vbo sur la cible
  glBindBuffer( GL_ARRAY_BUFFER, m_vbo );
  //Spécification du format de l'attribut de sommet position
  glVertexAttribPointer( VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof( ShapeVertex ), ( const GLvoid* ) offsetof( ShapeVertex, position ) );
  glVertexAttribPointer( VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof( ShapeVertex ), ( const GLvoid* ) offsetof( ShapeVertex, normal ) );
  glVertexAttribPointer( VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof( ShapeVertex ), ( const GLvoid* ) offsetof( ShapeVertex, texCoords ) );
  //Débindind du vbo de la cible pour éviter de le remodifier
  glBindBuffer( GL_ARRAY_BUFFER, 0 );

  //Débindind du vao de la cible pour éviter de le remodifier
  glBindVertexArray( 0 );

}



void Object3D::setPosition( vec3 position ) {
  m_position = position;
}
void Object3D::setRotation( vec3 rotation ) {
  m_rotation = rotation;
}
void Object3D::setScale( vec3 scale ) {
  m_scale = scale;
}
void Object3D::setMaterial( Material * material ) {
  m_material = material;
}
void Object3D::setTexture( Texture * texture ) {
  m_texture = texture;
}

void Object3D::pushMorphingParameter( float morphingParameter ) {
  m_morphingParameter = morphingParameter;
}
void Object3D::pushFadingParameter( float fadingParameter ) {
  m_fadingParameter = fadingParameter;
}



vec3 Object3D::getPosition() {
  return m_position;
}
vec3 Object3D::getRotation() {
  return m_rotation;
}
vec3 Object3D::getScale() {
  return m_scale;
}



bool Object3D::transition() {

  float step = 0.01;

  if ( (fabs(m_morphingParameter - m_currentMorphingParameter) < step ) && (fabs(m_fadingParameter - m_currentFadingParameter) < step ) ) return false;

	ease( m_currentFadingParameter, m_fadingParameter, 0.01 );
	ease( m_currentMorphingParameter, m_morphingParameter, 0.01 );

  buildVertices();
	initVertices();

	return true;

}




void Solid::draw() {

  // Binding
  glBindVertexArray( m_vao );
  m_texture->bindTexture();

  // Uniforms
  m_material->sendUniformValues();

  // Drawing
  glDrawArrays( GL_TRIANGLES, 0, m_vertices.size() );

  // Debinding
  m_texture->debindTexture();
  glBindVertexArray(0);

}
