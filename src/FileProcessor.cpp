
#include "FileProcessor.hpp"

#include <fstream>
#include <stdexcept>
#include <utility>

FileProcessor::FileProcessor(
    std::unique_ptr<TextReader> reader,
    ProcessingPipeline pipeline
)
    : reader(std::move(reader)),
      pipeline(std::move(pipeline)) {
    if (!this->reader) {
        throw std::invalid_argument("Reader cannot be null");
    }
}

void FileProcessor::processFile(
    const std::string& inputPath,
    const std::string& outputPath
) const {
    if (inputPath.empty() || outputPath.empty()) {
        throw std::invalid_argument("File paths cannot be empty");
    }

    if (inputPath == outputPath) {
        throw std::invalid_argument("Input and output paths must be different");
    }

    std::ifstream inputFile(inputPath);

    if (!inputFile.is_open()) {
        throw std::runtime_error("Failed to open input file: " + inputPath);
    }

    std::string content = reader->read(inputFile);

    std::string processedContent = pipeline.process(content);

    std::ofstream outputFile(outputPath);

    if (!outputFile.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputPath);
    }

    outputFile << processedContent;
    outputFile.flush();

    if (!outputFile) {
        throw std::runtime_error("Failed to write to output file: " + outputPath);
    }
}
