#include "Letter.hpp"

#include <vector>

using namespace glimac;
using namespace glm;

Letter::Letter( unsigned char index ) : m_index( index ) {
	buildVertices();
	initVertices();
}

void Letter::buildVertices() {

	ShapeVertex vertex;

    vertex.position = vec3( 0.0, 0.0, 0.0 );
    vertex.normal = vec3( 0.0, 0.0, -1.0 );
    vertex.texCoords = vec2( m_index * letterWidth, 0.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3( 1.0, 0.0, 0.0 );
    vertex.normal = vec3( 0.0, 0.0, -1.0 );
    vertex.texCoords = vec2( ( m_index + 1 ) * letterWidth, 0.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3( 1.0, -1.0, 0.0 );
    vertex.normal = vec3( 0.0, 0.0, -1.0 );
    vertex.texCoords = vec2( ( m_index + 1 ) * letterWidth, 1.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3( 0.0, 0.0, 0.0 );
    vertex.normal = vec3( 0.0, 0.0, -1.0 );
    vertex.texCoords = vec2( m_index * letterWidth, 0.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3( 0.0, -1.0, 0.0 );
    vertex.normal = vec3( 0.0, 0.0, -1.0 );
    vertex.texCoords = vec2( m_index * letterWidth, 1.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3( 1.0, -1.0, 0.0 );
    vertex.normal = vec3( 0.0, 0.0, -1.0 );
    vertex.texCoords = vec2( ( m_index + 1 ) * letterWidth, 1.0 );

    m_vertices.push_back(vertex);

}

void Letter::transition() {



}

void Letter::animation() {



}
