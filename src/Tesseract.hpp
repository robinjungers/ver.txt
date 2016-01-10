#pragma once

#include "Object3D.hpp"

class Tesseract : public Object3D {

  private:
		static GLint m_uIsLine;
		float m_rotate;

    void buildVertices();

  public:
    Tesseract();

    static void getUniformLocations( Program &program );

    void animation();

    void draw();

};
