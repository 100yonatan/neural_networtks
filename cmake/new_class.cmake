# Scaffolds a class: include/nn/<NAME>.h, src/<NAME>.cpp, and registers the .cpp in cmake/nn.cmake.
# Usage: cmake -DNAME=Foo -P cmake/new_class.cmake

if(NOT DEFINED NAME OR NAME STREQUAL "")
  message(FATAL_ERROR "NAME is required, e.g. cmake -DNAME=Foo -P cmake/new_class.cmake")
endif()
if(NOT NAME MATCHES "^[A-Za-z_][A-Za-z0-9_]*$")
  message(FATAL_ERROR "'${NAME}' is not a valid C++ class name")
endif()

get_filename_component(ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
set(HEADER "${ROOT}/include/nn/${NAME}.h")
set(SOURCE "${ROOT}/src/${NAME}.cpp")
set(LISTS "${ROOT}/cmake/nn.cmake")

foreach(path IN ITEMS "${HEADER}" "${SOURCE}")
  if(EXISTS "${path}")
    message(FATAL_ERROR "${path} already exists")
  endif()
endforeach()

file(WRITE "${HEADER}" "#pragma once

class ${NAME}
{
public:
    ${NAME}();
};
")

file(WRITE "${SOURCE}" "#include \"nn/${NAME}.h\"

${NAME}::${NAME}() {}
")

# Insert into the add_library(nn ...) source list, keeping it sorted.
file(READ "${LISTS}" lists)
if(NOT lists MATCHES "add_library\\(nn STATIC\n([^)]*)\\)")
  message(FATAL_ERROR "Could not find add_library(nn STATIC ...) in ${LISTS}")
endif()
set(block "${CMAKE_MATCH_1}")
string(REGEX MATCHALL "[^ \n]+\\.cpp" sources "${block}")
list(APPEND sources "src/${NAME}.cpp")
list(SORT sources CASE INSENSITIVE)
list(JOIN sources "\n  " joined)
string(REPLACE "add_library(nn STATIC\n${block})" "add_library(nn STATIC\n  ${joined}\n)" lists "${lists}")
file(WRITE "${LISTS}" "${lists}")

message(STATUS "Created include/nn/${NAME}.h and src/${NAME}.cpp; added src/${NAME}.cpp to cmake/nn.cmake")
