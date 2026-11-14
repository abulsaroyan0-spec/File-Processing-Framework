
#include "TextDecorators.hpp"
#include "TextReader.hpp"
#include "ProcessingPipeline.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>

class BasicTextProcessor : public TextProcessor {
public:
    std::string process(const std::string& text) const override {
        return text;
    }
};

void testUppercase() {
    std::unique_ptr<TextProcessor> processor =
        std::make_unique<UppercaseDecorator>(
            std::make_unique<BasicTextProcessor>()
        );

    if (processor->process("hello") == "HELLO") {
        std::cout << "Uppercase: PASSED\n";
    }
    else {
        std::cout << "Uppercase: FAILED\n";
    }
}

void testLowercase() {
    std::unique_ptr<TextProcessor> processor =
        std::make_unique<LowercaseDecorator>(
            std::make_unique<BasicTextProcessor>()
        );

    if (processor->process("HELLO") == "hello") {
        std::cout << "Lowercase: PASSED\n";
    }
    else {
        std::cout << "Lowercase: FAILED\n";
    }
}

void testReplace() {
    std::unique_ptr<TextProcessor> processor =
        std::make_unique<ReplaceDecorator>(
            std::make_unique<BasicTextProcessor>(),
            "cat",
            "dog"
        );

    if (processor->process("cat and cat") == "dog and dog") {
        std::cout << "Replace: PASSED\n";
    }
    else {
        std::cout << "Replace: FAILED\n";
    }
}

void testLineFilter() {
    std::unique_ptr<TextProcessor> processor =
        std::make_unique<LineFilterDecorator>(
            std::make_unique<BasicTextProcessor>(),
            "ERROR"
        );

    std::string input = "Hello\nERROR found\nWorld";
    std::string expected = "Hello\nWorld";

    if (processor->process(input) == expected) {
        std::cout << "LineFilter: PASSED\n";
    }
    else {
        std::cout << "LineFilter: FAILED\n";
    }
}

void testPipelineOrder() {
    std::unique_ptr<TextProcessor> processor =
        std::make_unique<UppercaseDecorator>(
            std::make_unique<BasicTextProcessor>()
        );

    processor = std::make_unique<ReplaceDecorator>(
        std::move(processor),
        "HELLO",
        "HI"
    );

    ProcessingPipeline pipeline(std::move(processor));

    if (pipeline.process("hello") == "HI") {
        std::cout << "Pipeline order: PASSED\n";
    }
    else {
        std::cout << "Pipeline order: FAILED\n";
    }
}

void testEmptySearch() {
    try {
        std::unique_ptr<TextProcessor> processor =
            std::make_unique<ReplaceDecorator>(
                std::make_unique<BasicTextProcessor>(),
                "",
                "new"
            );

        std::cout << "Empty search: FAILED\n";
    }
    catch (const std::invalid_argument&) {
        std::cout << "Empty search: PASSED\n";
    }
}

int main() {
    testUppercase();
    testLowercase();
    testReplace();
    testLineFilter();
    testPipelineOrder();
    testEmptySearch();

    return 0;
}
