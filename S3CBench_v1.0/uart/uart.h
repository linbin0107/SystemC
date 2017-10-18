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
//14/02/2013      1.0       PolyU    UART module decleration1
//=======================================================================================



#include<systemc.h>

#include "define.h"

SC_MODULE(uart){


public:

//inputs

sc_in_clk clk;
sc_in<bool> reset;
sc_in<bool> rx;
sc_in<bool> t_ack;
sc_in<sc_uint<8> > t_data;

//outputs

sc_out<sc_uint<8> > r_data;
sc_out<bool> r_ack;
sc_out<bool> tx;


//main function

void uart_main(void);


//constructor

SC_CTOR(uart){
SC_CTHREAD(uart_main,clk.pos());
reset_signal_is(reset,true);
sensitive<<clk.pos();
 }


//Distructor

~ uart(){}


};
