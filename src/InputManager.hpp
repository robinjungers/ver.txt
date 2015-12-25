#pragma once

#include <string>
#include <vector>

class InputManager {

  private:
    std::string m_inputValue;
    unsigned m_index;

    std::vector<std::string> m_inputEntries;

  public:
    InputManager();

    void addToInput( char c );
    void addToInput( std::string s );
    void deleteLastChar();

    void addEntry( std::string entry );

    unsigned getIndex();

    bool validate();
    void display();
    void clear();

};
