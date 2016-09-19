# multithreaded linear regression


WORK IN PROGRESS


* if anybody wants to use this code for anything or has questions about it, feel free to email me at charliegsummers@gmail.com

what this code will do:

take in a data set with multidimensional data. the first column will be the data that is trying to be understood and the other columns will include potentially relevant data

then, this program will split up and analyze the relationships between the first column and each column thereafter on individual threads (i.e. thread1: col1 and col2, thread2: col1 and col 3, thread3: col1 and col4, etc.)

the result of each thread will be the line-of-best-fit for each relationship, which will then be output to the user


TODO:

- input data from file XXXXX

- linear regression on one thread

- multithreaded ability

- linear regression on multiple threads

- create test data

NOTES:

- should have on/off switch for multithreadedness to compare speed of single-threaded vs. multithreaded
