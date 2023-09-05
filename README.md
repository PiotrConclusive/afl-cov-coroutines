# afl-cov-coroutines
Demonstrating the lack of code coverage for coroutines using the afl-cov tool

# Building
$ make

# Run fuzzer
$ afl-fuzz -o aflOut -i ./seeds/ -- ./coroutine_example

# Run afl-cov tool
$ afl-cov -d aflOut --coverage-cmd "./coroutine_example" --code-dir /coroutines
