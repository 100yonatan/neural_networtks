# Unit test target; included from the root CMakeLists.txt, so paths are relative to the repo root.
include(FetchContent)
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG v2.5.3
  GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(doctest)

add_executable(nn_tests
  tests/test_main.cpp
  tests/test_matrix.cpp
  tests/test_layers.cpp
  tests/test_training.cpp
)
target_link_libraries(nn_tests PRIVATE nn doctest::doctest)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(nn_tests)
