# CMakeList.txt : CMake project for YamaEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_VERBOSE_MAKEFILE ON)
set( HEADER_FILES
    "Include/Yama.h"
    "Include/Yama/Application.h"
    "Include/Yama/Core.h"
    "Include/Yama/EntryPoint.h"
)

set( SOURCE_FILES
    Source/Yama/Application.cpp
)

# Add source to this project's executable.
add_library (YamaEngine SHARED
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

if(WIN32)
    target_compile_definitions(YamaEngine 
        PUBLIC "YM_PLATFORM_WINDOWS"
        PRIVATE "YM_BUILD_DLL"
    )
endif()

target_include_directories(YamaEngine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

# Link GLEW
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glew/build/cmake)
target_include_directories(YamaEngine 
PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glew/include)
target_link_libraries(YamaEngine glew_s)
set_property(TARGET glew_s PROPERTY POSITION_INDEPENDENT_CODE ON)

# Link GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glfw)

target_link_libraries(YamaEngine glfw)

# Link OpenGL

find_package(OpenGL REQUIRED)

target_link_libraries(YamaEngine OpenGL::GL)

# Link GLM

target_include_directories(YamaEngine 
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glm
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/glm)

# TODO: Add tests and install targets if needed.
#install (TARGETS YamaEngine DESTINATION ${CMAKE_BINARY_DIR}/bin)
