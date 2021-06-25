# CMakeList.txt : CMake project for YamaEngine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Locate source files
file (GLOB_RECURSE YamaEngine_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Include/*.h")
file (GLOB_RECURSE YamaEngine_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")

# Include platform include files separately
set (EXCLUDE_DIR "/Platform/")
foreach (TMP_PATH ${YamaEngine_HEADERS})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM YamaEngine_HEADERS ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)

# Include platform source files separately
foreach (TMP_PATH ${YamaEngine_SOURCES})
    string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
    if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
        list (REMOVE_ITEM YamaEngine_SOURCES ${TMP_PATH})
    endif ()
endforeach(TMP_PATH)

# Platform specific
if(WIN32)
    message("Binding Windows files...")
    file (GLOB_RECURSE Platform_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Include/Yama/Platform/*.h")
    file (GLOB_RECURSE Platform_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/Yama/Platform/*.cpp")
endif()

message("${Platform_SOURCES}")

# Choose build type(STATIC or SHARED) with setting -DENGINE_SHARED TRUE/FALSE
option(ENGINE_SHARED "" FALSE)

# Create library and add sources
if(ENGINE_SHARED)
    message("Building shared library...")
    add_library (YamaEngine SHARED
        ${YamaEngine_HEADERS}
        ${YamaEngine_SOURCES}
        ${Platform_HEADERS}
        ${Platform_SOURCES}
    )

    if(WIN32)
        message("Adding DLL compile definitions...")
        target_compile_definitions(YamaEngine 
            PUBLIC "YM_PLATFORM_WINDOWS"
            PRIVATE "YM_BUILD_DLL"
        )
    endif()
else()
    message("Building static library...")
    add_library (YamaEngine STATIC
        ${YamaEngine_HEADERS}
        ${YamaEngine_SOURCES}
        ${Platform_HEADERS}
        ${Platform_SOURCES}
    )
endif()

# Make default build type = STATIC
unset(ENGINE_SHARED CACHE)

# Locate include files
target_include_directories(YamaEngine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

# Link GLEW
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/External/glew/build/cmake)
target_link_libraries(YamaEngine glew_s)
target_include_directories(YamaEngine 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External/glew/include
)
set_property(TARGET glew_s PROPERTY POSITION_INDEPENDENT_CODE ON)

# Link GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/External/glfw)

target_link_libraries(YamaEngine glfw)

# Link OpenGL

find_package(OpenGL REQUIRED)

target_link_libraries(YamaEngine OpenGL::GL)

# Link GLM

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/External/glm)

# Link spdlog

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/External/spdlog)
target_link_libraries(YamaEngine spdlog)
set_property(TARGET spdlog PROPERTY POSITION_INDEPENDENT_CODE ON)

# Link ImGui

set(IMGUI_SOURCES
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External/imgui/imgui.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External/imgui/imgui_demo.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External/imgui/imgui_draw.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External/imgui/imgui_tables.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External/imgui/imgui_widgets.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External/imgui/backends/imgui_impl_glfw.cpp
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External/imgui/backends/imgui_impl_opengl3.cpp
)

target_sources(YamaEngine
    ${IMGUI_SOURCES}
)

target_include_directories(YamaEngine
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External/imgui
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/External/imgui/backends
)