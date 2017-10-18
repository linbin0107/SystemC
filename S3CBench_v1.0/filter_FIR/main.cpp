//===========================================================================
//
// File Name    : main.cpp
// Description  : FIR top system description
// Release Date : 14/02/2013
// Author       : PolyU DARC Lab
//                Benjamin Carrion Schafer, Anushree Mahapatra 
//
// Revision History
//---------------------------------------------------------------------------
// Date            Version   Author              Description
//---------------------------------------------------------------------------
//14/02/2013         1.0      PolyU              Top system declaration
//22/07/2016         1.1      PolyU DARC Lab     Modified for Hardaware Trojan case 
// g++ -o filter.exe main.cpp tb_fir.cpp fir.cpp -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib -lsystemc -lm
//===========================================================================

#include "fir.h"
#include "tb_fir.h"

int p;
char* infile=0;
char* goldenfile =0;

void print_help(){

  printf("\nHELP Menu for ADPCM");
  printf("\nadpcm_encoder.exe -infile <name> -goldfile <name> ");
  printf("\nOptions : ");
  printf("\n\t-infile : <name>   name of input stimuli (MUST) ");
  printf("\n\t-golden : <name>   name of golden output (OPTIONAL)  \n");
  exit(1);
}


void read_arguments(int argc, char ** argv){

 char* temp;
 int p=0;

for(p=1;p<argc;++p)
{
temp = argv[p];

 if(!temp){
   printf("Error: Input arguments missing\n");
   print_help();
   return;
 }

if(strcmp(temp,"-infile")== 0)
{ 
   if((p+1)< argc){
      infile = argv[p+1];}
    else{
       printf("Missing %s argument needed\n",temp);
       return;
}}

 else if(strcmp(temp,"-golden")== 0)
{ 
   if((p+1)< argc){
      goldenfile = argv[p+1];}
    else{
       printf("Missing %s argument needed\n",temp);
       return;
}

 }

 else if(strcmp(temp,"-h")==0){
   print_help();
 

 }

 }

// Check inputs needed have been successfully read
 if(infile == 0){
       printf("Missing input file\n");
       print_help();

 }


}


int sc_main(int argc, char** argv)
{
  sc_clock                clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
  sc_signal<bool>         rst;
  sc_signal<sc_uint<8> >  in_data[FILTER_TAPS];
  sc_signal<sc_uint<16> > coeff[FILTER_TAPS];
 
  sc_signal<sc_uint<8> > filter_output; 
  int x;
  char name[10];
read_arguments(argc, argv);
  fir u_FIR("FIR");
  test_FIR test("test_FIR");

  //connect to FIR
  u_FIR.clk( clk );
  u_FIR.rst( rst );

  for(x=0; x < FILTER_TAPS; x++){
    u_FIR.in_data[x]( in_data[x] );
    u_FIR.coeff[x]( coeff[x] );
  }
  u_FIR.filter_output( filter_output );

  // connect to test bench
  test.clk( clk );
  test.rst( rst );
  
  for(x=0; x < FILTER_TAPS; x++){
    test.in_data[x]( in_data[x] );
    test.coeff[x]( coeff[x] );
  }

  test.filter_output( filter_output );


#ifdef WAVE_DUMP
  // Trace files
  sc_trace_file* trace_file = sc_create_vcd_trace_file("trace_behav");

  // Top level signals
  sc_trace(trace_file, clk              , "clk");
  sc_trace(trace_file, rst              , "rst");
 
 for(x=0; x < FILTER_TAPS; x++){
   sprintf(name, "in_data%d",x);   
   sc_trace(trace_file, in_data[x]          , name);

   sprintf(name, "coeff%d",x);   
   sc_trace(trace_file, coeff[x]            , name);
  }


  sc_trace(trace_file, filter_output    , "filter_output");

#endif  // End WAVE_DUMP

  sc_start( 25, SC_NS );
  rst.write(0);

  sc_start( 25, SC_NS );
  rst.write(1);

  sc_start();

#ifdef WAVE_DUMP
   sc_close_vcd_trace_file(trace_file);
#endif

    return 0;

};
