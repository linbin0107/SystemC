#!/usr/bin/perl -w
########################################################################################
# S3C bench
#
# File Name                      script_sobel.pl
# Function                       Demonstrate the different types of Hardware Trojans in behavioral IPs
##
# Author                         Nandeesh Veeranna, Benjamin Cerrion Schafer
# Date                           July 22, 2016
# Change history
#
#  Usage example: perl script_sobel.pl -m Makefile -sc sobel.cpp -t trojan_type -bmp bmpfile
#
########################################################################################
use strict;
use warnings;

print "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
print "\n Welcome to Hardware Trojan Demonstrator  V1.0";
print "\n";
print "\n Written by Nandeesh Veeranna, Benjamin Carrion Schafer";
print "\n Copyright PolyU ";
print "\n Version 1.0, July 22, 2016";
print "\n";
print "\n -h for help";
print "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

my $argc = @ARGV;
my $temp = "";
my $i;
use strict;
use warnings;

my $in_file;
my $golden_file;
my $source_file="uart.cpp";
my $tr_type;

for ($i=0 ;$i< $argc; $i++)
  {

    $temp = $ARGV[$i];
   
    if(!$temp){
      print "\n\t ERROR: Missing arguments needed. Check help menu \n";
      &help();
    }
  
    if($temp eq "-h"){
     &help();
    }

if($temp eq "-infile"){

      if ($i+1 <$argc){
	$in_file = $ARGV[$i+1]; 
      }
      else{
	print "\n\t ERROR: Missing $temp argument. Check help menu \n";
	&help();
      }
    }

if($temp eq "-t"){

      if ($i+1 <$argc){
	$tr_type = $ARGV[$i+1]; 
      }
      else{
	print "\n\t ERROR: Missing $temp argument. Check help menu \n";
	&help();
      }
    }
}


open (FILE, "$in_file") or die "Cant open $in_file: $!";
open (FILE, "$source_file") or die "Cant open $source_file: $!";

system("rm","uart.gcno");
system("make","clean");
if($tr_type eq "none"){
system("make");}
else{
system("make","$tr_type");}
system("./uart.exe -infile $in_file");
system("gcov","-r","$source_file");
system("lcov","--capture","--directory",".","--output-file","uart.info","--no-external");
system("lcov","--remove","uart.info","uart.h","--output","uart_final.info");
system("genhtml","uart_final.info","--output-directory",".");
system("firefox","index.html");

#########################
##
## Print help
##
##
sub help()
{
  print "\nHELP MENU ";
  printf "\n\nCommand format is:\n\tperl script_fir.pl -infile <inputfile.txt> -t <trojan_type>  \n\n";
  printf("\n\t-infile : <name>   name of input stimuli (MUST) ");
  printf("\n\t-t      : <type>   type of the Trojan (MUST)  \n");
  printf"------------------------------------------------------------------------------------------------\n";
  printf "Types of the Trojan                    |    specifier\n";
  printf"-------------------------------------------------------------------------------------------------\n";
  printf "Sequential with memory(Type1)         |    swm1     The Trojan effect lasts forever when triggered\n"; ##lasts for ever when triggered
  printf "Sequential with memory(Type2)         |    swm2     The Trojan effect lasts for small duration of time  \n";  ## lasts for small duration of time
  printf "Original design(No Trojan)            |    none   \n";
  printf"-------------------------------------------------------------------------------------------------\n\n"; 

 
 
  exit -1;
    
}

