#include "Sphere.hpp"

#include <vector>
#include <cmath>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/glm.hpp>

using namespace std;
using namespace glimac;
using namespace glm;

Sphere::Sphere( GLfloat r, GLsizei discLat, GLsizei discLong ) {
  buildVertices( r, discLat, discLong  );
  initVertices();
}

void Sphere::buildVertices( GLfloat r, GLsizei discLat, GLsizei discLong ) {
  GLfloat rcpLat = 1.f / discLat, rcpLong = 1.f / discLong;
  GLfloat dPhi = 2 * pi<float>() * rcpLat, dTheta = pi<float>() * rcpLong;

  vector<ShapeVertex> data;

  // Construit l'ensemble des vertex
  for(GLsizei j = 0; j <= discLong; ++j) {
    GLfloat cosTheta = cos(-pi<float>() / 2 + j * dTheta);
    GLfloat sinTheta = sin(-pi<float>() / 2 + j * dTheta);

    for(GLsizei i = 0; i <= discLat; ++i) {
      ShapeVertex vertex;

      vertex.texCoords.x = i * rcpLat;
      vertex.texCoords.y = 1.f - j * rcpLong;

      vertex.normal.x = sin(i * dPhi) * cosTheta;
      vertex.normal.y = sinTheta;
      vertex.normal.z = cos(i * dPhi) * cosTheta;

      vertex.position = r * vertex.normal;

      data.push_back(vertex);
    }
  }

  // Construit les vertex finaux en regroupant les données en triangles:
  // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
  // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
  // avec i sur la bande correspondant à la longitude
  for(GLsizei j = 0; j < discLong; ++j) {
    GLsizei offset = j * (discLat + 1);
    for(GLsizei i = 0; i < discLat; ++i) {
      m_vertices.push_back(data[offset + i]);
      m_vertices.push_back(data[offset + (i + 1)]);
      m_vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
      m_vertices.push_back(data[offset + i]);
      m_vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
      m_vertices.push_back(data[offset + i + discLat + 1]);
    }
  }

}


void Sphere::transition() {

}

void Sphere::animation() {

}
