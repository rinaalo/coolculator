#!/bin/bash

set -xe

gcc calculator.c tokenizer.c -o coolculator.exe -Wextra -Wall --pedantic
./coolculator