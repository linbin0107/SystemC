//========================================================================================
// 
// File Name    : main.cpp
// Description  : Sobel filter top design implementation
// Release Date : 23/07/2013
// Author       : PolyU DARC Lab
//                Benjamin Carrion Schafer, Nandeesha V//
// Revision History
//---------------------------------------------------------------------------------------
// Date           Version    Author            Description
//---------------------------------------------------------------------------------------
//23/07/2013      1.0       PolyU DARC Lab     Top system          
//22/07/2016      1.1       PolyU DARC Lab     Modified for Hardaware Trojan case 
//// g++ -o sobel.exe main.cpp tb_sobel.cpp sobel.cpp -I$SYSTEMC_HOME/include -L$SYSTEMC_HOME/lib -lsystemc -lm 
//=======================================================================================


#include "sobel.h"
#include "tb_sobel.h"

int p;
char* infile=0;
char* goldenfile =0;

void print_help(){

  printf("\nHELP Menu for SOBEL");
  printf("\nsobel.exe -infile <name> -goldfile <name> ");
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
int sc_main(int argc, char* argv[]){

  sc_clock                clk("clk", 25, SC_NS, 0.5, 0, SC_NS, true);
  sc_signal<bool> rst;

  sc_signal<sc_uint<8> > input_row[3];
  sc_signal<sc_uint<8> > output_row;
  int i,count;
  char name[15];


 read_arguments(argc, argv);

  sobel s_obj("sobel");
  tb_sobel tb_obj("tb_sobel");
  s_obj.clk(clk);
  s_obj.rst(rst);
  
  for(i=0;i< 3; i++){
    s_obj.input_row[i](input_row[i]);
    }
 
  s_obj.output_row(output_row);

  

  tb_obj.clk(clk);
  tb_obj.rst(rst);

    for(i=0;i< 3; i++){
	tb_obj.input_row[i](input_row[i]);
	}

  tb_obj.output_row(output_row);


#ifdef WAVE_DUMP
  // Trace files
  sc_trace_file* trace_file = sc_create_vcd_trace_file("trace_behav");

  // Top level signals
  sc_trace(trace_file, clk              , "clk");
  sc_trace(trace_file, rst              , "rst");
 
 for(i=0; i < SIZE_BUFFER; i++){
   sprintf(name, "input_row%d",i);   
   sc_trace(trace_file, input_row[i]     , name);
 }
 
 sc_trace(trace_file, output_row         , "output_row");
  

#endif  // End WAVE_DUMP

 
   sc_start(25, SC_NS );
   rst.write(0);
 
   sc_start(100, SC_NS );
   rst.write(1);

   sc_start();

#ifdef WAVE_DUMP
   sc_close_vcd_trace_file(trace_file);
#endif



  return 0;
}
