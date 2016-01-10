#pragma once

#include "Object3D.hpp"

class Column: public Solid {

  private:
    float m_width;
    float m_height;
    float m_terrainLong;
    float m_terrainLat;

   public:
	Column();

	void buildVertices();

	void buildSingleColumn(float x, float height, float z);

  void buildSol();

	void animation();

};
