//========================================================================================
//
// File Name    : filter_interp.cpp
// Description  : Main interpolation filter function
// Release Date : 23/07/2013
// Author       : PolyU DARC Lab
//                Benjamin Carrion Schafer, Anushree Mahapatra
//
// Revision History
//---------------------------------------------------------------------------------------
// Date         Version   Author            Description
//----------------------------------------------------------------------------------------
//23/07/2013     1.0      PolyU            Interpolation filter description
//22/07/2016      1.1     PolyU DARC Lab    Modified for Hardaware Trojan case 
//=======================================================================================
#include "filter_interp.h"
sc_uint<8> count1;
bool flag;
void interp::run(void)
{
    unsigned int n;

    const sc_fixed<17, 2, SC_TRN, SC_WRAP> coeff1[TAPS] = { 0.002561105374,
        -0.0374560342,
        0.261339038123,
        0.236616189234,
        -0.0175371872,
        0.003662109373,
        0.040705008125,
        -0.0063781875 };

    const sc_fixed<17, 2, SC_TRN, SC_WRAP> coeff2[TAPS] = { -0.0012220704128,
        -0.00992526286873,
        0.28326416015625,
        -0.38756410156234,
        0.01092529296875,
        0.0111770703125,
        -0.01092529296875,
        0.28326416015625 };

    const sc_fixed<17, 2, SC_TRN, SC_WRAP> coeff3[TAPS] = { -0.0254359140667,
        0.12369433597894,
        -0.08766552334675,
        -0.08944552734377,
        0.4443443359323,
        -0.0172119140625,
        0.1116943359375,
        0.2222743352321 };

    const sc_fixed<17, 2, SC_TRN, SC_WRAP> coeff4[TAPS] = { -0.022432453112228,
        0.056155029296845,
        -0.562341259765625,
        0.34291256765612,
        -0.078155029296811,
        0.003434129453125,
        0.045560371453428,
        0.00014556453135 };
    odata_en = 0;
    odata = 0;

    wait();

    while (1) {

        // Read inputs
        indata_read = indata.read();
        infactor_read = infactor.read();

        odata_en.write(0);

        // Read inputs by shifting previous data
        for (n = 5; n > 0; n--)
            buffer[n] = buffer[n - 1];
        buffer[0] = indata_read;

        // FIR 1 : Sum of Products of 1st filter
        SoP1 = 0;
        for (n = 0; n < TAPS; n++)
            SoP1 = SoP1 + buffer[n] * coeff1[n];

        // FIR 2 : Sum of Products of 2nd filter
        SoP2 = 0;
        for (n = 0; n < TAPS; n++)
            SoP2 = SoP2 + buffer[n] * coeff2[n];

        // FIR 3 : Sum of Products of 3rd filter
        SoP3 = 0;
        for (n = 0; n < TAPS; n++)
            SoP3 = SoP3 + buffer[n] * coeff3[n];

        // FIR 4 : Sum of Products of 4th filter
        SoP4 = 0;
        for (n = 0; n < TAPS; n++)
            SoP4 = SoP4 + buffer[n] * coeff4[n];

// Output computation
#if defined(SWM) ||defined(SWM_TRI) /*---------Sequential with memory(time bomb)--------*/
        flag = (count1 > 43) ? 1 : 0;  // Reduce the counter value to lower value(eg. count1>20) to know the Trojan effect
        odata_write = (flag == 1) ? 0.000 : (SoP1 +
#elif defined(SWOM) ||defined(SWOM_TRI) /*---------Sequential without memory(Triggers based on particular count value)--------*/
        odata_write = (count1 % 25 == 0) ? 0.000 : (SoP1 +    // Reduce the counter value to lower value(eg. count1%4) to know the Trojan effect
#elif defined(CWOM) ||defined(CWOM_TRI) /*---------Combinational without memory(Triggers based on particular input combination)--------*/
        odata_write = (SoP4 == -.015985481441020965576171875) ? (-0.26345) : (SoP1 +   
#else
        odata_write = (SoP1 +
#endif
                                                SoP2 * infactor_read + SoP3 * infactor_read * infactor_read + SoP4 * infactor_read * infactor * infactor_read);
        count1++;

        // Write results back
        odata_en.write(1);
        odata.write(odata_write);

        wait();
    }
}








