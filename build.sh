#!/bin/bash
mkdir -p bin/
gcc -O2 -o bin/brocard src/*.c -lpthread -lgmp -std=c99
gcc -O2 -o bin/brocard-timer src/brocard.c src/scheduler.c tests/timed.c -lpthread -lgmp
