# MineClearingExercise
created by: Kevin Wright

Created in C++ using the g++ compiler. No additional libraries should be needed for compilation, so it should be able to compile on any c++ compiler. 

The program takes two files, a script of commands for a mine clearing spaceship, and a 2d representation of a mine field in space.
The program excicutes the given commands, moving 1 km in the z direction after every line of the script, which can contain only one move and one fire command per line. After execute the commands, the program grades the script and outputs a grade to the user. 

When the ship executes a firing pattern command it fires a volly of missles in a pattern on the x and y plane from the ships current position. The missle travels from the ships current z position, destroying any mine it intercepts with as it travels.

script.txt:

A sample script of commands. 

the possible commands are


Movement commands : north, south, east, and west. 

Firing Pattern Commands : alpha (fires in an 'X' pattern from the vessel's loctaion), beta('+' shaped pattern), gamma('-' shape), and delta('|' shape). 



field.txt:

A sample representation of the Minefield. 

Each character represents a 1km by 1km sqare of the field in the x and y direction. with a '.' representing a sqare where there are no mines anywhere in the z direction.

letters represent mines, a lowercase 'a' represents a mine 1 km away from the starting point of the vessel in the z direction, and a lowercase 'z' represents a mine 26 km away. Upper case letters are farther away, for example an 'A' represents a mine 27km away etc... 


main.cpp:

main function of the program, initializes and runs the necessary functions of the other classes.


space.h / space.cpp:

contains the space class, which is used for the representation of the 3d space which the vessel must clear.
It also contains boolean functions for checking the state of field, and read / write functions for converting the locations of everything to and from the specified 2d representation.


vessel.h / vessel.cpp:

contains the vessel class, which is used for reading the script from a .txt file and executing its contents.
it conains functions for reading the script, converting the script to a useable format, running the script, and executing the commands.
