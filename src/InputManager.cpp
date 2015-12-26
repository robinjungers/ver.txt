#include "InputManager.hpp"

#include <iostream>
#include <algorithm>

#include <glimac/glm.hpp>

#include "Texture.hpp"

using namespace glm;

GLint InputManager::m_uIsText = 0;
GLint InputManager::m_uMVPMatrix = 0;

InputManager::InputManager() : m_fontTexture( "font.png" ) {

  m_inputValue = "";
  m_index = 0;

  // Initialise bitmap font
  for ( unsigned i = 0; i < 26; i++ ) {
    Letter letter( i );
    letter.setTexture( &m_fontTexture );
    m_letters.push_back(letter);
  }

}

void InputManager::getUniformLocations( Program &program ) {

  m_uIsText = glGetUniformLocation( program.getGLId(), "uIsText" );
  m_uMVPMatrix = glGetUniformLocation( program.getGLId(), "uMVPMatrix" );

}

void InputManager::addToInput( char c ) {

  if ( m_inputValue.size() < maxLetters )
    m_inputValue += c;

}

void InputManager::addToInput( std::string s ) {

  if ( m_inputValue.size() < maxLetters )
    m_inputValue += s;

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

  //std::cout << "Current input value : " << m_inputValue << std::endl;

  glUniform1i(m_uIsText, true);

  unsigned nbLetters = m_inputValue.size();

  glm::mat4 MVPMatrix = scale(mat4(1), vec3( 0.1, 0.1, 0.1 ));
  MVPMatrix = translate( MVPMatrix, vec3( -( nbLetters * 0.5 ), 0.5, 0.0 ) );

  for ( unsigned i = 0; i < nbLetters; ++i ) {

    unsigned char character = m_inputValue[i];

    glUniformMatrix4fv( m_uMVPMatrix, 1, GL_FALSE, value_ptr( MVPMatrix ) );
    m_letters[ m_inputValue[ i ] - asciiLettersOffset ].draw();

    MVPMatrix = translate( MVPMatrix, vec3( 1.0, 0.0, 0.0 ) );

  }

  glUniform1i(m_uIsText, false);

}

void InputManager::clear() {

  m_inputValue = "";

}
