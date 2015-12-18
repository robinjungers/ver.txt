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
#include "Texture.hpp"
#include "Light.hpp"



using namespace glimac;
using namespace glm;


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

    // Test objects
    Quad monQuad;

    // Test camera
    TrackballCamera maCamera(6000);
    TrackballPosition maPosition;
    maPosition.distance = 5.0;
    maPosition.angleX = 45.0;
    maPosition.angleY = 0.0;
    maCamera.addControlPoint( maPosition );
    maPosition.distance = 5.0;
    maPosition.angleX = 45.0;
    maPosition.angleY = 180.0;
    maCamera.addControlPoint( maPosition );
    maPosition.distance = 5.0;
    maPosition.angleX = 45.0;
    maPosition.angleY = 360.0;
    maCamera.addControlPoint( maPosition );

    // Matrices de projection...
    GLint uMVPMatrix = glGetUniformLocation( program.getGLId(), "uMVPMatrix" );
    GLint uMVMatrix = glGetUniformLocation( program.getGLId(), "uMVMatrix" );
    GLint uNormalMatrix = glGetUniformLocation( program.getGLId(), "uNormalMatrix" );
    mat4 ProjMatrix = perspective( radians(70.f), 800.f/600.f, 0.1f, 100.f );
    mat4 MVMatrix;
    mat4 NormalMatrix;

    // Test texture
    Texture maTexture( "lol.jpg", program );

    // Test light
    PointLight maLight( vec3( 0.0, 5.0, -5.0 ) );
    maLight.setIntensity( vec3( 25.0, 25.0, 25.0 ) );
    maLight.getUniformLocations( program );

    // Test material
    Material monMaterial( vec3( 1.0, 1.0, 1.0 ),
                          vec3( 1.0, 1.0, 1.0 ),
                          30.0 );
    monMaterial.getUniformLocations( program );
    monMaterial.sendUniformValues();

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
        NormalMatrix = transpose( inverse( MVMatrix ) );

        glUniformMatrix4fv( uMVPMatrix, 1, GL_FALSE, value_ptr( ProjMatrix * MVMatrix ) );
        glUniformMatrix4fv( uMVMatrix, 1, GL_FALSE, value_ptr( MVMatrix ) );
        glUniformMatrix4fv( uNormalMatrix, 1, GL_FALSE, value_ptr( NormalMatrix ) );

        maLight.sendUniformValues( MVMatrix );

        maTexture.bindTexture();

        monQuad.draw();
        // mySphere.draw();

        maTexture.debindTexture();

        windowManager.swapBuffers();

        ////////////////////////////////////////////////////////////////////////////////////////////////////


	}

	return EXIT_SUCCESS;
}
