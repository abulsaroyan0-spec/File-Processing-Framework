
#include "FileProcessor.hpp"
#include "TextDecorators.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <limits>
#include <stdexcept>
#include <exception>
#include <utility>

class BasicTextProcessor : public TextProcessor {
public:
    std::string process(const std::string& text) const override {
        return text;
    }
};

int main() {
    try {
        std::string inputPath;
        std::string outputPath;

        std::cout << "Enter input file path: ";
        std::getline(std::cin, inputPath);

        std::cout << "Enter output file path: ";
        std::getline(std::cin, outputPath);

        int readerChoice;

        std::cout << "\nChoose reading strategy:\n";
        std::cout << "1. Whole file\n";
        std::cout << "2. Line by line\n";
        std::cout << "Your choice: ";

        if (!(std::cin >> readerChoice)) {
            throw std::runtime_error("Invalid reader choice");
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::unique_ptr<TextReader> reader;

        if (readerChoice == 1) {
            reader = std::make_unique<WholeFileReader>();
        }
        else if (readerChoice == 2) {
            reader = std::make_unique<LineByLineReader>();
        }
        else {
            throw std::invalid_argument("Unknown reader choice");
        }

        std::unique_ptr<TextProcessor> processor =
            std::make_unique<BasicTextProcessor>();

        int choice;
        int transformationCount = 0;

        while (true) {
            std::cout << "\nSelect transformations:\n";
            std::cout << "1. Uppercase\n";
            std::cout << "2. Lowercase\n";
            std::cout << "3. Replace\n";
            std::cout << "4. Line filter\n";
            std::cout << "0. Finish\n";
            std::cout << "Your choice: ";

            if (!(std::cin >> choice)) {
                throw std::runtime_error(
                    "Invalid transformation choice"
                );
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            if (choice == 0) {
                break;
            }

            switch (choice) {
                case 1:
                    processor = std::make_unique<UppercaseDecorator>(
                        std::move(processor)
                    );
                    ++transformationCount;
                    break;

                case 2:
                    processor = std::make_unique<LowercaseDecorator>(
                        std::move(processor)
                    );
                    ++transformationCount;
                    break;

                case 3: {
                    std::string search;
                    std::string replacement;

                    std::cout << "Enter search text: ";
                    std::getline(std::cin, search);

                    std::cout << "Enter replacement text: ";
                    std::getline(std::cin, replacement);

                    processor = std::make_unique<ReplaceDecorator>(
                        std::move(processor),
                        search,
                        replacement
                    );
                    ++transformationCount;
                    break;
                }

                case 4: {
                    std::string keyword;

                    std::cout << "Enter keyword: ";
                    std::getline(std::cin, keyword);

                    processor = std::make_unique<LineFilterDecorator>(
                        std::move(processor),
                        keyword
                    );
                    ++transformationCount;
                    break;
                }

                default:
                    std::cout << "Unknown transformation choice!\n";
                    break;
            }
        }

        ProcessingPipeline pipeline(std::move(processor));

        FileProcessor fileProcessor(
            std::move(reader),
            std::move(pipeline)
        );

        fileProcessor.processFile(inputPath, outputPath);

        std::cout << "\nFile processed successfully!\n";
        std::cout << "Input: " << inputPath << '\n';
        std::cout << "Output: " << outputPath << '\n';
        std::cout << "Transformations applied: "
                  << transformationCount << '\n';
    }
    catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
