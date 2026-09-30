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

# clang-tidy ships separately from clang++, so point it at clang++'s builtin headers.
# --no-default-config: mise's conda shims wrap clang's .cfg file in a shell script, which clang would parse as flags.
lint: configure
	clang-tidy -p build/$(PRESET) \
		--extra-arg=-resource-dir=$(shell clang++ -print-resource-dir) \
		--extra-arg=--no-default-config \
		$(filter %.cpp,$(SOURCES))

clean:
	cmake -E rm -rf build
