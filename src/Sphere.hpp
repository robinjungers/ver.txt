#pragma once

#include "Object3D.hpp"


class Sphere: public Object3D {

  private:
    void buildVertices( GLfloat r, GLsizei discLat, GLsizei discLong );

  public:
    Sphere( GLfloat r = 1, GLsizei discLat = 32, GLsizei discLong = 16 );

    void transition();
    void animation();

};
