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
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}
	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version   : " << glewGetString(GLEW_VERSION) << std::endl;


	FilePath applicationPath( argv[0] );
	Scene scene(
		"La scène de Robin hihihi",
    applicationPath.dirPath() + "shaders/default.vs.glsl",
  	applicationPath.dirPath() + "shaders/default.fs.glsl"
  );

  // Z-buffer
  glEnable(GL_DEPTH_TEST);

  // Test camera
	TrackballCamera * camera = new TrackballCamera( 100 );
  camera->addControlPoint( (TrackballPosition) { 5.0, 45.0,   0.0 } );
  camera->addControlPoint( (TrackballPosition) { 6.0, 25.0, 180.0 } );
  camera->addControlPoint( (TrackballPosition) { 5.0, 45.0, 360.0 } );

	// Test light
	PointLight * light = new PointLight( vec3( 0.0, 5.0, -5.0 ) );
	light->setIntensity( vec3( 25.0, 25.0, 25.0 ) );

	// Test objects
  Quad * quad = new Quad();
  quad->setTexture( "lol.jpg" );
	quad->setMaterial( vec3( 1.0, 1.0, 1.0 ), vec3( 1.0, 1.0, 1.0 ), 30.0 );

  // Test scene
	scene.setCamera( camera );
	scene.addLight( light );
	scene.addObject3D( quad );

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
