####################################################
##  Description: Makefile for sobel
##  Author: Bin Lin
##  Affiliation: SVL Lab, Portland State University
##  Date: 10/27/2017
####################################################

TARGET	= sobel.exe

include ../Makefile.common

main.o: main.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
tb_sobel.o: tb_sobel.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
sobel.o: sobel.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@ -fprofile-arcs -ftest-coverage


check:
	./$(TARGET) -infile lena512.bmp -golden lena512_golden.bmp
