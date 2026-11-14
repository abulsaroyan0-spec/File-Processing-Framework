#include "ProcessingPipeline.hpp"

#include <stdexcept>
#include <utility>

ProcessingPipeline::ProcessingPipeline(
    std::unique_ptr<TextProcessor> processor
)
    : processor(std::move(processor)) {
    if (!this->processor) {
        throw std::invalid_argument("Processor cannot be null");
    }
}

std::string ProcessingPipeline::process(const std::string& text) const {
    return processor->process(text);
}