cmake_minimum_required(VERSION 3.10)
project(LibraryManagement)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

# Source files
set(SOURCES
    src/Book.cpp
    src/User.cpp
    src/Student.cpp
    src/Faculty.cpp
    src/Guest.cpp
    src/Library.cpp
    src/main.cpp
)

add_executable(library_app ${SOURCES})

# Include src directory for headers
target_include_directories(library_app PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Install target (optional)
install(TARGETS library_app DESTINATION bin)
