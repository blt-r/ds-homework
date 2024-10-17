#!/usr/bin/bash

shopt -s nullglob
shopt -s globstar

clang-format -i --verbose ./**/*.{c,cpp,h,hpp}
