#pragma once

#include "Object3D.hpp"

class Sphere : public Solid {

  private:
    GLfloat m_r;
    GLsizei m_discLat;
    GLsizei m_discLong;

  public:
    Sphere();
    Sphere( GLfloat r, GLsizei discLat, GLsizei discLong );
    void buildVertices();

    void animation();

};
