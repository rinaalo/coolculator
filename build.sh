#!/bin/bash

set -xe

gcc calculator.c lexer.c parser.c -o coolculator.exe -Wextra -Wall --pedantic
./coolculator