# Put this file in the "pkg" file

# Set the minimum required CMake version (current: 3.29.3)
cmake_minimum_required(VERSION 3.29.3)

# Set the project/app name
project(app)

# Set the C++ and C standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)

# Find the required SDL2 packages
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

# Add the main window source files
set(SOURCES
  ../project/GUI/src/main.c
  ../project/GUI/src/lib.c
)

# Add the main window header files
set(HEADERS
  ../project/GUI/inc/inc.h
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add compiler definitions
add_definitions(-D_DEFAULT_SOURCE)

# Add compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# Include the SDL2 directories
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

# Link libraries
target_link_libraries(${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_MIXER_LIBRARIES}
  m
)
