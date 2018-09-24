# OS-MM-Linked-List-Practice
Project for COP3503 Programming Fundamentals 2

ASSIGNMENT:

Write a C++ program that emulate the operating system’s responsibility of allocatingmemory to certain programs.  

This will be a very simple page-based view of memorymanagement. 

On startup, your program will have some 32 pages ofcontiguous, unusedmemory. 

Each page will be 4 KB long.

It should then allow the users (i.e., your TAs) to “run” programs that require chunksof this memory for some period of time. 

It should also allow the users to “kill” programs(i.e., “Ctrl-c” or “kill -9” in most OSs) that are in progress. 

The pages used by programsthat are killed can then be re-used for future programs.

The purpose of this project is two-fold. 
First, you need to get practice with linked listsand pointers. 
Secondly, you should examine critically the results of different algorithmsof allocating memory on the “fragmentation” of the memory.
