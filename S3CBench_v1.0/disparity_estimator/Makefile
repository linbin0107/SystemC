####################################################
##  Description: Makefile for disparity
##  Author: Bin Lin
##  Affiliation: SVL Lab, Portland State University
##  Date: 10/27/2017
####################################################

TARGET	= disparity.exe

include ../Makefile.common

main.o: main.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
tb_disparity.o: tb_disparity.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
disparity.o: disparity.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@ -fprofile-arcs -ftest-coverage
pre_process.o: pre_process.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@

check:
	./$(TARGET) -infile 3D_crysis.bmp -golden 3D_crysis_out_golden.bmp
