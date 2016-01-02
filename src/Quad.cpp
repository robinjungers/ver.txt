#include "Quad.hpp"

#include <vector>

using namespace glimac;
using namespace glm;

Quad::Quad() {
	buildVertices();
	initVertices();
}

void Quad::buildVertices() {

	ShapeVertex vertex;

	vertex.position = vec3( -1.0, 0.0, 1.0 );
	vertex.normal = vec3( 0.0, 1.0, 0.0 );
	vertex.texCoords = vec2( 0.0, 0.0 );

	m_vertices.push_back(vertex);

	vertex.position = vec3( 1.0, 0.0, 1.0 );
	vertex.normal = vec3( 0.0, 1.0, 0.0 );
	vertex.texCoords = vec2( 1.0, 0.0 );

	m_vertices.push_back(vertex);

  vertex.position = vec3( 1.0, 0.0, -1.0 );
	vertex.normal = vec3( 0.0, 1.0, 0.0 );
	vertex.texCoords = vec2( 1.0, 1.0 );

	m_vertices.push_back(vertex);

	vertex.position = vec3( -1.0, 0.0, 1.0 );
	vertex.normal = vec3( 0.0, 1.0, 0.0 );
	vertex.texCoords = vec2( 0.0, 0.0 );

  m_vertices.push_back(vertex);

  vertex.position = vec3( -1.0, 0.0, -1.0 );
	vertex.normal = vec3( 0.0, 1.0, 0.0 );
	vertex.texCoords = vec2( 0.0, 1.0 );

  m_vertices.push_back(vertex);

  vertex.position = vec3( 1.0, 0.0, -1.0 );
	vertex.normal = vec3( 0.0, 1.0, 0.0 );
	vertex.texCoords = vec2( 1.0, 1.0 );

  m_vertices.push_back(vertex);

}

void Quad::animation() {



}
