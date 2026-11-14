
#pragma once

#include "TextProcessor.hpp"
#include <memory>
#include <string>

class TextDecorator : public TextProcessor {
private:
    std::unique_ptr<TextProcessor> ptr;

public:
    explicit TextDecorator(std::unique_ptr<TextProcessor> p);

    std::string process(const std::string& text) const override;
};

class UppercaseDecorator : public TextDecorator {
public:
    explicit UppercaseDecorator(std::unique_ptr<TextProcessor> p);

    std::string process(const std::string& text) const override;
};

class LowercaseDecorator : public TextDecorator {
public:
    explicit LowercaseDecorator(std::unique_ptr<TextProcessor> p);

    std::string process(const std::string& text) const override;
};

class ReplaceDecorator : public TextDecorator {
private:
    std::string search;
    std::string replacement;

public:
    ReplaceDecorator(
        std::unique_ptr<TextProcessor> p,
        const std::string& search,
        const std::string& replacement
    );

    std::string process(const std::string& text) const override;
};

class LineFilterDecorator : public TextDecorator {
private:
    std::string keyword;

public:
    LineFilterDecorator(
        std::unique_ptr<TextProcessor> p,
        const std::string& keyword
    );

    std::string process(const std::string& text) const override;
};
