#pragma once

#include <string>
#include <vector>

#include "Letter.hpp"

const unsigned maxLetters = 12;
const unsigned asciiLettersOffset = 97;

class InputManager {

  private:
    std::string m_inputValue;
    unsigned m_index;

    std::vector<std::string> m_inputEntries;
    std::vector<Letter> m_letters;

    static GLint m_uMVPMatrix;
    static GLint m_uIsText;
    Texture m_fontTexture;

  public:
    InputManager();

    static void getUniformLocations( Program &program );

    void addToInput( char c );
    void addToInput( std::string s );
    void deleteLastChar();

    void addEntry( std::string entry );

    unsigned getIndex();

    bool validate();
    void display();
    void clear();

};
