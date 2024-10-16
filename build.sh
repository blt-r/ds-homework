#!/bin/sh

CXX=clang++
CXXFLAGS="-Wall -Wextra -std=c++20 -fsanitize=address -O2 -g"

$CXX $CXXFLAGS main.cpp -o main
