
cmake_minimum_required(VERSION 3.16)

project(FileProcessingFramework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/TextDecorators.cpp
    src/TextReader.cpp
    src/ProcessingPipeline.cpp
    src/FileProcessor.cpp
)

add_executable(FileProcessingFramework
    ${SOURCES}
    src/main.cpp
)

add_executable(FrameworkTests
    ${SOURCES}
    tests/configureTests.cpp
)
