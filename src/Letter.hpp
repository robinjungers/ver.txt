#pragma once

#include "Object3D.hpp"


class Letter : public Object3D {

  private:
  	const float m_letterWidth;
  	unsigned char m_index;

    void buildVertices();

  public:
    Letter( unsigned char index );

  	void transition();
    void animation();

};
