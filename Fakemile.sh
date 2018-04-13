#!/bin/sh
gcc -o test test.c -lncurses 
./test $1
