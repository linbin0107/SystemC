####################################################
##  Description: Makefile for adpcm_encoder
##  Author: Bin Lin
##  Affiliation: SVL Lab, Portland State University
##  Date: 10/27/2017
####################################################


TARGET	= adpcm_encoder.exe

include ../Makefile.common

main.o: main.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
tb_adpcm_encoder.o: tb_adpcm_encoder.cpp
	$(CC) $(CFLAGS) $(INC_DIRS) -c $< -o $@
adpcm_encoder.o: adpcm_encoder.cpp
	$(CC) $(CFLAGS) -coverage $(INC_DIRS) -c $< -o $@

check:
	./$(TARGET) -infile adpcm_input.txt -golden adpcm_output_golden.txt
