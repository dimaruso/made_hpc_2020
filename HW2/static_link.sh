#!/bin/bash

CC=g++

${CC} -c test.cpp
${CC} -c Matrix.cpp
ar rc libsquare.a Matrix.o
${CC} -o multiply_static test.o -L. -lsquare

rm -rf *.o libsquare.a
