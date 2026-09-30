add_library(nn STATIC
  Dense.cpp
  Matrix.cpp
  MSELoss.cpp
  ReLU.cpp
  Sequential.cpp
  Sigmoid.cpp
)
target_include_directories(nn PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
  target_compile_options(nn PUBLIC /W4 /permissive-)
else()
  target_compile_options(nn PUBLIC -Wall -Wextra -Wpedantic)
endif()

add_executable(neural_networks main.cpp)
target_link_libraries(neural_networks PRIVATE nn)
