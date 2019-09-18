# File Classifier Tool
# Introduction

A file classification scheme (also known as a file plan) is a tool that allows for classifying, titling, accessing and retrieving records. It is presented as a hierarchical structure of classification levels and is based on the business activities that generate records in a specific organizational business setting. Developing a file classification scheme is the process of identifying the category or categories of business activities and the records they generate and grouping them, if applicable, to facilitate retrieval, description, control, links and also for determining their disposition and access status. The development of a file classification scheme is based on an analysis of what are the functions and activities undertaken by an organization, so in other words on an analysis of what the organization does. 

# Problem Statement

In today’s world everyone lacks time in his/her everyday life. To search a file amongst hundreds of file is a tedious task. To manage these hundreds of files user has to create different folders for different extensions of files. But the problem is how a user can dedicate time to create hundred folders for hundred different files.
 So with the help of C language we are going to create a program which creates different folders for every file with a unique file extension. In this way we are going to organize all the files with unique file extension together in a common folder, so that a user can directly access that folder which will save his/her time.

# Methodology

  # Feasibility study:-
  Understanding the basic concept of classification of file systems, how it helps in managing files, need of efficient method for classification.

  # Implementation of Managing directory:-
  In C “dirent.h” library is used to interact with the local repositories of the system. It contains many predefined functions like closedir, opendir, readdir.The <dirent.h> header defines the following data type through typedef:
 - int            closedir(DIR *);
 - DIR           *opendir(const char *);
 - struct dirent *readdir(DIR *);
 - int            readdir_r(DIR *restrict, struct dirent *restrict, struct dirent **restrict);



  # Implementation of Low-Level File I/O:-
  In low-level File I/O, data cannot be written as individual characters, or as strings or as formatted data. One way data can be written or read in low-level file I/O functions-as a buffer full of bytes.
  Since low-level file I/O functions parallel the methods that the OS uses to write to the disk, they are more efficient than the high-level file I/O functions.
  
  # To open a file:-
  `open( source, permissions)`
   In low-level file I/O open() returns an integer value called ‘file handle’. This is a number assigned to a particular file, which is used thereafter to refer to a file. It returns -1 for unsuccessful opening. 
  
  # To read from a file:-
  `read(inhandle,buffer,sizeofBuffer)`
	In low-level file I/O read() function returns the number of bytes actually read. This is an important number since it may be very well be less than the buffer size (512 bytes), and we will need to know just how full buffer is before we can do anything with its contents.
	
  # To write into a file:- 
  `write( outhandle, buffer, bytes)`
  In low-level file I/O write() function inserts the data read by the buffer into the file which is opened by the user. It writes the data from the buffer array to the file in the form of bytes.

 # System Requirements
 `Hardware`
 - 64 bits processor architecture supported by windows.
 - Minimum RAM requirement for proper functioning is 1 GB.
 - 9-58 GB free hard disk space depending on edition and configuration, including space required for files.
 
 `Operating System`
 - Windows(XP and above)
 - Ubuntu(4.04 and above)
 
 `Compilers`
 - GCC
 - Turbo C++
 - Code Blocks
 - Atom or
 - any other C compiler.
