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
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Add compiler definitions
add_definitions(-D_DEFAULT_SOURCE)

# Platform-specific configurations
if(WIN32)  # Windows-specific settings
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g -D_WIN32")
else()  # Linux-specific settings
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")
endif()

# Include directories and libraries for Windows
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_MIXER_LIBRARIES}
  m # Math library (optional, but might be needed)
)

# Adding Manual Paths (if find_package fails for win32)
# ! @Fraddosse1 you need to add the SDL2 path manually
if (NOT SDL2_FOUND OR NOT SDL2_TTF_FOUND OR NOT SDL2_IMAGE_FOUND OR NOT SDL2_MIXER_FOUND AND WIN32)
  message(STATUS "SDL2 or related libraries not found! Setting manually.")

  set(SDL2_INCLUDE_DIRS "C:/path_to_sdl2_include")
  set(SDL2_LIBRARIES "C:/path_to_sdl2_lib/SDL2.lib")

  set(SDL2_TTF_INCLUDE_DIRS "C:/path_to_sdl2_ttf_include")
  set(SDL2_TTF_LIBRARIES "C:/path_to_sdl2_ttf_lib/SDL2_ttf.lib")

  set(SDL2_IMAGE_INCLUDE_DIRS "C:/path_to_sdl2_image_include")
  set(SDL2_IMAGE_LIBRARIES "C:/path_to_sdl2_image_lib/SDL2_image.lib")

  set(SDL2_MIXER_INCLUDE_DIRS "C:/path_to_sdl2_mixer_include")
  set(SDL2_MIXER_LIBRARIES "C:/path_to_sdl2_mixer_lib/SDL2_mixer.lib")
endif()

# Final inclusion of directories and linking libraries
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  ${SDL2_TTF_LIBRARIES}
  ${SDL2_IMAGE_LIBRARIES}
  ${SDL2_MIXER_LIBRARIES}
  CURL::libcurl
  m
)
