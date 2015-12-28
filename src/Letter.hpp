#pragma once

#include "Object3D.hpp"

const float letterWidth = 1.0 / 27.0;

class Letter : public Object3D {

  private:
  	unsigned char m_index;

    void buildVertices();

  public:
    Letter( unsigned char index );

  	void transition();
    void animation();

};
