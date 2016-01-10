#include "Organic.hpp"
#include "PerlinNoise.hpp"
#include "tools.hpp"

using namespace glm;

Organic::Organic() {
  buildVertices();
  initVertices();
}

void Organic::buildVertices(  ) {

  GLsizei discLat = 32, discLong = 32;

  GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
  GLfloat dPhi = 2 * pi<float>() * rcpLat, dTheta = pi<float>() * rcpLong;

  PerlinNoise pn;
  std::vector<ShapeVertex> data;
  m_vertices.clear();

  for ( GLsizei j = 0; j <= discLong; ++j ) {

    GLfloat cosTheta = cos( -pi<float>() / 2 + j * dTheta );
    GLfloat sinTheta = sin( -pi<float>() / 2 + j * dTheta );

    for ( GLsizei i = 0; i <= discLat; ++i ) {

      ShapeVertex vertex;

      vertex.texCoords.x = i * rcpLat;
      vertex.texCoords.y = 1.f - j * rcpLong;

      float shaping;
      if ( j > discLong / 2 )
        shaping = 0.3;
      else
        shaping = 1.5;

      vertex.normal.x = sin( i * dPhi ) * cosTheta;
      vertex.normal.y = sinTheta * shaping;
      vertex.normal.z = cos( i * dPhi ) * cosTheta;

      float x = ( i == discLat ) ? 0 : ( 0.2 * i );
      float y = ( j == discLong ) ? 0 : ( 0.2 * j );

      shaping = 0.1 * map( j, 0, discLong, 10, 0 );
   
      GLfloat r = m_currentFadingParameter * shaping * pn.noise( x, y, m_currentMorphingParameter ) + 0.8;
      vertex.position = r * vertex.normal;

      data.push_back( vertex );

    }

  }

  for ( GLsizei j = 0; j < discLong; ++j ) {

    GLsizei offset = j * ( discLat + 1 );

    for ( GLsizei i = 0; i < discLat; ++i ) {

      m_vertices.push_back( data[offset + i] );
      m_vertices.push_back( data[offset + ( i + 1 )] );
      m_vertices.push_back( data[offset + discLat + 1 + ( i + 1 )] );

      m_vertices.push_back( data[offset + i] );
      m_vertices.push_back( data[offset + discLat + 1 + ( i + 1 )] );
      m_vertices.push_back( data[offset + i + discLat + 1] );

    }

  }

}

void Organic::animation() {

}
