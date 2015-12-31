#pragma once

#include "Object3D.hpp"

class Column: public Object3D {

   public:
	Column();

	void buildVertices();
    
	void animation();

};