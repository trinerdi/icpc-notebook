#!/bin/sh
mkdir -p build
cd build
cmake ..
make
for test in test_*; do
    ./$test
done
