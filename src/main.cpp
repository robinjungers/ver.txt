#include <iostream>

#include <GL/glew.h>

#ifdef __APPLE__
	#include <glimac/SDLAppleWindowManager.hpp>
#else
	#include <glimac/SDLWindowManager.hpp>
#endif

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "Object3D.hpp"


using namespace glimac;


int main( int argc, char **) {
	// Initialize SDL and open a window
  SDLWindowManager windowManager(800, 600, "GLImac");

  // Initialize glew for OpenGL3+ support
	glewExperimental = GL_TRUE;
  GLenum glewInitError = glewInit();
  if( GLEW_OK != glewInitError ) {
    std::cerr << glewGetErrorString(glewInitError) << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version   : " << glewGetString(GLEW_VERSION) << std::endl;

	// Display loop
	bool done = false;
  while(!done) {

		SDL_Event e;
    while( windowManager.pollEvent(e) ) {
      if( e.type == SDL_QUIT )
				done = true;
    }


		//////////////////////////////
		/*       DESSINER ICI       */
		//////////////////////////////


	}

	return 0;
}
