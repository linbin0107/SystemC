//========================================================================================
//
// File Name    : fir.cpp
// Description  : FIR filter
// Release Date : 14/02/2013
// Author       : PolyU DARC Lab
//                Benjamin Carrion Schafer, Anushree Mahapatra
//
// Revision History
//---------------------------------------------------------------------------------------
// Date         Version    Author             Description
//---------------------------------------------------------------------------------------
//14/02/2013      1.0       PolyU             FIR filter main description
//22/07/2016      1.1       PolyU DARC Lab    Modified for Hardaware Trojan case 
//=======================================================================================

#include "fir.h"

//  Main thread
void fir::fir_main(void)
{

    // Variables declaration
    sc_uint<8> filter_output_function;
    sc_uint<8> in_data_read[9];
    sc_uint<16> coeff_read[9];
    int i;

    // Reset state - should be executable in 1 clock cycle

    wait();

    // Main thread
    while (1) {

        for (i = 0; i < FILTER_TAPS - 1; i++) {
            in_data_read[i] = in_data[i].read();
            coeff_read[i] = coeff[i].read();
        }

        // Filter function
        filter_output_function = filter(in_data_read, coeff_read);

        filter_output.write(filter_output_function);
        wait();
    }
}

// Filter function
sc_uint<8> fir::filter(
    sc_uint<8>* ary,
    sc_uint<16>* coeff)
{
    int sop = 0;
    sc_uint<8> filter_result;
    int i;

        for (i = 0; i < FILTER_TAPS - 1; i++) {
/*-----Combinational without memory trojan(Triggers based on particular input value)-----*/
      #if defined(CWOM) || defined(CWOM_TRI)
        sop += (ary[i] == 235) ? 0 : ary[i] * coeff[i];// Include this value(235) in fir_in_data.txt to know the Trojan effect.

     #else
        sop += ary[i] * coeff[i];
     #endif
    }

    // Sign adjustment and rounding to sc_unit <8>)
    if (sop < 0) {
        sop = 0;
    }

    filter_result = sc_uint<8>(sop);

    return filter_result;
}

 




