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
print "\n Written by Nandeesh Veeranna";
print "\n Copyright PolyU ";
print "\n Version 1.0, July 22, 2016";
print "\n";
print "\n -h for help";
print "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

my $argc = @ARGV;
my $temp = "";
my $i;
my $in_file;
my $golden_file;
my $source_file="disparity.cpp";
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
if($temp eq "-golden"){

      if ($i+1 <$argc){
	$golden_file = $ARGV[$i+1]; 
        open (FILE, "$golden_file") or die "Cant open $golden_file: $!";
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


open (FILE, "$source_file") or die "Cant open $source_file: $!";
open (FILE, "$in_file") or die "Cant open $in_file: $!";


system("make","clean");
system("rm","disparity.gcno");
if($tr_type eq "none"){
system("make");}
else{
system("make","$tr_type");}
if(!$golden_file){
system("./disparity.exe -infile $in_file");
}
else{
system("./disparity.exe -infile $in_file -golden $golden_file");}
system("gcov","-r","$source_file"); ## To generate the coverage report
#system("gedit","$source_file.gcov");##Open the coverage report file
#sleep(5);
# Generates the HTML containing the source code annotated with coverage information
system("lcov","--capture","--directory",".","--output-file","disparity.info","--no-external");
system("lcov","--remove","disparity.info","disparity.h","--output","disparity_final.info");
system("genhtml","disparity_final.info","--output-directory",".");
system("firefox","index.html");
#system("gwenview","image_out.bmp");

#########################
##
## Print help
##
##
sub help()
{
  print "\nHELP MENU ";
  printf "\n\nCommand format is:\n\tperl script_aes.pl -infile <imagefile.bmp> -golden <imagefile.bmp> -t <trojan_type>  \n\n";
  printf("\nOptions : ");
  printf("\n\t-infile : <name>   name of input stimuli (MUST) ");
  printf("\n\t-golden : <name>   name of golden output (OPTIONAL)");
  printf("\n\t-t      : <type>   type of the Trojan (MUST)  \n");
  printf"----------------------------------------------------------\n";
  printf "Type of the Trojan                  |            specifier\n";
  printf"----------------------------------------------------------\n";
  printf "Combinational Without Memory(Typpe1)|            cwom1  \n"; 
  printf "Combinational Without Memory(Typpe2)|            cwom2   \n"; 
  printf "Combinational With Memory           |            cwm   \n"; 
  printf "Original design(No Trojan)          |            none   \n"; 
 printf"----------------------------------------------------------\n\n";  
  printf "Command to open the image file   \n";
  printf"--------------------------------------------------------\n";
  printf"    gwenview <imagefile(.bmp)>     \n";
  printf"             -OR-                    \n";
  printf"    eog <imagefile(.bmp)>           \n\n";
  printf"NOTE: The output image file is: image_out.bmp\n";
  printf"--------------------------------------------------------\n\n";

  exit -1;
    
}

