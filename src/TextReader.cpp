#include "TextReader.hpp"

#include <sstream>
#include <stdexcept>
#include <string>

std::string WholeFileReader::read(std::ifstream& file) const {
    std::ostringstream buffer;

    buffer << file.rdbuf();

    if (file.bad()) {
        throw std::runtime_error("Error while reading file");
    }

    return buffer.str();
}

std::string LineByLineReader::read(std::ifstream& file) const {
    std::string result;
    std::string line;

    while (std::getline(file, line)) {
        result += line;
        result += '\n';
    }
	
	if (!file.eof()) {
		result += '\n';
	}

    if (file.bad()) {
        throw std::runtime_error("Error while reading file");
    }


    return result;
}