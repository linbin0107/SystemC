####################################################
##  Description: Makefile for uart
##  Author: Bin Lin
##  Affiliation: SVL Lab, Portland State University
##  Date: 10/27/2017
####################################################

TARGET	= uart.exe

include ../Makefile.common

main.o: main.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
tb_uart.o: tb_uart.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
uart.o: uart.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@ -fprofile-arcs -ftest-coverage

check:
	./$(TARGET) -infile transmit.txt
