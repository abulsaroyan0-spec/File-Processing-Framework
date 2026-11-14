
#pragma once

#include <string>
#include <fstream>

class TextReader {
public:
    virtual ~TextReader() = default;

    virtual std::string read(std::ifstream& file) const = 0;
};

class WholeFileReader : public TextReader {
public:
    std::string read(std::ifstream& file) const override;
};

class LineByLineReader : public TextReader {
public:
    std::string read(std::ifstream& file) const override;
};
