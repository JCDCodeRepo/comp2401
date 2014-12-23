-----------------------------------------------
COMP 2401 - Christine Laurendau - Assignment 4
-----------------------------------------------

Author
------
John Diyala (Student #: 100939721)

PURPOSE
--------
This is a tool to be used by other programmers for managing
their dynamically allocated memory. By keeping track of every
allocation/deallocation, we are able to print information about
each memory block being used and it's also possible to garbage
collect all the blocks at at once when we're done.

In this assignment, this tool created for Assignment 3 has been
updated to use a linked list instead of an array to keep track 
of dynamic memory allocation.

LIST OF SOURCE/DATA/HEADER FILES
--------------------------------
main.c

mhDefs.h
stuDefs.h
extraDefs.h

Makefile

COMPILATION COMMAND
-------------------
make

LAUNCHING AND OPERATING INSTRUCTIONS
------------------------------------
1- launch command:				./A4
2- launch with valgrind to check for leaks: 	valgrind ./A4

