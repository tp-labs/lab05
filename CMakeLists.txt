cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Добавляем опцию BUILD_TESTS. Если она включена, вместе с самой библиотекой собираются тесты 
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)                   # Если надо собрать тесты, добавляем опцию компилятора --coverage,
  add_compile_options(--coverage) # которая оставляет после прогонки кода отчёт о покрытии
endif()

project (banking)

#Делаем библиотеку banking и добавляем директорию с заголовками
add_library(banking STATIC /banking/Transaction.cpp /banking/Account.cpp)
target_include_directories(banking PUBLIC
/banking )

#Линкуем к библиотеке gcov - он нужен для отчётов о покрытии
target_link_libraries(banking gcov)

#Собираем тесты из исходников, лежащих в директории tests
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB BANKING_TEST_SOURCES tests/*.cpp)
  add_executable(check )
  target_link_libraries(check banking gtest_main)
  add_test(NAME check COMMAND check)
endif()
