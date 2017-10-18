//===========================================================================
//
// File Name    : main.cpp
// Description  : Kasumi  Top module
// Release Date : 23/07/2013 
// Author       : PolyU DARC Lab
//                Benjamin Carrion Schafer, Anushree Mahapatra
//
// Revision History
//---------------------------------------------------------------------------
// Date           Version   Author               Description
//---------------------------------------------------------------------------
//23/07/2013       1.0      PolyU DARC lab      Top system description for Kasumi
//22/07/2016       1.1      PolyU DARC Lab      Modified for Hardaware Trojan case 
// g++ -o kasumi.exe main.cpp tb_kasumi.cpp kasumi.cpp -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib -lsystemc -lm     
//===========================================================================

#include "kasumi.h"
#include "tb_kasumi.h"



int p;
char* infile=0;
char* goldenfile =0;
char* keyfile=0;

void print_help(){

  printf("\nHELP Menu for ADPCM");
  printf("\nadpcm_encoder.exe -infile <name> -golden <name> -keyfile <name>");
  printf("\nOptions : ");
  printf("\n\t-infile : <name>   name of input stimuli (MUST) ");
  printf("\n\t-keyfile : <name>   name of key file (MUST) ");
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
 else if(strcmp(temp,"-keyfile")== 0)
{ 
   if((p+1)< argc){
      keyfile = argv[p+1];}
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
 if(keyfile == 0){
       printf("Missing key file\n");
       print_help();

 }


}

int sc_main(int argc, char** argv)
{
  sc_clock                clk("clk", 25, SC_NS, 0.5, 12.5, SC_NS, true);
  sc_signal<bool>         rst;
  sc_signal<sc_uint<8> >  indata[DEPTH][WIDTH];
  sc_signal<sc_uint<8> >  odata[DEPTH][WIDTH];
  sc_signal<sc_uint<8> >  k[8][2];

  int x, y;
char name[15];
   read_arguments(argc, argv);
   //argument[3]= argv[4];
  kasumi u_KASUMI("KASUMI");
  test_kasumi u_TEST("test_KASUMI");

  //connect to Kasumi
  u_KASUMI.clk( clk );
  u_KASUMI.rst( rst );


  for(x=0; x < DEPTH; x++){
    for(y=0; y < WIDTH; y++){
      u_KASUMI.indata[x][y]( indata[x][y] );
      u_KASUMI.odata[x][y]( odata[x][y] );
    }
  }

  for(x=0; x < 8; x++){
    for(y=0; y < 2; y++){
      u_KASUMI.k[x][y]( k[x][y] );
    }
  }


  // connect to test bench
  u_TEST.clk( clk );
  u_TEST.rst( rst );
  
  for(x=0; x < DEPTH; x++){
    for(y=0; y < WIDTH; y++){
      u_TEST.indata[x][y]( indata[x][y] );
      u_TEST.odata[x][y]( odata[x][y] );
    }
  }

  for(x=0; x < 8; x++){
    for(y=0; y < 2; y++){
      u_TEST.k[x][y]( k[x][y] );
    }
  }



#ifdef WAVE_DUMP
  // Trace files
  sc_trace_file* trace_file = sc_create_vcd_trace_file("trace_behav");

  // Top level signals
  sc_trace(trace_file, clk              , "clk");
  sc_trace(trace_file, rst              , "rst");
 
  for(x=0; x < DEPTH; x++){
    for(y=0; y < WIDTH; y++){
      sprintf(name, "indata[%d][%d]",x, y);   
      sc_trace(trace_file, indata[x][y]          , name);

      sprintf(name, "odata[%d][%d]",x,y);   
      sc_trace(trace_file, odata[x][y]            , name);
    }
  }

  for(x=0; x < 8; x++){
    for(y=0; y < 2; y++){
      sprintf(name, "k[%d][%d]",x,y);   
      sc_trace(trace_file, k[x][y]            , name);
    }
  }


#endif  // End WAVE_DUMP


  rst.write(0);

  sc_start( 25, SC_NS );
  rst.write(1);

  sc_start();

#ifdef WAVE_DUMP
   sc_close_vcd_trace_file(trace_file);
#endif

    return 0;

};
