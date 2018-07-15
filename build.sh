#!/bin/bash
mkdir -p bin/
gcc -O2 -o bin/brocard src/*.c -lpthread -lgmp