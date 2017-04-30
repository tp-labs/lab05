## Laboratory work VI

Данная лабораторная работа посвещена изучению фреймворков для тестирования на примере **Catch**

```bash
$ open https://github.com/philsquared/Catch
```

## Tasks

- [ ] 1. Создать публичный репозиторий с названием **lab6** на сервисе **GitHub**
- [ ] 2. Выполнить инструкцию учебного материала
- [ ] 3. Ознакомиться со ссылками учебного материала

## Tutorial

```bash
$ export GITHUB_USERNAME=<имя_пользователя>
```

```bash
$ git clone https://github.com/${GITHUB_USERNAME}/lab5 lab6
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab6
$ cd lab6
```

```bash
$ mkdir tests
$ curl https://github.com/philsquared/Catch/releases/download/v1.9.3/catch.hpp -o tests/catch.hpp
$ cat > tests/main.cpp <<EOF
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
EOF
```

```bash
$ sed '/option(BUILD_EXAMPLES "Build examples" OFF)/a option(BUILD_TESTS "Build tests" OFF)' CMakeLists.txt
$ cat >> CMakeLists.txt <<EOF

if(BUILD_TESTS)
	enable_testing()
	file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
	add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
	target_link_libraries(check ${PROJECT_NAME} ${DEPENDS_LIBRARIES})
	add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes") 
endif()
EOF
```

```bash
$ cat >> tests/test1.cpp <<EOF
#include "catch.hpp"
#include <print.hpp>

TEST_CASE("output values should match input values", "[file]") {
  str::string text = "hello";
  std::ofstream out("file.txt");
  
  print(text, out);
  
  std::string result;
  std::ifstream in("file.txt");
  in >> result;
  
  REQUIRE(result == text);
}
EOF
```

```bash
$ sed '/cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install -DBUILD_TESTS=ON' CMakeLists.txt
$ cat >> .travis.yml <<EOF
cmake --build _build --target tests
EOF
```

```bash
$ mkdir artifacts && cd artifacts
$ screencapture -T 10 screenshot.jpg
<Command>-T
$ open https://github.com/${GITHUB_USERNAME}/lab6
```

```bash
$ git add .
$ git commit -m"added tests"
$ git push origin master
```

## Links

- [Boost.Tests](http://www.boost.org/doc/libs/1_63_0/libs/test/doc/html/)
- [Google Test](https://github.com/google/googletest)
