#pragma once

#include <string>

class TextProcessor {
	public:
		virtual ~TextProcessor() = default;

		virtual std::string process(const std::string& text) const = 0;
};