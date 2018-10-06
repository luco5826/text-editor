#ifndef TextDocument_H
#define TextDocument_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>

#include <algorithm>
#include <string>

#include "SpecialChars.h"

class TextDocument {
   public:
    bool init(std::string& filename);
    bool saveFile(std::string& filename);
    bool hasChanged();

    sf::String getLine(int lineNumber);
    int charsInLine(int line) const;
    int getLineCount() const;

    void addTextToPos(sf::String& text, int line, int charN);
    void removeTextFromPos(int amount, int line, int charN);
    sf::String getTextFromPos(int amount, int line, int charN);

    void swapLines(int lineA, int lineB);

    int charAmountContained(int startLineN, int startCharN, int endLineN, int endCharN);

   private:
    bool initLinebuffer();
    sf::String buffer;
    int length;
    std::vector<int> lineBuffer;
    bool documentHasChanged;

    int getBufferPos(int line, int charN);

    void swapWithNextLine(int line);

    sf::String toUtf32(const std::string& inString);
};

#endif
