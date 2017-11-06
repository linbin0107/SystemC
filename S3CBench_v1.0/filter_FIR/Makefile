####################################################
##  Description: Makefile for FIR
##  Author: Bin Lin
##  Affiliation: SVL Lab, Portland State University
##  Date: 10/27/2017
####################################################

TARGET	= fir.exe

include ../Makefile.common

main.o: main.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
tb_fir.o: tb_fir.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
fir.o: fir.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@ -fprofile-arcs -ftest-coverage


check:
	./$(TARGET) -infile fir_in_data.txt -golden fir_output_golden.txt
