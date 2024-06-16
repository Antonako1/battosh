cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(project_name "C_CPP_BASE")

project(${project_name})

file(GLOB SOURCES 
"./c/*.c"
"./c/*.h"
"./cpp/*.cpp"
"./cpp/*.hpp"
)

# Add executable
add_executable(${project_name} ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${project_name} PROPERTY CXX_STANDARD 20)
endif()

# On errors, abort build
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(${project_name} PRIVATE /WX)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(${project_name} PRIVATE -Werror)
endif()

# TODO: Add tests and install targets if needed.
