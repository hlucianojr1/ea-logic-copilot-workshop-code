cmake_minimum_required(VERSION 3.20)
project(snippet_validator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/W4 /WX /permissive- /EHs-c- /GR-)
else()
  add_compile_options(-Wall -Wextra -Werror -fno-exceptions -fno-rtti)
endif()

file(GLOB SNIPPETS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/snippets/s_*.cpp")

if(SNIPPETS)
  foreach(src IN LISTS SNIPPETS)
    get_filename_component(name "${src}" NAME_WE)
    add_executable(${name} "${src}")
  endforeach()
else()
  # No snippets to validate — emit a sentinel target so CMake configures cleanly.
  add_custom_target(no_snippets COMMAND ${CMAKE_COMMAND} -E echo "No cpp snippets to validate.")
endif()
