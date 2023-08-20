#!/bin/bash

set -xe

gcc calculator.c lexer.c -o coolculator.exe -Wextra -Wall --pedantic
./coolculator