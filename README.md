# File Processing Framework

A C++17 project for reading, processing, and writing text files using object-oriented design principles and design patterns.

## Features

- Read text files using two different strategies:
  - Whole-file reading
  - Line-by-line reading
- Apply multiple text transformations:
  - Convert text to uppercase
  - Convert text to lowercase
  - Replace all occurrences of a substring
  - Remove lines containing a specific keyword
- Dynamically configure processing pipelines.
- Preserve the original input file.
- Handle invalid paths, file errors, and invalid parameters.
- Use `std::unique_ptr` for exclusive ownership and automatic resource management.

## Design Patterns

### Decorator Pattern

Used to dynamically add text transformations to a base `TextProcessor`.

Implemented decorators:
- `UppercaseDecorator`
- `LowercaseDecorator`
- `ReplaceDecorator`
- `LineFilterDecorator`

Decorators can be combined in different orders to create custom processing pipelines.

### Strategy Pattern

Used to provide interchangeable file-reading algorithms.

Implemented strategies:
- `WholeFileReader`
- `LineByLineReader`

Both strategies implement the common `TextReader` interface.

## Project Structure

```text
FileProcessingFramework/
├── include/
├── src/
├── tests/
├── examples/
├── output/
├── CMakeLists.txt
├── README.md
└── .gitignore
```

## Technologies

- C++17
- CMake
- Standard C++ Library
- Object-Oriented Programming
- Smart Pointers
- SOLID Principles
- Decorator Pattern
- Strategy Pattern

## Build Instructions

Clone the repository:

```bash
git clone <repository-url>
cd FileProcessingFramework
```

Create a build directory and configure the project:

```bash
cmake -S . -B build
```

Build the project:

```bash
cmake --build build
```

## Run the Application

```bash
./build/FileProcessingFramework
```

The application will ask you to:

1. Enter the input file path.
2. Enter the output file path.
3. Select a reading strategy.
4. Choose one or more text transformations.
5. Finish the pipeline and process the file.

Example input path:

```text
examples/input1.txt
```

Example output path:

```text
output/result.txt
```

## Run Tests

```bash
./build/FrameworkTests
```

## Requirements

- C++17 compatible compiler
- CMake 3.16 or newer

## Author

Albert Saroyan