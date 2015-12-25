#include "InputManager.hpp"

#include <iostream>
#include <algorithm>


InputManager::InputManager() {

  m_inputValue = "";
  m_index = 0;

}

void InputManager::addToInput( char c ) {

  m_inputValue += c;

}

void InputManager::addToInput( std::string s ) {

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

  std::cout << "Current input value : " << m_inputValue << std::endl;

}

void InputManager::clear() {

  m_inputValue = "";

}
