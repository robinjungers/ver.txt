#include <iostream>

#include <GL/glew.h>

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

const unsigned viewportWidth = 800, viewportHeight = 600; // Viewport dimensions
const float FRAME_DURATION = 1000 / 60; // Frame duration


int main( int argc, char** argv ) {

  // Initialize SDL and open a window
  SDLWindowManager windowManager( viewportWidth, viewportHeight, "" );

  #ifndef __APPLE__
    SDL_EnableKeyRepeat( 400, 100 );
    SDL_EnableUNICODE(SDL_ENABLE);
  #endif

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

  // Enable Z-buffer
  glEnable(GL_DEPTH_TEST);


  // Init inputManager
  InputManager inputManager( viewportWidth, viewportHeight );

  // Init sceneManager
  FilePath applicationPath( argv[0] );
  SceneManager sceneManager;
  sceneManager.loadSceneFromFile( applicationPath, "ver.1.txt", inputManager, viewportWidth, viewportHeight );


  // Display loop
  bool done = false;
  float timer = 0.0;
  while( !done ) {

    // Used for frame rate cap
    Uint32 startTime = SDL_GetTicks();


    // Events
    SDL_Event e;
    while( windowManager.pollEvent( e ) ) {

      if( e.type == SDL_QUIT )
        done = true;

      #ifdef __APPLE__

        else if ( e.type == SDL_WINDOWEVENT ) {
          if ( e.window.event == SDL_WINDOWEVENT_RESIZED ) {
            glViewport(0, 0, e.window.data1, e.window.data2);
            sceneManager.updateViewportDimensions( e.window.data1, e.window.data2 );
            inputManager.updateViewportDimensions( e.window.data1, e.window.data2 );
          }
        }

      #else

        else if ( e.type == SDL_VIDEORESIZE ) {
          SDL_SetVideoMode(e.resize.w, e.resize.h, 32, SDL_OPENGL | SDL_RESIZABLE);
          glViewport(0, 0, e.resize.w, e.resize.h);
          sceneManager.updateViewportDimensions( e.resize.w, e.resize.h );
          inputManager.updateViewportDimensions( e.resize.w, e.resize.h );
        }

      #endif

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
              sceneManager.fadeOut();
            else
              sceneManager.morphing( inputManager.getInputValueHash() );
            break;

          case SDLK_BACKSPACE:
            inputManager.deleteLastChar();
            break;

        }

        if ( ( keyPressed >= SDLK_a ) && ( keyPressed < SDLK_z ) ) {
          #ifdef __APPLE__
            string keyValue = SDL_GetKeyName( keyPressed );
            inputManager.addToInput( keyValue[0] );
          #else
            inputManager.addToInput( e.key.keysym.unicode );
          #endif
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
    timer += 0.01;
    Uint32 elapsedTime = SDL_GetTicks() - startTime;

    if(elapsedTime < FRAME_DURATION)
      SDL_Delay(FRAME_DURATION - elapsedTime);

  }

  return EXIT_SUCCESS;
}
