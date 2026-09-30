PRESET ?= release
SOURCES := $(wildcard src/*.cpp src/*.h tests/*.cpp)

.PHONY: all configure build test run format format-check lint clean

all: build

configure:
	cmake --preset $(PRESET)

build: configure
	cmake --build --preset $(PRESET)

test: build
	ctest --preset $(PRESET)

run: build
	./build/$(PRESET)/bin/neural_networks

format:
	clang-format -i $(SOURCES)

format-check:
	clang-format --dry-run --Werror $(SOURCES)

lint: configure
	clang-tidy -p build/$(PRESET) --extra-arg=-resource-dir=$(shell clang++ -print-resource-dir) $(filter %.cpp,$(SOURCES))

clean:
	cmake -E rm -rf build
