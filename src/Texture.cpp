#include "Texture.hpp"

using namespace glimac;
using namespace glm;

Texture::Texture( string fileTexture, Program &program ) {
	
    unique_ptr<Image> Texture = loadImage( "assets/" + fileTexture );
	
    if( Texture == NULL )
        cerr << "Can't load texture " << fileTexture << " \n" << endl;

    glGenTextures( 1, &m_texture );
    glBindTexture( GL_TEXTURE_2D, m_texture );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Texture->getWidth(), Texture->getHeight(), 0, GL_RGBA, GL_FLOAT, Texture->getPixels() );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glBindTexture( GL_TEXTURE_2D, 0 );

    uTexture = glGetUniformLocation( program.getGLId(), "uTexture" );
    
}

void Texture::bindTexture() {
	glUniform1i( uTexture, 0 );
	glBindTexture( GL_TEXTURE_2D, m_texture );
}

void Texture::debindTexture() {
	glBindTexture( GL_TEXTURE_2D, 0 );
}