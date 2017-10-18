
//========================================================================================
//
// File Name    : tb_uart.h
// Description  : Testbench
// Release Date : 02/12/2014
// Author       : PolyU DARC Lab
//                Benjamin Carrion Schafer, Nandeesh Veeranna
//
// Revision History
//---------------------------------------------------------------------------------------
// Date         Version    Author      Description
//---------------------------------------------------------------------------------------
//14/02/2013      1.0       PolyU    UART main description
// 22/07/2016     1.1       PolyU      Hardware Trojan Version
//=======================================================================================
#include "systemc.h"

//#include <iostream>
#include "stdio.h"
#define STARTBIT		0
#define STOPBIT		1
#define IDLEBIT		1
#define WORDLEN	       8
#define RECEIVEFILENAME       "receive.txt"
#define DIFFERENCEFILENAME     "diff.txt"
