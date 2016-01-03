#pragma once

#include "Object3D.hpp"

class Column: public Solid {

   public:
	Column();

	void buildVertices();
    
	void animation();

};