#pragma once

#include "Object3D.hpp"


class SkyBox: public Solid {

  private:
    int m_width;
    int m_height;
    int m_depth;

  public:
    SkyBox();
    void buildVertices();

    void animation();

};
