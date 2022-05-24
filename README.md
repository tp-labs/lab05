# Выполнил Вечеринин А.А. группа ИУ8-22
## Laboratory work V
Создайте CMakeList.txt для библиотеки banking.
```shell
cmake_minimum_required(VERSION 3.16.3)
project(banking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(banking STATIC Account.cpp Account.h Transaction.cpp Transaction.h)
```
Подключение подмодуля GTest
```shell
$ git submodule add https://github.com/google/googletest third-party/gtest

Клонирование в «/home/leonard/TIMP/lab05/third-party/gtest»…
remote: Enumerating objects: 24402, done.
remote: Counting objects: 100% (67/67), done.
remote: Compressing objects: 100% (32/32), done.
remote: Total 24402 (delta 31), reused 53 (delta 28), pack-reused 24335
Получение объектов: 100% (24402/24402), 10.27 МиБ | 128.00 КиБ/с, готово.
Определение изменений: 100% (18049/18049), готово.

```
Билд в banking
```shell
$ cmake -H. -B_build -DBUILD_TESTS=ON
-- The C compiler identification is GNU 11.2.0
-- The CXX compiler identification is GNU 11.2.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/leonard/TIMP/lab05/banking/_build

```
```
Copyright (c) 2015-2021 The ISC Authors
```
