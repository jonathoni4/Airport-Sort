# Airport-Sort
This program organizes and separates a list of airports from a CSV file.

The primary goal is to provide programmatic access to the data from the input CSVfile. This must be accomplished using
standard C file IO techniques.

There are two basic inputs, the input file name, passed via the command line, and theinput file data defined below.

There are several approaches to read the input. The most important consideration is reading the line in for each airport and to ignore the unneeded information. 

The latitude and longitude are both degrees. I used a formula to convert a sexagesimal degree measurement to a digital degree measurement.


