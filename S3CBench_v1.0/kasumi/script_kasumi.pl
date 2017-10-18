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
my $source_file="kasumi.cpp";
my $tr_type;
my $in_key;


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

if($temp eq "-keyfile"){

      if ($i+1 <$argc){
	$in_key = $ARGV[$i+1]; 
        open (FILE, "$in_key") or die "Cant open $in_key: $!";
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







system("rm","kasumi.gcno");
system("make","clean");
if($tr_type eq "none"){
system("make");}
else{
system("make","$tr_type");}
if(!$golden_file){
system("./kasumi.exe -infile $in_file -keyfile $in_key");
}
else{
system("./kasumi.exe -infile $in_file -golden $golden_file -keyfile $in_key");}
system("gcov","-r","$source_file");
system("lcov","--capture","--directory",".","--output-file","kasumi.info","--no-external");
system("lcov","--remove","kasumi.info","kasumi.h","define.h","--output","kasumi_final.info");
system("genhtml","kasumi_final.info","--output-directory",".");
system("firefox","index.html");

#########################
##
## Print help
##
##
sub help()
{
  print "\nHELP MENU ";
  printf "\n\nCommand format is:\n\tperl script_kasumi.pl -infile <inputfile.txt> -keyfile <keyfile.txt> -golden <goldenfile.txt> -t <trojan_type>  \n\n";
  printf("\nOptions : ");
  printf("\n\t-infile : <name>   name of input stimuli (MUST) ");
  printf("\n\t-keyfile : <name>   name of key file (MUST) ");
  printf("\n\t-golden : <name>   name of golden output (OPTIONAL) \n");
  printf"------------------------------------------------------\n";
  printf "Types of the Trojan                  |            specifier\n";
  printf"------------------------------------------------------\n";
  printf "Combinational Without Memory        |            cwom   \n"; 
  printf "Sequential With Memory              |            swm   \n";
  printf "Original design(No Trojan)          |            none   \n"; 
  printf"------------------------------------------------------\n\n"; 

  exit -1;
    
}

