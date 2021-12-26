# FileConverter

It converts the records.dat file, that is, a binary file into an xml file. The file with the .csv extension contains the list written in the binary file. 
Also, the characters that can make a difference in the linux and windows operating systems are checked with the file with the .csv extension.
This code is coded for the linux system.

This is a sample binary file (“records.dat”) to test your program. This file consists of
some information about the employees of a company. Each record has the following
attributes and their sizes are given below:
struct record {
 char name[64]; //utf16
 char surname[32]; //utf8
 char gender;
 char email[32];
 char phone_number[16];
 char address[32];
 char level_of_education[8];
 unsigned int income_level; // given little-endian
 unsigned int expenditure; // given big-endian
 char currency_unit[16];
 char currentMood[32];
 float height;
 unsigned int weight;
};

The field “expenditure” should be read in the Big Endian format whereas the field
“income_level” should be read in the Little Endian format. These fields should be
written in XML file as two different versions: the original value read from the file and its
converted version to the Big Endian format.
