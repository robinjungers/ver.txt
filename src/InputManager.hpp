#pragma once

#include <string>
#include <vector>

#include "Letter.hpp"

const unsigned maxLetters = 12;

const unsigned asciiLettersOffset = 'A';

class InputManager {

  private:
    std::string m_inputValue;
    unsigned m_index;

    std::vector<std::string> m_inputEntries;
    std::vector<Letter> m_letters;

    glm::mat4 m_MVPMatrix;

    static GLint m_uMVPMatrix;
    Texture m_fontTexture;

  public:
    InputManager( float viewportWidth, float viewportHeight );

    static void getUniformLocations( Program &program );
    void updateViewportDimensions( float viewportWidth, float viewportHeight );

    void addToInput( char c );
    void deleteLastChar();

    void addEntry( std::string entry );

    unsigned getIndex();
    std::string getInputValue();
    float getInputValueHash();

    bool validate();
    void display();
    void clear();

};
