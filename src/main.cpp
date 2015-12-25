/*
A NOTER
possibles soucis de compilation dus aux changement de fonctions entre SDL 1.2 et SDL2
> résolus en principe
*/

#include <iostream>

#include <GL/glew.h>

#ifdef __APPLE__
	#include <glimac/SDLAppleWindowManager.hpp>
#else
	#include <glimac/SDLWindowManager.hpp>
#endif

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "TrackballCamera.hpp"
#include "Texture.hpp"
#include "Light.hpp"
#include "Scene.hpp"
#include "InputManager.hpp"
#include "SceneManager.hpp"

#include "Sphere.hpp"
#include "Quad.hpp"


using namespace glimac;
using namespace glm;


int main( int argc, char** argv ) {

  // Initialize SDL and open a window
  SDLWindowManager windowManager( 800, 600, "Ver.txt" );

  // Initialize glew for OpenGL3+ support
  glewExperimental = GL_TRUE;
  GLenum glewInitError = glewInit();
  if( GLEW_OK != glewInitError ) {
    std::cerr << glewGetErrorString( glewInitError ) << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "OpenGL Version : " << glGetString( GL_VERSION ) << std::endl;
  std::cout << "GLEW Version   : " << glewGetString( GLEW_VERSION ) << std::endl;

	// Init inputManager
	InputManager inputManager;

	// Init sceneManager
	FilePath applicationPath( argv[0] );
	SceneManager sceneManager;
	sceneManager.loadSceneFromFile( applicationPath, "ver.1.txt", inputManager );

  // Display loop
  bool done = false;
  while( !done ) {

  	SDL_Event e;
  	while( windowManager.pollEvent( e ) ) {

  		if( e.type == SDL_QUIT )
				done = true;
			else if ( e.type == SDL_KEYDOWN ) {

				#ifdef __APPLE__
	      	SDL_Keycode keyPressed = e.key.keysym.sym;
				#else
					SDLKey keyPressed = e.key.keysym.sym;
				#endif

	      switch ( keyPressed ) {
	        case SDLK_ESCAPE:
	          done = true;
	        break;
					case SDLK_RETURN:
						if ( inputManager.validate() )
							sceneManager.setCurrentScene( inputManager.getIndex() );
					break;
					case SDLK_BACKSPACE:
						inputManager.deleteLastChar();
						inputManager.display();
					break;
        }

				if ( (keyPressed >= SDLK_a) && (keyPressed < SDLK_z) ) {
					string keyValue = SDL_GetKeyName( keyPressed );
					inputManager.addToInput( keyValue );
					inputManager.display();
				}

      }
    }

    // Dessin
    sceneManager.clear();
    sceneManager.draw();

    // Swap
    windowManager.swapBuffers();

  }

  return EXIT_SUCCESS;
}
