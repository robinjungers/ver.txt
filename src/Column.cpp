#include "Column.hpp"
#include "PerlinNoise.hpp"
#include "tools.hpp"

#include <vector>

using namespace glimac;
using namespace glm;

Column::Column(){
    m_width = 200;
    m_height = 200;
    m_terrainLong = 50;
    m_terrainLat = 50;
    buildVertices();
    initVertices();
}

void Column::buildVertices() {

  PerlinNoise pn;
  PerlinNoise pn2;
    m_vertices.clear();

    buildSol();

    float n(0);

  for ( unsigned i = 0; i <= m_terrainLong; ++i ) {
    for ( unsigned j = 0; j <= m_terrainLat; ++j ) {

        if((j%10)==0)
            n++;

        float x = map( i, 0, m_terrainLong, -m_width/2, m_width/2 );
        float z = map( j, 0, m_terrainLat, -m_height/2, m_height/2 ) + 100 * pn.noise( i, j, 0.1 ) - 50;
        float distToCenter = x*x + z*z;
        float height =  ( 0.002 * distToCenter * pn.noise( 0.1 * x, 0.1 * z, m_currentMorphingParameter ) + 30*pn.noise( 100.1*(int)(0.1*i), 100.1*(int)(0.1*j), 0.1 ) - 15 );

        buildSingleColumn(x + pn.noise( x, height, z ), height * m_currentFadingParameter, z + pn.noise( x, height, z ));

    }
  }

}

void Column::buildSingleColumn(float x, float height, float z){

    vec3 normalDessus = vec3(0.0,1.0,0.0);
    vec3 normalDessous = vec3(0.0,-1.0,0.0);

    vec3 normalDevant = vec3(0.0, 0.0, 1.0);
    vec3 normalDerriere = vec3(0.0, 0.0, -1.0);

    vec3 normalDroiteDevant = vec3(1.0, 0.0, 0.5);
    vec3 normalDroiteDerriere =  vec3(1.0, 0.0, -0.5);

    vec3 normalGaucheDevant = vec3(-1.0, 0.0, 0.5);
    vec3 normalGaucheDerriere = vec3(-1.0, 0.0, -0.5);

    ShapeVertex vertex;

//face de devant

    vertex.position = vec3(-1.0 + x, -1.0, 1.0 + z);
    vertex.normal= normalDevant;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x , height, 1.0 + z);
    vertex.normal= normalDevant;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, 1.0 + z);
    vertex.normal= normalDevant;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, 1.0 + z);
    vertex.normal= normalDevant;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, -1.0, 1.0 + z);
    vertex.normal= normalDevant;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, -1.0, 1.0 + z);
    vertex.normal= normalDevant;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

// face de dessous

    vertex.position = vec3(-1.0 + x, -1.0, -1.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5 + x, -1.0, 0.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, -1.0, 1.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, -1.0, 1.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, -1.0, -1.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, -1.0, 1.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, -1.0, 1.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, -1.0, -1.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, -1.0, -1.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, -1.0, -1.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5 + x, -1.0, 0.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, -1.0, 1.0 + z);
    vertex.normal= normalDessous;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

// face de gauche - devant

    vertex.position = vec3(-1.0 + x, -1.0, 1.0 + z);
    vertex.normal= normalGaucheDevant;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5 + x, -1.0, 0.0 + z);
    vertex.normal= normalGaucheDevant;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, height, 1.0 + z);
    vertex.normal= normalGaucheDevant;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, height, 1.0 + z);
    vertex.normal= normalGaucheDevant;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5 + x, height, 0.0 + z);
    vertex.normal= normalGaucheDevant;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5 + x, -1.0, 0.0 + z);
    vertex.normal= normalGaucheDevant;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

// face de gauche - derrière

    vertex.position = vec3(-1.0 + x, -1.0, -1.0 + z);
    vertex.normal= normalGaucheDerriere;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5 + x, -1.0, 0.0 + z);
    vertex.normal= normalGaucheDerriere;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5 + x, height, 0.0 + z);
    vertex.normal= normalGaucheDerriere;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5 + x, height, 0.0 + z);
    vertex.normal= normalGaucheDerriere;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, height, -1.0 + z);
    vertex.normal= normalGaucheDerriere;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0  + x, -1.0, -1.0 + z);
    vertex.normal= normalGaucheDerriere;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

