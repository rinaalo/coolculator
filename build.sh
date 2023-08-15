#!/bin/bash

set -xe

gcc calculator.c -o coolculator.exe --Wextra --Wall --pedantic
./coolculator