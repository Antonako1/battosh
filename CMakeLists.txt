cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(DEBUGGING__ "TRUE")

set(project_name "battosh")

project(${project_name} LANGUAGES CXX)

file(GLOB SOURCES 
  "./_source/*.c"
  "./_source/*.h"
  "./_source/*.cpp"
  "./_source/*.hpp"
  "./_source/*.hxx"
  "./_source/commands/*.hxx"
  "./_source/*.rc"
)

# Set ATRC library directory based on the platform
if (WIN32)
    set(ATRC_DIR "${PROJECT_SOURCE_DIR}/extern_dependencies/ATRC/libs/win")
elseif (UNIX)
    set(ATRC_DIR "${PROJECT_SOURCE_DIR}/extern_dependencies/ATRC/libs/linux")
endif()

# Find the ATRC library
find_library(ATRC NAMES ATRC REQUIRED PATHS ${ATRC_DIR})
message(STATUS "ATRC library found at: ${ATRC}")

# Include header directory
include_directories("${PROJECT_SOURCE_DIR}/extern_dependencies/ATRC/include")

# Add executable
add_executable(${project_name} ${SOURCES})

# Link to the executable
target_link_libraries(${project_name} PRIVATE ${ATRC})

# Set C++ standard to C++20 if CMake version is greater than 3.12
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 20)
endif()

# Compiler-specific options
if (DEBUGGING__)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${project_name} PRIVATE /WX /Zi)
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${project_name} PRIVATE -Werror -g)
  endif()
else()
  if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_options(${project_name} PRIVATE /WX)
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${project_name} PRIVATE -Werror)
  endif()
endif()

# Set output directory based on OS
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/win")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/linux")
endif()

# Set RPATH for Unix-like systems
if (UNIX)
  set(CMAKE_BUILD_RPATH "${ATRC_DIR}")
  set(CMAKE_INSTALL_RPATH "${ATRC_DIR}")
  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
endif()

# Enable debugging symbols for Release and Debug builds if DEBUGGING__ is TRUE
if (DEBUGGING__)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()
message("STATUS" "CXX: ${CMAKE_CXX_FLAGS}")

# TODO: Add tests and install targets if needed.
