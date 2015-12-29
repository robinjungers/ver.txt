#pragma once

#include "Object3D.hpp"


class Quad : public Object3D {

  public:
    Quad();
    void buildVertices();

    void animation();

};
