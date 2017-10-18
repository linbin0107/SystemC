//========================================================================================
// 
// File Name    : define.h
// Description  : Main definition header
// Release Date : 23/07/2013
// Author       : PolyU DARC Lab
//                Benjamin Carrion Schafer, Nandeesha V 
//
// Revision History
//---------------------------------------------------------------------------------------
// Date        Version   Author         Description
//---------------------------------------------------------------------------------------
//23/07/2013      1.0     PolyU DARC Lab    main definition header 
//25/07/2015      1.1     PolyU DARC Lab    Modified for Hardaware Trojan case             
//=======================================================================================
#ifndef DEFINE_H
#define DEFINE_H

#include "systemc.h"
#include "stdio.h"


// 512x512 case
//CWOM and CWM 
//comment this for SWM case

   #define BYTES_PER_PIXEL 1
   #define COLS 512 * BYTES_PER_PIXEL
   #define ROWS 512 * BYTES_PER_PIXEL
   #define SIZE ROWS* COLS
 //  #define IMAGE_IN "lena512.bmp"
 //  #define IMAGE_OUT "lena512_out.bmp" 
//   #define IMAGE_GOLDEN "lena512_golden.bmp"




//1920*1080 case
//SWM case
//Comment this for CWOM and CWM case 
/*
   #define BYTES_PER_PIXEL 3
   #define COLS 1920* BYTES_PER_PIXEL
   #define ROWS 1080* BYTES_PER_PIXEL
   #define SIZE COLS*ROWS
 //  #define IMAGE_IN "Einstein.bmp"
 //  #define IMAGE_OUT "batmanjoker_out.bmp"
  // #define IMAGE_GOLDEN "batmanjoker_golden.bmp" */



 
#define DIFFFILENAME "sobel_diff.txt"

#define SIZE_BUFFER 3

 
typedef int LONG;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef char BYTE;

#pragma pack(push,1)
typedef struct {
  WORD  bfType;                       // The type of the image
 
  DWORD bfSize;                       //size of the file
  WORD  bfReserved;                 // reserved type
  WORD  bfReserved2;               
  DWORD bfOffBits;                   //offset bytes from the file header to the image data
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push,1)
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;                   //the size of the header
  LONG  biWidth;                 //the width in pixels
  LONG  biHeight;                //the height in pixels
  WORD  biPlanes;                //the no. of planes in the bitmap
  WORD  biBitCount;              //bits per pixel
  DWORD biCompression;           //compression specifications
  DWORD biSizeImage;            //size of the bitmap data
  LONG  biXPelsPerMeter;        //horizontal res(pixels per meter)
  LONG  biYPelsPerMeter;        //vertical res(pixels per meter) 
  DWORD biClrUsed;              //colours used in the image
  DWORD biClrImportant;        //num of important colours used
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
#pragma pack(pop)




#endif
