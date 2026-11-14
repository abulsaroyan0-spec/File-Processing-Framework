#pragma once

#include "TextReader.hpp"
#include "ProcessingPipeline.hpp"

#include <memory>
#include <string>

class FileProcessor {
private:
    std::unique_ptr<TextReader> reader;
    ProcessingPipeline pipeline;

public:
    FileProcessor(
        std::unique_ptr<TextReader> reader,
        ProcessingPipeline pipeline
    );

    void processFile(
        const std::string& inputPath,
        const std::string& outputPath
    ) const;
};