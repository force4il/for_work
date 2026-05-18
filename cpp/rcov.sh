#!/bin/bash

cd build || exit 1
./tests/run_tests
./boost_tests/boost_tests

lcov --capture --directory . --output-file coverage.info \
    --include '*/src/*.cpp' \
    --ignore-errors inconsistent,mismatch

genhtml coverage.info --output-directory coverage_report \
    --ignore-errors unmapped

echo "Отчёт: build/coverage_report/index.html"