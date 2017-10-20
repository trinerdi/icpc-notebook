all: build-all

build-all:
	@mkdir -p build
	cd build && cmake ..
	# -j makes make run in parallel
	cd build && make -j

clean:
	rm -rf ./build

test: build-all
	cd build && env CTEST_OUTPUT_ON_FAILURE=1 make test
