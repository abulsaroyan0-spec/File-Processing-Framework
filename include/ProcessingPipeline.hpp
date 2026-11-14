#pragma once

#include "TextProcessor.hpp"

#include <memory>
#include <string>

class ProcessingPipeline {
private:
    std::unique_ptr<TextProcessor> processor;

public:
    explicit ProcessingPipeline(std::unique_ptr<TextProcessor> processor);

    std::string process(const std::string& text) const;
};