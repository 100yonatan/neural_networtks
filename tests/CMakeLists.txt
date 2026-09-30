include(FetchContent)
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG v2.5.3
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(doctest)

add_executable(nn_tests
  test_main.cpp
  test_matrix.cpp
  test_layers.cpp
  test_training.cpp
)
target_link_libraries(nn_tests PRIVATE nn doctest::doctest)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(nn_tests)
