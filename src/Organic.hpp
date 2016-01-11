#pragma once

#include "Object3D.hpp"

class Organic : public Solid {

  private:
    void buildVertices();

  public:
    Organic();

    void animation();

};
