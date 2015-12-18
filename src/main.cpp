#include <iostream>

#include <GL/glew.h>

#ifdef __APPLE__
	#include <glimac/SDLAppleWindowManager.hpp>
#else
	#include <glimac/SDLWindowManager.hpp>
#endif

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "Quad.hpp" // Pour test
#include "TrackballCamera.hpp"
#include "Sphere.hpp"



using namespace glimac;


int main( int argc, char** argv ) {

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


	//////////////////////////////////////////////////////////////////////////////////////////////////// Pour tests

	// Shaders
	FilePath applicationPath(argv[0]);
    Program program = loadProgram(
        applicationPath.dirPath() + "shaders/default.vs.glsl",
        applicationPath.dirPath() + "shaders/default.fs.glsl"
    );
    program.use();

    // Z-buffer
    glEnable(GL_DEPTH_TEST);

    // Test object
    Quad monQuad;

    // Test camera
    TrackballCamera maCamera;
    TrackballPosition maPosition;
    maPosition.distance = 5.0;
    maPosition.angleX = 45.0;
    maPosition.angleY = 0.0;
    maCamera.addControlPoint( maPosition );
    maPosition.distance = 5.0;
    maPosition.angleX = 45.0;
    maPosition.angleY = 180.0;
    maCamera.addControlPoint( maPosition );

    // Matrices de projection...
    GLint uMVPMatrix = glGetUniformLocation( program.getGLId(), "uMVPMatrix" );
    GLint uMVMatrix = glGetUniformLocation( program.getGLId(), "uMVMatrix" );
    GLint uNormalMatrix = glGetUniformLocation( program.getGLId(), "uNormalMatrix" );
    glm::mat4 ProjMatrix = glm::perspective( glm::radians(70.f), 800.f/600.f, 0.1f, 100.f );
    glm::mat4 MVMatrix = maCamera.getViewMatrix();
    glm::mat4 NormalMatrix = glm::transpose( glm::inverse( MVMatrix ) );

	////////////////////////////////////////////////////////////////////////////////////////////////////


	glEnable(GL_DEPTH_TEST);

	// Graphic objects
	Sphere mySphere;

	// Display loop
	bool done = false;
	while( !done ) {

		SDL_Event e;
    	while( windowManager.pollEvent( e ) ) {
    	if( e.type == SDL_QUIT )
				done = true;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////// Pour tests
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// Camera
		maCamera.moveOnPath();
		MVMatrix = maCamera.getViewMatrix();

        glUniformMatrix4fv( uMVPMatrix, 1, GL_FALSE, glm::value_ptr( ProjMatrix * MVMatrix ) );
        glUniformMatrix4fv( uMVMatrix, 1, GL_FALSE, glm::value_ptr( MVMatrix ) );
        glUniformMatrix4fv( uNormalMatrix, 1, GL_FALSE, glm::value_ptr( NormalMatrix ) );

        monQuad.draw();
				mySphere.draw();

        windowManager.swapBuffers();

        ////////////////////////////////////////////////////////////////////////////////////////////////////

	}

	return EXIT_SUCCESS;
}
