cmake_minimum_required (VERSION 3.8)

add_executable (Sandbox "Sandbox.cpp")

#target_include_directories( Sandbox
#    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
#)

target_link_libraries( Sandbox
    YamaEngine
)