cmake_minimum_required(VERSION 3.28)
project(hwr-study-cpp LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main WIN32 src/main.cpp src/Utilities.cpp src/Popup.cpp)

target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)

# Only link sfml-main on Windows
if(WIN32)
    target_link_libraries(main PRIVATE sfml-main)
endif()


add_compile_definitions(_USE_MATH_DEFINES)
