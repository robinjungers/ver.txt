#include "Terrain.hpp"
#include "PerlinNoise.hpp"
#include "tools.hpp"

#include <vector>
#include <cmath>

using namespace glimac;
using namespace glm;

Terrain::Terrain() {
	m_width = 200;
	m_height = 200;
	m_terrainLong = 100;
	m_terrainLat = 100;
	buildVertices();
	initVertices();
}
Terrain::Terrain( float width, float height, float terrainLong, float terrainLat ) {
	m_width = width;
	m_height = height;
	m_terrainLong = terrainLat;
	m_terrainLat = terrainLat;
	buildVertices();
	initVertices();
}

void Terrain::buildVertices() {

  PerlinNoise pn;
	std::vector<ShapeVertex> data;
	m_vertices.clear();

  for ( unsigned i = 0; i <= m_terrainLong; ++i ) {
    for ( unsigned j = 0; j <= m_terrainLat; ++j ) {

      float x = map( i, 0, m_terrainLong, -m_width/2, m_width/2 );
			float z = map( j, 0, m_terrainLat, -m_height/2, m_height/2 );
			float distToCenter = x*x + z*z;
			float y = 0.004 * m_currentFadingParameter * distToCenter * pn.noise( 1.1 * x, 1.1 * z, m_currentMorphingParameter ) - 10.0;

      ShapeVertex vertex;

    	vertex.position		= vec3( x, y, z );
    	vertex.texCoords	= vec2( (float)i/(float)m_terrainLong, (float)j/(float)m_terrainLat );

			data.push_back( vertex );

    }
  }

	for ( unsigned i = 0; i < m_terrainLong; ++i ) {
		unsigned offset = i * (m_terrainLat+1);
    for ( unsigned j = 0; j < m_terrainLat; ++j ) {
			ShapeVertex v1, v2, v3;
			vec3 normal;

			v1 = data[offset + j];
			v2 = data[offset + (j + 1)];
			v3 = data[offset + m_terrainLat + 1 + (j + 1)];
			normal = cross( ( v2.position - v1.position ), ( v3.position - v1.position ));
			v1.normal = normal;
			v2.normal = normal;
			v3.normal = normal;
			// à commenter pour une texture de terrain non fragmentée
			v1.texCoords = vec2( 0, 0 );
			v2.texCoords = vec2( 0, 1 );
			v3.texCoords = vec2( 1, 1 );
			/////////////////////////////////////////////////////////
			m_vertices.push_back( v1 );
      m_vertices.push_back( v2 );
      m_vertices.push_back( v3 );

			v1 = data[offset + j];
			v2 = data[offset + m_terrainLat + 1 + (j + 1)];
			v3 = data[offset + j + m_terrainLat + 1];
			normal = cross( ( v2.position - v1.position ), ( v3.position - v1.position ));
			v1.normal = normal;
			v2.normal = normal;
			v3.normal = normal;
			// à commenter pour une texture de terrain non fragmentée
			v1.texCoords = vec2( 0, 0 );
			v2.texCoords = vec2( 1, 1 );
			v3.texCoords = vec2( 0, 1 );
			/////////////////////////////////////////////////////////
			m_vertices.push_back( v1 );
      m_vertices.push_back( v2 );
      m_vertices.push_back( v3 );

		}
	}

}

void Terrain::animation() {



}
