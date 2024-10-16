#!/usr/bin/bash

shopt -s nullglob

clang-format -i --verbose ./**/*.{c,cpp,h,hpp}
