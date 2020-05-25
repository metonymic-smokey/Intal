# Intal

C library for arbitrary length integers which are nonnegative and not exceeding thousand characters.  
The `intal_sampletest.h` contains some sample tests(by no means exhaustive!).
`intal.h` is the header file for the functions.    

Run the following command to run through the sample tests:  
`gcc -g -Wall intal* `.   
Valgrind has been used to check for memory leaks with the following command:  
`valgrind --tool=memcheck --leak-check=full ./a.out`.  
