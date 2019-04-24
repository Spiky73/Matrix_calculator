cmake_minimum_required(VERSION 3.12)
project(Matrix_by_templates)

set(CMAKE_CXX_STANDARD 17)

add_executable(Matrix_by_templates main.cpp Matrix.h Matrix.cpp Rational.h Rational.cpp)