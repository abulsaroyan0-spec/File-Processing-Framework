#include "TextDecorators.hpp"

#include <cctype>
#include <stdexcept>
#include <utility>

TextDecorator::TextDecorator(std::unique_ptr<TextProcessor> p)
    : ptr(std::move(p)) {
    if (!ptr) {
        throw std::invalid_argument("Processor cannot be null");
    }
}

std::string TextDecorator::process(const std::string& text) const {
    return ptr->process(text);
}


UppercaseDecorator::UppercaseDecorator(std::unique_ptr<TextProcessor> p)
    : TextDecorator(std::move(p)) {}

std::string UppercaseDecorator::process(const std::string& text) const {
    std::string result = TextDecorator::process(text);

    for (char& ch : result) {
        ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
    }

    return result;
}

LowercaseDecorator::LowercaseDecorator(std::unique_ptr<TextProcessor> p) 
					: TextDecorator(std::move(p)) {}

std::string LowercaseDecorator::process(const std::string& text) const {
	std::string result = TextDecorator::process(text);

	for (char& ch : result) {
		ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
	}
	return result;
}

ReplaceDecorator::ReplaceDecorator(std::unique_ptr<TextProcessor> p,
        const std::string& search,
        const std::string& replacement) : TextDecorator(std::move(p)),
		search(search), replacement(replacement) {
			if (search.empty()) {
				throw std::invalid_argument("Search string cannot be empty");
			}
}

std::string ReplaceDecorator::process(const std::string& text) const {
    std::string result = TextDecorator::process(text);

    std::size_t pos = 0;

    while ((pos = result.find(search, pos)) != std::string::npos) {
        result.replace(pos, search.length(), replacement);
        pos += replacement.length();
    }

    return result;
}


LineFilterDecorator::LineFilterDecorator(
    std::unique_ptr<TextProcessor> p,
    const std::string& keyword): TextDecorator(std::move(p)),
    							 keyword(keyword) {}


std::string LineFilterDecorator::process(const std::string& text) const {
    std::string result;
    std::size_t lineStart = 0;

    while (lineStart < text.size()) {
        std::size_t lineEnd = text.find('\n', lineStart);

        bool hasNewline = lineEnd != std::string::npos;

        std::string line = text.substr(
            lineStart,
            hasNewline ? lineEnd - lineStart : std::string::npos
        );

        if (line.find(keyword) == std::string::npos) {
            result += line;

            if (hasNewline) {
                result += '\n';
            }
        }

        if (!hasNewline) {
            break;
        } 

        lineStart = lineEnd + 1;
    }

    if (!text.empty() && text.back() == '\n' && keyword.empty()) {
        result += '\n';
    }

    return result;
}
