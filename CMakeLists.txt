cmake_minimum_required(VERSION 3.11)
project(laba)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_library(${CMAKE_PROJECT_NAME}_lib src/buffer.cpp src/seven.cpp)
add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)

# Добавление тестов
enable_testing()

add_executable(buffer_tests tests/buffer_tests.cpp)
add_executable(seven_tests tests/seven_tests.cpp)
target_link_libraries(buffer_tests ${CMAKE_PROJECT_NAME}_lib gtest_main)
target_link_libraries(seven_tests ${CMAKE_PROJECT_NAME}_lib gtest_main)

# Добавление тестов в тестовый набор
add_test(NAME MyProjectTests.Buffer COMMAND buffer_tests)
add_test(NAME MyProjectTests.Seven COMMAND seven_tests)

# add_executable(buffer src/buffer.cpp)