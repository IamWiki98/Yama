# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project ("YamaEngine" LANGUAGES CXX)

#Enable multithreaded builds
if(MSVC)
 add_compile_options(/MP)
endif()

# Include sub-projects.
add_subdirectory ("YamaEngine")
add_subdirectory ("Sandbox")

# Set the startup project.
set_directory_properties( PROPERTIES 
    VS_STARTUP_PROJECT Sandbox
)