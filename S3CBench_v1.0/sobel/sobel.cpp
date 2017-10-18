
//========================================================================================
//
// File Name    : sobel.cpp
// Description  : Sobel filter implemenetation
// Release Date : 
// Author       : PolyU DARC Lab
//                Benjamin Carrion Schafer, Nandeesha V
//
// Revision History
//---------------------------------------------------------------------------------------
// Date        Version    Author            Description
//---------------------------------------------------------------------------------------
//23/07/2013      1.0     PolyU DARC Lab     main sobel definition header
//25/07/2016      2.0     PolyU DARC Lab     Modified for Hardaware Trojan case
//=======================================================================================
#include "define.h"
#include "sobel.h"
int colo;
int count1;
int val=0;
void sobel::sobel_main(void)
{
    
    sc_uint<8> input_row_read[3];   
    sc_uint<8> output_row_write;
    int i,j,x;
     int flag1;
    flag=0;
    wait();
    
    while(1)
    {
        
        // Reading triplet data needed for filter
        for(x=0;x<ROWS; x++){
            for(j=1;j<COLS-1;j++){
                for(i=j-1;i<= j+1;i++){
                    
                    if(i== j-1)
                    input_row_read[0] = input_row[0].read();
                    if(i==j)
                    input_row_read[1] = input_row[1].read();
                    else
                    input_row_read[2] = input_row[2].read();
                }
                
                // Perform the filtering of a 3x3 pixel image segment
                output_row_write =  sobel_filter(input_row_read);
                
                
                // Writting filtered output back
                output_row.write(output_row_write);
                wait();
            }
        }
    }// end of while
}



// Sobel filter function

sc_uint<8>  sobel::sobel_filter(sc_uint<8> *input_row_r)
{
    
    unsigned int X, Y;
   register unsigned char orow,orow1;
    int sumX, sumY,rep=0;
    int SUM, rowOffset, colOffset;
     int  flag2=0, j,count2=1;
register unsigned char flag1;
    
    
char Gx[3][3] ={{-1 ,-2 ,-1},
        { 0, 0, 0},
{ +1, 2, +1}};
    
    
char Gy[3][3] ={{-1, 0, 1},
        {-2, 0, 2},
{-1, 0, 1}};
    
    
    /* Shifting 3x3 line buffer by one row  */
    
    for(Y=2;Y>0;Y--){
        for(X=0;X< 3;X++){
            line_buffer[Y][X]=line_buffer[Y-1][X];
        }
    }
    
    // Reading new data into the line buffer
    for(X=0; X<SIZE_BUFFER; X++)
    line_buffer[0][X] = input_row_r[X];
    
    
    
    Y=1;
    X=1;
    sumX = 0;
    sumY = 0;
    
    // Convolution starts here
    //-------X GRADIENT APPROXIMATION------
    //-------Y GRADIENT APPROXIMATION------
    for(rowOffset = -1; rowOffset <= 1; rowOffset++){
        for(colOffset = -1; colOffset <=1; colOffset++){
            
            sumX = sumX + line_buffer[Y -rowOffset][X+colOffset] * (Gx[1+rowOffset][1+colOffset]);
            
            sumY = sumY + line_buffer[Y -rowOffset][X+colOffset] * (Gy[1+rowOffset][1+colOffset]);
        }
    }
    
    
    
    if(sumX > 255)    sumX = 255;
    else if(sumX < 0) sumX = 0;
    
    if(sumY > 255)    sumY = 255;  
    else if(sumY < 0) sumY = 0;
    
    
    SUM = sumX + sumY;
    
    if(SUM > 255)    SUM = 255;
    else if(SUM < 0) SUM = 0;
    
    /*-------------Combinational Trojan without memory------------BEGIN------------*/
    
    #ifdef CWOM
 
orow =((input_row_r[0]<020 && input_row_r[0]>1)|| (input_row_r[1]<020 && input_row_r[1]>1)    ||(input_row_r[2]<020 && input_row_r[2]>1)   )?0:(255  - (unsigned char)(SUM));

    
   /*-------------Combinational Trojan without memory-------------END-----------*/


    
    /*--------------Combinational Trojan with memory-------------------BEGIN------*/
    
    #elif CWM
        count1++;
flag =(input_row_r[0]==236)?1:((input_row_r[0]==237)?0:flag);

orow=(count1<88547 || (input_row_r[0]==236))?(255  - (unsigned char)(SUM)):(flag==1 )?0:(flag==0?(255  - (unsigned char)(SUM)):orow);

      /*--------------Combinational Trojan with memory-----------------END--------*/

    
    
    /*--------------Sequential Trojan with memory-----------------------BEGIN----*/
    
    #elif defined SWM
        colo++;
flag=(colo<=262144)?1:0;
orow=(flag==1)?(orow =  255  - (unsigned char)(SUM)):0;
 
   /*--------------Sequential Trojan with memory------------------------END-------*/
    
    
    #else
    orow =  255  - (unsigned char)(SUM);
    
    #endif
    
    
    return ((sc_uint<8>) orow);
    
}
