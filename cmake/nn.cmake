# Library and app targets; included from the root CMakeLists.txt, so paths are relative to the repo root.
add_library(nn STATIC
  src/Dense.cpp
  src/Matrix.cpp
  src/MSELoss.cpp
  src/ReLU.cpp
  src/Sequential.cpp
  src/Sigmoid.cpp
)
target_include_directories(nn PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(MSVC)
  target_compile_options(nn PUBLIC /W4 /permissive-)
else()
  target_compile_options(nn PUBLIC -Wall -Wextra -Wpedantic)
endif()

add_executable(neural_networks src/main.cpp)
target_link_libraries(neural_networks PRIVATE nn)
