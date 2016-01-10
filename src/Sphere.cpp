#include "Sphere.hpp"

#include <vector>
#include <cmath>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/glm.hpp>

using namespace std;
using namespace glimac;
using namespace glm;

Sphere::Sphere() {
  m_r = 1;
  m_discLat = 32;
  m_discLong = 16;
  buildVertices();
  initVertices();
}
Sphere::Sphere( GLfloat r, GLsizei discLat, GLsizei discLong ) {
  m_r = r;
  m_discLat = discLat;
  m_discLong = discLong;
  buildVertices();
  initVertices();
}

void Sphere::buildVertices() {
  GLfloat rcpLat = 1.f / m_discLat, rcpLong = 1.f / m_discLong;
  GLfloat dPhi = 2 * pi<float>() * rcpLat, dTheta = pi<float>() * rcpLong;

  vector<ShapeVertex> data;

  // Construit l'ensemble des vertex
  for(GLsizei j = 0; j <= m_discLong; ++j) {
    GLfloat cosTheta = cos(-pi<float>() / 2 + j * dTheta);
    GLfloat sinTheta = sin(-pi<float>() / 2 + j * dTheta);

    for(GLsizei i = 0; i <= m_discLat; ++i) {
      ShapeVertex vertex;

      vertex.texCoords.x = i * rcpLat;
      vertex.texCoords.y = 1.f - j * rcpLong;

      vertex.normal.x = sin(i * dPhi) * cosTheta;
      vertex.normal.y = sinTheta;
      vertex.normal.z = cos(i * dPhi) * cosTheta;

      vertex.position = m_r * m_currentFadingParameter * vertex.normal;

      data.push_back(vertex);
    }
  }

  // Construit les vertex finaux en regroupant les données en triangles:
  // Pour une longitude donnée, les deux triangles formant une face sont de la forme:
  // (i, i + 1, i + discLat + 1), (i, i + discLat + 1, i + discLat)
  // avec i sur la bande correspondant à la longitude
  for(GLsizei j = 0; j < m_discLong; ++j) {
    GLsizei offset = j * (m_discLat + 1);
    for(GLsizei i = 0; i < m_discLat; ++i) {
      m_vertices.push_back(data[offset + i]);
      m_vertices.push_back(data[offset + (i + 1)]);
      m_vertices.push_back(data[offset + m_discLat + 1 + (i + 1)]);
      m_vertices.push_back(data[offset + i]);
      m_vertices.push_back(data[offset + m_discLat + 1 + (i + 1)]);
      m_vertices.push_back(data[offset + i + m_discLat + 1]);
    }
  }

}

void Sphere::animation() {

}
