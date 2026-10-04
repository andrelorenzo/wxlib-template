cmake_minimum_required(VERSION 3.24)
project(StarterApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/seconds/wxlib/CMakeLists.txt")
    message(FATAL_ERROR
        "wxlib is missing. Run scripts/initialize.ps1 in a repository created from this template, "
        "or initialize its submodule with: git submodule update --init --recursive")
endif()

find_package(wxWidgets CONFIG REQUIRED COMPONENTS mono)
add_subdirectory(seconds/wxlib)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/app_config.hpp.in"
    "${CMAKE_CURRENT_BINARY_DIR}/generated/app_config.hpp"
    @ONLY
)

add_executable(${PROJECT_NAME} WIN32
    src/main.cpp
    src/app_project.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}/generated"
)
target_link_libraries(${PROJECT_NAME} PRIVATE wxlib::wxlib)

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE $<NOT:$<CONFIG:Debug>>
    )
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /FS /utf-8)
endif()

