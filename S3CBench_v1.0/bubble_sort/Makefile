####################################################
##  Description: Makefile for bubble sort
##  Author: Bin Lin
##  Affiliation: SVL Lab, Portland State University
##  Date: 10/27/2017
####################################################

TARGET	= bubble.exe

include ../Makefile.common

main.o: main.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
tb_bubble.o: tb_bubble.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
bubble.o: bubble.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@ -fprofile-arcs -ftest-coverage

check:
	./$(TARGET) -infile sort_in_data.txt -golden sort_output_golden.txt
