#include "SkyBox.hpp"

#include <vector>
#include <cmath>
#include <GL/glew.h>
#include <glimac/common.hpp>
#include <glimac/glm.hpp>

using namespace std;
using namespace glimac;
using namespace glm;

SkyBox::SkyBox() {
  m_castsLight = false;
  m_isRescalable = false;

  m_width = 1000;
  m_height = 1000;
  m_depth = 1000;

  buildVertices();
  initVertices();
}

void SkyBox::buildVertices() {
  float w = m_width/2;
  float h = m_height/2;
  float d = m_depth/2;

  vec3 normalDessus = vec3(0.0,0.0,0.0);
  vec3 normalDessous = vec3(0.0,0.0,0.0);

  vec3 normalDevant = vec3(0.0,0.0,0.0);
  vec3 normalDerriere = vec3(0.0,0.0,0.0);

  vec3 normalDroite = vec3(0.0,0.0,0.0);
  vec3 normalGauche = vec3(0.0,0.0,0.0);

  ShapeVertex vertex;

//face de devant

  vertex.position = vec3(-w, -h, d);
  vertex.normal= normalDevant;
  vertex.texCoords = vec2(1.0, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, h, d);
  vertex.normal= normalDevant;
  vertex.texCoords = vec2(1.0, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, h, d);
  vertex.normal= normalDevant;
  vertex.texCoords = vec2(0.75, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, h, d);
  vertex.normal= normalDevant;
  vertex.texCoords = vec2(0.75, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, -h, d);
  vertex.normal= normalDevant;
  vertex.texCoords = vec2(0.75, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, -h, d);
  vertex.normal= normalDevant;
  vertex.texCoords = vec2(1.0, 0.334);

  m_vertices.push_back(vertex);

//face de droite

  vertex.position = vec3(w, -h, d);
  vertex.normal= normalDroite;
  vertex.texCoords = vec2(0.75, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, h, d);
  vertex.normal= normalDroite;
  vertex.texCoords = vec2(0.75, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, h, -d);
  vertex.normal= normalDroite;
  vertex.texCoords = vec2(0.499, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, h, -d);
  vertex.normal= normalDroite;
  vertex.texCoords = vec2(0.499, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, -h, -d);
  vertex.normal= normalDroite;
  vertex.texCoords = vec2(0.499, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, -h, d);
  vertex.normal= normalDroite;
  vertex.texCoords = vec2(0.75, 0.334);

  m_vertices.push_back(vertex);

//face derriere

  vertex.position = vec3(w, -h, -d);
  vertex.normal= normalDerriere;
  vertex.texCoords = vec2(0.499, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, h, -d);
  vertex.normal= normalDerriere;
  vertex.texCoords = vec2(0.499, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, h, -d);
  vertex.normal= normalDerriere;
  vertex.texCoords = vec2(0.251, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, h, -d);
  vertex.normal= normalDerriere;
  vertex.texCoords = vec2(0.251, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, -h, -d);
  vertex.normal= normalDerriere;
  vertex.texCoords = vec2(0.251, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, -h, -d);
  vertex.normal= normalDerriere;
  vertex.texCoords = vec2(0.499, 0.334);

  m_vertices.push_back(vertex);

//face gauche

  vertex.position = vec3(-w, -h, -d);
  vertex.normal= normalGauche;
  vertex.texCoords = vec2(0.251, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, h, -d);
  vertex.normal= normalGauche;
  vertex.texCoords = vec2(0.251, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, h, d);
  vertex.normal= normalGauche;
  vertex.texCoords = vec2(0.0, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, h, d);
  vertex.normal= normalGauche;
  vertex.texCoords = vec2(0.0, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, -h, d);
  vertex.normal= normalGauche;
  vertex.texCoords = vec2(0.0, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, -h, -d);
  vertex.normal= normalDerriere;
  vertex.texCoords = vec2(0.251, 0.334);

  m_vertices.push_back(vertex);

// face de dessous

  vertex.position = vec3(-w, -h, d);
  vertex.normal= normalDessous;
  vertex.texCoords = vec2(0.251, 0.0);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, -h, -d);
  vertex.normal= normalDessous;
  vertex.texCoords = vec2(0.251, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, -h, -d);
  vertex.normal= normalDessous;
  vertex.texCoords = vec2(0.499, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, -h, -d);
  vertex.normal= normalDessous;
  vertex.texCoords = vec2(0.499, 0.334);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, -h, d);
  vertex.normal= normalDessous;
  vertex.texCoords = vec2(0.499, 0.0);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, -h, d);
  vertex.normal= normalDessous;
  vertex.texCoords = vec2(0.251, 0.0);

  m_vertices.push_back(vertex);

// face de dessus

  vertex.position = vec3(-w, h, d);
  vertex.normal= normalDessus;
  vertex.texCoords = vec2(0.251, 1.0);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, h, -d);
  vertex.normal= normalDessus;
  vertex.texCoords = vec2(0.251, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, h, -d);
  vertex.normal= normalDessus;
  vertex.texCoords = vec2(0.499, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, h, -d);
  vertex.normal= normalDessus;
  vertex.texCoords = vec2(0.499, 0.665);

  m_vertices.push_back(vertex);

  vertex.position = vec3(w, h, d);
  vertex.normal= normalDessus;
  vertex.texCoords = vec2(0.499, 1.0);

  m_vertices.push_back(vertex);

  vertex.position = vec3(-w, h, d);
  vertex.normal= normalDessus;
  vertex.texCoords = vec2(0.251, 1.0);

  m_vertices.push_back(vertex);


}

void SkyBox::animation() {

}
