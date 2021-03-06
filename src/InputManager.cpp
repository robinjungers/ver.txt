#include "InputManager.hpp"

#include <iostream>
#include <algorithm>

#include <glimac/glm.hpp>

#include "Texture.hpp"

using namespace glm;

GLint InputManager::m_uMVPMatrix = 0;

InputManager::InputManager( float viewportWidth, float viewportHeight ) : m_fontTexture( "font.png" ) {

  m_inputValue = "VER.TXT";

  m_index = 0;

  // Initialise bitmap font
  for ( unsigned i = 0; i < 27; i++ ) {
    Letter letter( i );
    letter.setTexture( &m_fontTexture );
    letter.setMaterial( new Material( vec3(1), vec3(0), 0 ) );
    m_letters.push_back(letter);
  }

  // Initialise display matrix
  updateViewportDimensions( viewportWidth, viewportHeight );

}

void InputManager::getUniformLocations( Program &program ) {
  m_uMVPMatrix = glGetUniformLocation( program.getGLId(), "uMVPMatrix" );
}

void InputManager::updateViewportDimensions( float viewportWidth, float viewportHeight ) {
  m_MVPMatrix = scale(mat4(1), vec3( 0.1, 0.1 * viewportWidth / viewportHeight, 0.1 ));
}

void InputManager::addToInput( char c ) {

  if ( c >= 'a' && c <= 'z' )
    c = c - 'a' + asciiLettersOffset;

  if ( m_inputValue.size() < maxLetters )
    m_inputValue += c;

}

void InputManager::deleteLastChar() {

  if ( m_inputValue.size() > 0 )
    m_inputValue.erase( m_inputValue.end()-1, m_inputValue.end() );

}



void InputManager::addEntry( std::string entry ) {

  m_inputEntries.push_back( entry );

}


unsigned InputManager::getIndex() {

  return m_index;

}

std::string InputManager::getInputValue() {

  return m_inputValue;

}

float InputManager::getInputValueHash() {

  float hash = 0.0;
  for ( unsigned i = 0; i < m_inputValue.size(); ++i )
    hash += 0.002 * ((int) m_inputValue[i]);

  return hash;

}



bool InputManager::validate() {

  for ( unsigned i = 0; i < m_inputEntries.size(); ++i ) {
    if ( m_inputValue == m_inputEntries[i] ) {
      m_index = i;
      std::cout << "Input validated. New index : " << m_index << std::endl;
      clear();
      return true;
    }
  }

  std::cout << "Input not validated." << std::endl;
  return false;

}

void InputManager::display() {

  unsigned nbLetters = m_inputValue.size();

  glm::mat4 MVPMatrix = translate( m_MVPMatrix, vec3( -( nbLetters * 0.5 ), 0.5, 0.0 ) );

  for ( unsigned i = 0; i < nbLetters; ++i ) {

    unsigned char character = m_inputValue[i];

    glUniformMatrix4fv( m_uMVPMatrix, 1, GL_FALSE, value_ptr( MVPMatrix ) );

    if ( character == '.' )
      m_letters[ 26 ].draw();
    else
      m_letters[ character - asciiLettersOffset ].draw();

    MVPMatrix = translate( MVPMatrix, vec3( 1.0, 0.0, 0.0 ) );

  }

}

void InputManager::clear() {

  m_inputValue = "";

}
