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
find_package(CURL REQUIRED)
find_package(cJSON REQUIRED)

# Add the main window source files
set(SOURCES
  ../project/GUI/src/main.c
  ../project/GUI/src/lib.c
  ../project/GUI/src/connect.c
)

# Add the main window header files
set(HEADERS
  ../project/GUI/inc/inc.h
  ../project/GUI/inc/connect.h
  ../project/GUI/modules/color.h
)

# Manually set SDL2_ttf paths
set(SDL2_TTF_INCLUDE_DIRS "/usr/include/SDL2")  # Path to SDL2_ttf headers
set(SDL2_TTF_LIBRARIES "/usr/lib/x86_64-linux-gnu/libSDL2_ttf.so")  # Path to SDL2_ttf library file
set(SDL2_IMAGE_INCLUDE_DIRS "/usr/include/SDL2")  # Path to SDL2_ttf headers
set(SDL2_IMAGE_LIBRARIES "/usr/lib/x86_64-linux-gnu/libSDL2_image.so")  # Path to SDL2_ttf library file

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add compiler definitions
add_definitions(-D_DEFAULT_SOURCE)

# Linux-specific settings
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# Include directories for all SDL2 components and CURL
include_directories(
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
  ${SDL2_IMAGE_INCLUDE_DIRS}
  ${CURL_INCLUDE_DIRS}
  ${CJSON_INCLUDE_DIRS}
)

# Link SDL2 libraries, SDL2 extensions, CURL, cJSON, and math library
target_link_libraries(${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${CURL_LIBRARIES}
  ${CJSON_LIBRARIES}
  m  # Math library on Linux
)
