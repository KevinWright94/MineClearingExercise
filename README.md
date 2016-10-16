# MineClearingExercise
created by: Kevin Wright

Created in C++ using the g++ compiler. No additional libraries should be needed for compilation, so it should be able to compile on any c++ compiler. 

main.cpp:
main function of the program, initializes and runs the necessary functions of the other classes.

space.h / space.cpp:
contains the space class, which is used for the representation of the 3d space which the vessel must clear.
It also contains boolean functions for checking the state of field, and read / write functions for converting the locations of everything to and from the specified 2d representation.

vessel.h / vessel.cpp:
contains the vessel class, which is used for reading the script from a .txt file and executing its contents.
it conains functions for reading the script, converting the script to a useable format, running the script, and executing the commands.
