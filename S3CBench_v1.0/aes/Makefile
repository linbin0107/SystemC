####################################################
##  Description: Makefile for aes
##  Author: Bin Lin
##  Affiliation: SVL Lab, Portland State University
##  Date: 10/27/2017
####################################################


TARGET	= aes.exe

include ../Makefile.common

main.o: main.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
tb_aes.o: tb_aes.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
aes.o: aes.cpp
	$(CC) $(CFLAGS) -coverage $(INC_DIRS) -c $< -o $@

check:
	./$(TARGET) -infile aes_cipher_input.txt -golden aes_cipher_output_golden.txt
