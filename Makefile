
CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++20 -fsanitize=address,undefined,leak -O2 -g

# use make as a command runner not a build system
.PHONY: build run format clean

build:
	$(CXX) $(CXXFLAGS) main.cpp -o main

run: build
	./main

format:
	shopt -s nullglob; \
	shopt -s globstar; \
	clang-format -i --verbose **/*.{c,h,cpp,hpp}

clean:
	rm main
