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


	FilePath applicationPath( argv[0] );
	Scene scene( "La scène de Robin hihihi",
                 applicationPath.dirPath() + "shaders/default.vs.glsl",
                 applicationPath.dirPath() + "shaders/default.fs.glsl"
                 );

  // Z-buffer
  glEnable(GL_DEPTH_TEST);

  // Test camera
  TrackballCamera * camera = new TrackballCamera( 6000 );
  camera->addControlPoint( (TrackballPosition) { 5.0, 30.0,   0.0 } );
  camera->addControlPoint( (TrackballPosition) { 8.0, 60.0, 180.0 } );
  camera->addControlPoint( (TrackballPosition) { 5.0, 30.0, 360.0 } );

  // Test light
  // Light * light = new Light( vec4( 0.0, 5.0, -5.0, 1.0 ), vec3( 25.0, 25.0, 25.0 ) );
  Light * light = new Light( vec4( 0.0, -1.0, 0.0, 0.0 ), vec3( 25.0, 25.0, 25.0 ) );

  // Test objects
  Quad * quad = new Quad();
  scene.addMaterial( vec3( 1.0, 0.0, 0.0 ), vec3( 1.0, 1.0, 1.0 ), 30 );
  scene.addTexture( "lol.jpg" );
  // scene.addObject3D( quad, 0, 0 );
  scene.addObject3D( quad, 0 );

  // Test scene
  scene.setCamera( camera );
  scene.addLight( light );

  // Display loop
  bool done = false;
  while( !done ) {

  SDL_Event e;
  while( windowManager.pollEvent( e ) ) {
    
    if( e.type == SDL_QUIT )
		done = true;
    }

    // Dessin
    scene.clear();
    scene.draw();

    // Swap
    windowManager.swapBuffers();

    }

  return EXIT_SUCCESS;
}
