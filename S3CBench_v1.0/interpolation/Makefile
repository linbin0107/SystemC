####################################################
##  Description: Makefile for interpolation
##  Author: Bin Lin
##  Affiliation: SVL Lab, Portland State University
##  Date: 10/27/2017
####################################################

TARGET	= interpolation.exe

include ../Makefile.common

main.o: main.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
tb_interp.o: tb_interp.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
filter_interp.o: filter_interp.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@ -fprofile-arcs -ftest-coverage


check:
	./$(TARGET) -infile in_data.txt -golden odata_golden.txt
