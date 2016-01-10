#include "Tesseract.hpp"

using namespace glimac;
using namespace glm;

GLint Tesseract::m_uIsLine = 0;

Tesseract::Tesseract() {
	m_rotate = 0;
	buildVertices();
	initVertices();
}

void Tesseract::getUniformLocations( Program &program ) {
  m_uIsLine = glGetUniformLocation( program.getGLId(), "uIsLine" );
}

void Tesseract::buildVertices() {

	ShapeVertex vertex;
	m_vertices.clear();

	vertex.normal = vec3( 0.0, 0.0, 0.0 );
	vertex.texCoords = vec2( 0.0, 0.0 );


	vertex.position = vec3( -0.5, 0.5, -0.5 ); // arrière externe haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, 0.5, -0.5 ); 
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, 0.5, -0.5 ); // droite externe haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, 0.5, 0.5 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, 0.5, 0.5 ); // avant externe haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, 0.5, 0.5 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, 0.5, 0.5 ); // gauche externe haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, 0.5, -0.5 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, -0.5, -0.5 ); // arrière externe bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, -0.5, -0.5 ); 
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, -0.5, -0.5 ); // droite externe bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, -0.5, 0.5 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, -0.5, 0.5 ); // avant externe bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, -0.5, 0.5 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, -0.5, 0.5 ); // gauche externe bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, -0.5, -0.5 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, 0.5, -0.5 ); // arrière gauche externe vertical
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, -0.5, -0.5 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, 0.5, -0.5 ); // arrière droite externe vertical
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, -0.5, -0.5 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, 0.5, 0.5 ); // avant droite externe vertical
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, -0.5, 0.5 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, 0.5, 0.5 ); // avant gauche externe vertical
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, -0.5, 0.5 );
	m_vertices.push_back(vertex);


	vertex.position = vec3( -0.3, 0.3, -0.3 ); // arrière interne haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, 0.3, -0.3 ); 
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, 0.3, -0.3 ); // droite interne haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, 0.3, 0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, 0.3, 0.3 ); // avant interne haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, 0.3, 0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, 0.3, 0.3 ); // gauche interne haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, 0.3, -0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, -0.3, -0.3 ); // arrière interne bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, -0.3, -0.3 ); 
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, -0.3, -0.3 ); // droite interne bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, -0.3, 0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, -0.3, 0.3 ); // avant interne bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, -0.3, 0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, -0.3, 0.3 ); // gauche interne bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, -0.3, -0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, 0.3, -0.3 ); // arrière gauche interne vertical
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, -0.3, -0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, 0.3, -0.3 ); // arrière droite interne vertical
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, -0.3, -0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, 0.3, 0.3 ); // avant droite interne vertical
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, -0.3, 0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, 0.3, 0.3 ); // avant gauche interne vertical
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, -0.3, 0.3 );
	m_vertices.push_back(vertex);


	vertex.position = vec3( -0.5, 0.5, -0.5 ); // arrière gauche lien haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, 0.3, -0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, 0.5, -0.5 ); // arrière droite lien haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, 0.3, -0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, 0.5, 0.5 ); // avant droite lien haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, 0.3, 0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, 0.5, 0.5 ); // avant gauche lien haut
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, 0.3, 0.3 );
	m_vertices.push_back(vertex);


	vertex.position = vec3( -0.5, -0.5, -0.5 ); // arrière gauche lien bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, -0.3, -0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, -0.5, -0.5 ); // arrière droite lien bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, -0.3, -0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.5, -0.5, 0.5 ); // avant droite lien bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( 0.3, -0.3, 0.3 );
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.5, -0.5, 0.5 ); // avant gauche lien bas
	m_vertices.push_back(vertex);

	vertex.position = vec3( -0.3, -0.3, 0.3 );
	m_vertices.push_back(vertex);


	mat4 rotateXW( 1.0 );
	rotateXW[0].x = cos( m_rotate );
	rotateXW[0].w = -sin( m_rotate );
	rotateXW[3].x = sin( m_rotate );
	rotateXW[3].w = cos( m_rotate );

	mat4 rotateYW( 1.0 );
	rotateYW[1].y = cos( m_rotate );
	rotateYW[1].w = sin( m_rotate );
	rotateYW[3].y = -sin( m_rotate );
	rotateYW[3].w = cos( m_rotate );

	for ( unsigned i = 0; i < m_vertices.size(); ++i )
		m_vertices[i].position = vec3( rotateXW * rotateYW * vec4( m_vertices[i].position, 1.0 ) );

}

void Tesseract::animation() {

	m_rotate += 0.01;

	buildVertices();
	reInitVertices();

}

void Tesseract::draw() {

	glUniform1i(m_uIsLine, true);

  // Binding
  glBindVertexArray( m_vao );

  // Drawing
  glDrawArrays( GL_LINES, 0, m_vertices.size() );

  // Debinding
  glBindVertexArray(0);

  glUniform1i(m_uIsLine, false);

}
