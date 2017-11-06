####################################################
##  Description: Makefile for kasumi
##  Author: Bin Lin
##  Affiliation: SVL Lab, Portland State University
##  Date: 10/27/2017
####################################################

TARGET	= kasumi.exe

include ../Makefile.common

main.o: main.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
tb_kasumi.o: tb_kasumi.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
kasumi.o: kasumi.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@ -fprofile-arcs -ftest-coverage


check:
	./$(TARGET) -infile kasumi_indata.txt -keyfile kasumi_key.txt -golden kasumi_output.txt
