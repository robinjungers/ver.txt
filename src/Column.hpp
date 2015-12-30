#pragma once

#include "Object3D.hpp"

class Column: public Object3D{

  private:
    void buildVertices();

   public:
	Column();

	void transition();
    void animation();

};