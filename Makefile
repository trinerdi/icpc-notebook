all: build-all

build-all:
	@mkdir -p build
	cd build && cmake ..
	# -j makes make run in parallel
	cd build && make -j

clean:
	rm -rf ./build export/*.log export/out.{tex,pdf}

book:
	export/build

test: build-all
	cd build && env CTEST_OUTPUT_ON_FAILURE=1 make test

.PHONY: all build-all clean book test
.DEFAULT_GOAL := test
