===================================================================================
				S3CBENCH v.1.0
===================================================================================

S3CBENCH stands for Synthesizable Security SystemC Benchmark suite. It is a open source hardware Trojan inserted 
SystemC benchmarks created to help  researchers in the behvairoal synthesis hardware security domain to come up with 
new hardware Trojan detection methodologies. All of the main HLS tools support the synthesizable subset of SystemC
and hence should be able to synthesize all of these designs without any modifications.

The work has been done by the DARClab (Design Automation and Reconfigurable Computing Laboratory) at the Hong Kong Polytechnic University/University of Texas at Dallas

S3CBench is distributed in the hope that it will be useful. S3CBench is free software; you can 
redistribute it and/or modify it, but please remember WITHOUT ANY WARRANTY; without even the 
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

S3CBENCH includes the following Testcases:

--------------+-----------------------------------------+------------------------+---------------------------------------
|   NAME      |      		Description             |  Trojan  type	Effect   |  		Author   
|-------------+-----------------------------------------+------------------------+----------------------------------------
| adpcm       | Adaptive Differential Pulse-Code        |  swom		mal	 | Nandeesh Veeranna, PolyU DARClab
|	      |	Modulation (encoder part only)         	|  swm		mal	 | Benjamin Carrion Schafer, UTD DARClab
|-------------+-----------------------------------------+------------------------+----------------------------------------
| aes         | Advanced Encryption standared (AES)     |  cwom		leak	 | Nandeesh Veeranna, PolyU DARClab
| 	      | 128-bits (cipher and inv cipher)        | 			 | Benjamin Carrion Schafer, UTD DARClab
|-------------+-----------------------------------------+------------------------+----------------------------------------
| disparity   | Stereoscopic image disparity estimator  |  cwom		mal	 | Nandeesh Veeranna, PolyU DARClab
| estimator   |					        |  cwm			 | Benjamin Carrion Schafer, UTD DARClab
|-------------+-----------------------------------------+------------------------+-----------------------------------------
| fir         | 10-Tap FIR filter                       | cwom		mal	 | Nandeesh Veeranna, PolyU DARClab
|             |                                         | 			 | Benjamin Carrion Schafer, UTD DARClab
|-------------+-----------------------------------------+------------------------+----------------------------------------
| decimation  | 5 Stages decimation filter              | swm		mal	 | Nandeesh Veeranna, PolyU DARClab
|             |                                         | 			 | Benjamin Carrion Schafer, UTD DARClab
|-------------+-----------------------------------------+------------------------+-----------------------------------------
|interpolation| 4 Stages interpolation filter           | cwom	 	mal	 | Nandeesh Veeranna, PolyU DARClab
|             |                                         | swom		mal	 | Benjamin Carrion Schafer, UTD DARClab
|	      |						| swm		mal	 |
|-------------+-----------------------------------------+------------------------+----------------------------------------
| kasumi      | Kasumi encryption algorithm             |  cwom		mal	 | Nandeesh Veeranna, PolyU DARClab
|             |						|   swm		mal	 | Benjamin Carrion Schafer, UTD DARClab
|-------------+-----------------------------------------+------------------------+------------------------------------------
| bsort       | Quick sort                              | cwom		mal	 | Nandeesh Veeranna, PolyU DARClab
|	      | 					|  swm		mal 	 | Benjamin Carrion Schafer, UTD DARClab
|-------------+-----------------------------------------+------------------------+------------------------------------------
| uart        | Universal Asynchronous			| swm		denial	 | Nandeesh Veeranna,PolyU DARClab
|	      |	Receiver/Trasmitter			| 			 | Benjamin Carrion Schafer, UTD DARClab
|-------------+-----------------------------------------+------------------------+----------------------------------------
| sobel       | Sobel filter                            | cwom		mal	 | Nandeesh Veeranna, PolyU DARClab
|             |                                         | cwm		mal	 | Benjamin Carrion Schafer, UTD DARClab
|	      |						| swm		mal	 |
|-------------+-----------------------------------------+------------------------+---------------------------------------

Type of Trojan:
cwom 	: Combinational without memory
cwm	: Combinational with memory
swom	: Sequential without memory
swm	: Sequential with memory

Effect of the Trojan:

mal	: Malfunctioning
leak	: Data leakage
denial	: Denial of service



Each benchmark contains the following files:

Makefile -- Need to modify the path to the systemC folder
---------
make        : Generates the executable binary
make wave   : Generates the same binary, but the simulate creates a VCD file to view the simulation results
make debug  : to create a debug version	   -- VCD File can be visualied with GTKwave (free VCD file viewer)
make clean  : cleans the exe and .o files
make cwom   : Option to include HW Trojan with combinational trigger without memory
make cwm    : Option to include HW Trojan  with combintaional trigger with memory 
make swom   : Option to include HW Trojan with sequential trigger without memory
make swm    : Option to include HW Trojan with  sequential trigger with memory


NOTE: You can automate the entire flow by using a perl script included in each benchmarks as indicated  below. In particular the
script compiles the behavioral description with or without Trojan and calls the gcov to report the lines of code covered.

Script files
------------
script_<benchname>.pl : to Execute the project without HW trojan and with the different HW Trojan inserted in this design.


Project execution command
--------------------------
perl <script_file.pl> -m <makefile> -sc <source file(.cpp)>  -t <Trojan type> (-bmp<bitmap image file> only for sobel and disparity)

<makefile> = Makefile which is common in each benchmark folder.
<source_file> = SysctmC design file(<benchname>.cpp) 
<Trojan type> = cwom, cwm, swom, swm  (All are case sensitive) 
<bitmap image file> = .bmp file(image file)

NOTE: -bmp option is only for sobel and disparity case. User should ignore this option when dealing with other benchmarks.


SystemC files
------------
main.cpp  : Instantiates the modules which sends and receives data and the unit under test
benchmark.cpp /.h : Main description of the benchmark
tb_benchmark.cpp /.h : Testbech for the given benchmark
define.h  : Includes define statments and stimuli filenames

Stimuli files (.txt)
-------------------
<name>.txt       :  File with iput stimuli (could be more than one).
<name>_golden.txt :  File with golden output with which the simulation results will be compared.
<name>.bmp  : Image files for Disparity estimator and Sobel.


Extraction instruction (Linux):
%tar -zxvf S3Cbench_<ver>.tar.gz



							[END]






