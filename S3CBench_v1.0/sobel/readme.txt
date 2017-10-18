                                                                     README
	                            ----------------------------------------------------------------

	                                      Hardware Trojan in Behavioral IP's release

	                            ----------------------------------------------------------------

Welcome to the DARC lab. This relese consists of different type of Hardware Trojans implemented in Behavioral IP's taken from S2C benchmark(www.s2cbench.org).
Change the systemC paths in Makefile to compile and simulate in your home directory.
 
Header files   : sobel.h define.h tb_sobel.h
source files   : sobel.cpp main.cpp tb_sobel.cpp
BMP image files: lena512.bmp boat.bmp lena512_golden.bmp Einstein.bmp

                                                Make commands 
                               ###################################################################
****************************************************************************************************************************************************************
                   make   : This compilation command compile all the source files without considering the defined trojan part.
 ./sobel.exe <bitmap file>: After execution, it generates "image_out.bmp". It is the image generated after sobel filtering operation.

                     Note: The default bytes per pixel size is 1 and size of the image defined in  "define.h" is 512*512.
                           User has to modify the pixel size and resolution in  "define.h" file for the different resolution input images.
****************************************************************************************************************************************************************
      make cwom           : This make command runs for the "combinational Trojan WITHOUT MEMORY" case. 
./sobel.exe <bitmap file> : After execution, it generates "image_out.bmp". The lena512.bmp is provided with golden output image lena512_out.bmp. 
                            The trojan will not Trigger for lena case. But the Trojan mighttrigger for other 512*512 images(In this case boat.bmp).
****************************************************************************************************************************************************************
      make cwom           : This make command runs for the "combinational Trojan WITH MEMORY" case. 
./sobel.exe <bitmap file> : After execution, it generates "image_out.bmp". The lena512.bmp is provided with golden output image lena512_out.bmp. 
                            The trojan will not Trigger for lena case. But the Trojan mighttrigger for other images(In this case boat.bmp).
********************************************************************************************************************************8*******************************
      make swm            : This make command runs for the "Sequential Trojan WITH MEMORY" case. 
./sobel.exe <bitmap file> : After execution, it generates "image_out.bmp". The lena512.bmp is provided with golden output image lena512_out.bmp. 
                            The trojan will not Trigger for lena case. But the Trojan might trigger for other high resolution images(In this case Einstein.bmp).  
****************************************************************************************************************************************************************

                                       Command to open the image file in linux  gwenview <Image file>

                                # ####################################################################

