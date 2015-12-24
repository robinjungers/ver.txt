#pragma once

#include <GL/glew.h>
#include "glimac/glm.hpp"
#include "glimac/Program.hpp"
#include <glimac/Image.hpp>
#include <string>
#include <iostream>


using namespace glimac;
using namespace glm;
using namespace std;

class Texture {

  private:
	GLuint m_texture;
	static GLint m_uTexture;

  public:
	Texture( string fileTexture );

	static void getUniformLocations( Program &program );

	void bindTexture();
	void debindTexture();

};
