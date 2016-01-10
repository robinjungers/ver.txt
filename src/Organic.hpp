#pragma once

#include "Object3D.hpp"

class Organic : public Solid {

  private:
    void buildVertices();
    float m_animationOffset;
    float m_animationStep;

  public:
    Organic();

    void animation();

};
