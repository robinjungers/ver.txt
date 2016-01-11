#pragma once

#include "Object3D.hpp"

class Terrain : public Solid {

  private:
    float m_width;
    float m_height;
    float m_terrainLong;
    float m_terrainLat;

  public:
    Terrain();
    Terrain( float width, float height, float terrainLong, float terrainLat );
    void buildVertices();

    void animation();

};
