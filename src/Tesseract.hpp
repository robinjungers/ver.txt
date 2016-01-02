#pragma once

#include "Object3D.hpp"

class Tesseract : public Object3D {

  private:
		static GLint m_uIsLine;

    void buildVertices();

  public:
    Tesseract();

    static void getUniformLocations( Program &program );

  	void transition();
    void animation();

    void draw();

};
