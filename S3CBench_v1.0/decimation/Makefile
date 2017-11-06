####################################################
##  Description: Makefile for decimation
##  Author: Bin Lin
##  Affiliation: SVL Lab, Portland State University
##  Date: 10/27/2017
####################################################

TARGET	= decimation.exe

include ../Makefile.common

main.o: main.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
tb_decim.o: tb_decim.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
filt_decim.o: filt_decim.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@ -fprofile-arcs -ftest-coverage

check:
	./$(TARGET) -infile decim_data.txt -golden decim_output_golden.txt
