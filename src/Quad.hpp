#pragma once

#include "Object3D.hpp"


class Quad : public Object3D {

  private:
    void buildVertices();

  public:
    Quad();

  	void transition();
    void animation();

};
