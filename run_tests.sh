#!/bin/sh
cd build
cmake ..
make
for test in test_*; do
    ./$test
done