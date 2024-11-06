#!/bin/bash

cmake --build build
GTEST_COLOR=1 ctest --test-dir ${PWD}/build --output-on-failure 

