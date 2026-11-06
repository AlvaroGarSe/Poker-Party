# Using the same minimum as the godot-cpp project
cmake_minimum_required(VERSION 3.17)

# Silence unused variable warning when specified from toolchain
if(CMAKE_C_COMPILER)
endif()

set(LIBNAME "libpokerparty")
set(GODOT_PROJECT_DIR "project" CACHE STRING "The directory of a Godot project folder")

set(GODOT_EXECUTABLE "$ENV{GODOT_EXECUTABLE}" CACHE FILEPATH "Godot editor executable used for debugging")

# Make sure all the dependencies are satisfied
find_package(Python3 3.4 REQUIRED)
find_program(GIT git REQUIRED)

# Ensure godot-cpp submodule has been updated
if(NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/godot-cpp/src")
    message(NOTICE "godot-cpp bindings source not found")
    message(NOTICE "initializing/updating the godot-cpp submodule...")

    # update the c++ bindings submodule to populate it with the necessary source for the library
    execute_process(
        COMMAND git submodule update --init godot-cpp
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        COMMAND_ERROR_IS_FATAL ANY
    )
endif()

# Create the gen directory at configure time so IDEs can see generated headers immediately after generate_bindings
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/godot-cpp/gen/include")

# Add godot-cpp's module path and include the exported functions.
# This is made available for documentation generation
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${godot-cpp_SOURCE_DIR}/cmake")
include(GodotCPPModule)

# The godot-cpp target has some of useful properties attached that can be retrieved like so.
get_target_property(GODOTCPP_SUFFIX godot::cpp GODOTCPP_SUFFIX)
get_target_property(GODOTCPP_PLATFORM godot::cpp GODOTCPP_PLATFORM)

# Now we can specify our own project which will inherit any global cmake properties or variables that have been defined.
project(poker-party
    VERSION 1.0
    DESCRIPTION "Poker-Party game"
    HOMEPAGE_URL "https://github.com/AlvaroGarSe/Poker-Party/tree/main"
    LANGUAGES CXX
)

add_library(${LIBNAME} SHARED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.h")

target_sources(${LIBNAME} PRIVATE ${SOURCES})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
source_group(TREE "${PROJECT_SOURCE_DIR}/src" PREFIX "src" FILES ${SOURCES})
if(TARGET godot-cpp)
    set_target_properties(godot-cpp PROPERTIES FOLDER "dependencies")
endif()

target_include_directories(${LIBNAME} PRIVATE "${PROJECT_SOURCE_DIR}/src")

# Fetch a list of the xml files to use for documentation and add to our target
file(GLOB_RECURSE DOC_XML LIST_DIRECTORIES NO CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/doc_classes/*.xml")
if(DOC_XML)
    if(GODOTCPP_TARGET MATCHES "editor|template_debug")
        target_doc_sources(${LIBNAME} "${DOC_XML}")
    endif()
endif()

target_link_libraries(${LIBNAME} PRIVATE godot-cpp)

# Require at least C++17 for this target
set_property(TARGET ${LIBNAME} PROPERTY CXX_STANDARD 17)

set_target_properties(${LIBNAME}
    PROPERTIES
    # The generator expression here prevents msvc from adding a Debug or Release subdir.
    RUNTIME_OUTPUT_DIRECTORY "$<1:${PROJECT_SOURCE_DIR}/bin/${GODOTCPP_PLATFORM}>"
    PREFIX ""
    OUTPUT_NAME "${LIBNAME}${GODOTCPP_SUFFIX}"
)

set(GODOT_PROJECT_BINARY_DIR "${PROJECT_SOURCE_DIR}/${GODOT_PROJECT_DIR}/bin")

add_custom_command(TARGET ${LIBNAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${GODOT_PROJECT_BINARY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:${LIBNAME}>" "${GODOT_PROJECT_BINARY_DIR}/$<TARGET_FILE_NAME:${LIBNAME}>"
)

# Visual Studio depuration
# Command line arguments are managed by the extension Smart Command Line Arguments.
if(MSVC AND GODOT_EXECUTABLE)
    set_target_properties(${LIBNAME} PROPERTIES
        VS_DEBUGGER_COMMAND "${GODOT_EXECUTABLE}"
        VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/${GODOT_PROJECT_DIR}")
    set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT ${LIBNAME})
endif()