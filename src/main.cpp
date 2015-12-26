#include <iostream>

#include <GL/glew.h>

#ifdef __APPLE__
	#include <glimac/SDLAppleWindowManager.hpp>
#else
	#include <glimac/SDLWindowManager.hpp>
#endif

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "InputManager.hpp"
#include "SceneManager.hpp"


using namespace glimac;
using namespace glm;


int main( int argc, char** argv ) {

  // Initialize SDL and open a window
  SDLWindowManager windowManager( 800, 600, "Ver.txt" );

  SDL_EnableKeyRepeat( 400, 100 );
  SDL_EnableUNICODE( 1 );

  // Initialize glew for OpenGL3+ support
  glewExperimental = GL_TRUE;
  GLenum glewInitError = glewInit();
  if( GLEW_OK != glewInitError ) {
    std::cerr << glewGetErrorString( glewInitError ) << std::endl;
    return EXIT_FAILURE;
  }
  std::cout << "OpenGL Version : " << glGetString( GL_VERSION ) << std::endl;
  std::cout << "GLEW Version   : " << glewGetString( GLEW_VERSION ) << std::endl;

  // Enable OpenGL blending
  glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Frame duration
  const float FRAME_DURATION = 1000 / 60;


	// Init inputManager
	InputManager inputManager;

	// Init sceneManager
	FilePath applicationPath( argv[0] );
	SceneManager sceneManager;
	sceneManager.loadSceneFromFile( applicationPath, "ver.1.txt", inputManager );


  // Display loop
  bool done = false;
  while( !done ) {

  	// Used for frame rate cap
  	Uint32 startTime = SDL_GetTicks();


  	// Events
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
						break;

        }

				if ( ( keyPressed >= SDLK_a ) && ( keyPressed < SDLK_z ) ) {
					string keyValue = SDL_GetKeyName( keyPressed );
					inputManager.addToInput( keyValue );
				}

      }
    }


    // Draw
    sceneManager.clear();
    sceneManager.draw();

    inputManager.display();


    // Swap
    windowManager.swapBuffers();


    // Frame rate cap
    Uint32 elapsedTime = SDL_GetTicks() - startTime;

    if(elapsedTime < FRAME_DURATION)
      SDL_Delay(FRAME_DURATION - elapsedTime);

  }

  return EXIT_SUCCESS;
}
