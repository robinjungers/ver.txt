#pragma once

#include "Object3D.hpp"

const float letterWidth = 1.0 / 27.0;

class Letter : public Solid {

  private:
  	unsigned char m_index;

  public:
    Letter( unsigned char index );
    void buildVertices();

    void animation();

};