// face de derrière

    vertex.position = vec3(-1.0  + x, -1.0, -1.0 + z);
    vertex.normal= normalDerriere;
    vertex.texCoords = vec2(0.0,1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0  + x, height, -1.0  + z);
    vertex.normal = normalDerriere;
    vertex.texCoords = vec2(0.0,0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0  + x, height, -1.0 + z);
    vertex.normal = normalDerriere;
    vertex.texCoords = vec2(1.0,0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, -1.0 + z);
    vertex.normal = normalDerriere;
    vertex.texCoords = vec2(1.0,0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, -1.0,-1.0 + z);
    vertex.normal = normalDerriere;
    vertex.texCoords = vec2(0.0,1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, -1.0,-1.0 + z);
    vertex.normal = normalDerriere;
    vertex.texCoords = vec2(1.0,1.0);

    m_vertices.push_back(vertex);

// face de droite - devant

    vertex.position = vec3(1.0 + x, -1.0, 1.0 + z);
    vertex.normal = normalDroiteDevant;
    vertex.texCoords = vec2( 0.0, 1.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, 1.0 + z);
    vertex.normal = normalDroiteDevant;
    vertex.texCoords = vec2( 0.0, 0.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5 + x, -1.0, 0.0 + z);
    vertex.normal = normalDroiteDevant;
    vertex.texCoords = vec2( 1.0, 1.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5 + x, -1.0, 0.0 + z);
    vertex.normal = normalDroiteDevant;
    vertex.texCoords = vec2( 1.0, 1.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5 + x, height, 0.0 + z);
    vertex.normal = normalDroiteDevant;
    vertex.texCoords = vec2( 1.0, 0.0 );

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, 1.0 + z);
    vertex.normal = normalDroiteDevant;
    vertex.texCoords = vec2( 0.0, 0.0 );

    m_vertices.push_back(vertex);

// face de droite - derriere

    vertex.position = vec3(1.0 + x, -1.0, -1.0 + z);
    vertex.normal = normalDroiteDerriere;
    vertex.texCoords = vec2(1.0,1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, -1.0 + z);
    vertex.normal = normalDroiteDerriere;
    vertex.texCoords = vec2(1.0,0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5 + x, height, 0.0 + z);
    vertex.normal = normalDroiteDerriere;
    vertex.texCoords = vec2(0.0,0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5 + x, height, 0.0 + z);
    vertex.normal = normalDroiteDerriere;
    vertex.texCoords = vec2(0.0,.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5 + x, -1.0, 0.0 + z);
    vertex.normal = normalDroiteDerriere;
    vertex.texCoords = vec2(0.0,1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, -1.0, -1.0 + z);
    vertex.normal = normalDroiteDerriere;
    vertex.texCoords = vec2(1.0,1.0);

    m_vertices.push_back(vertex);

// face de dessus

    vertex.position = vec3(-1.0 + x, height, -1.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.5 + x, height, 0.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, height, 1.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, height, 1.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, height, -1.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, 1.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, 1.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, -1.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-1.0 + x, height, -1.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, -1.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.5 + x, height, 0.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(1.0 + x, height, 1.0 + z);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

}

void Column::buildSol() {

    vec3 normalDessus = vec3(0.0,1.0,0.0);

    ShapeVertex vertex;
    float w = m_width/2;
    float h = m_height/2;

    vertex.position = vec3(-w, 0.0, h);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(0.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-w, 0.0, -h);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(w, 0.0, h);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(w, 0.0, h);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(1.0, 1.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(w, 0.0, -h);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(1.0, 0.0);

    m_vertices.push_back(vertex);

    vertex.position = vec3(-w, 0.0, -h);
    vertex.normal = normalDessus;
    vertex.texCoords = vec2(0.0, 0.0);

    m_vertices.push_back(vertex);
}

void Column::animation() {

}
