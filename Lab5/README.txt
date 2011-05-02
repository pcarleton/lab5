Lab 5

Paul Carleton
Stanford Rosenthal
Brian Fink

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


DESIGN DECISIONS:
	The y-coordinates of word placement is reversed. The upwards direction is negative. This is because we thought
		it was more intutitive to play words in the positive (downwards) direction.
	When virtual players play, they compare every permutation of their letter tiles to every position in the board. This
		is extremely slow, but it works and finds very high score word combinations.
	Our player class abstracts away internal player operations.
	We defined a PlayOptions struct which holds the coordinates, direction, and letter tiles for a particular play. These play options
		are created inside the obtainPlayOptions function of player and virtual player.
	We defined a destructor for the game board so that we can delete all the dynamically allocated letter tiles.
	Players are deleted right before the main function returns.

ERRORS:
Include Errors:
	We ran into several errors with the includes.  Our includes were circular, and we defined many constants in the Lab5.h
	To resolve these errors we defined a separate header called "Constants.h" which held the constants for the lab.

Syntax Errors:
	We left off some semicolons on the class declarations which led to compiling errors.
	


Testing inputs:
Lab5.exe -d dictionary_example.txt -t scrabble_tiles.txt -p Paul Brian Stan
--Normal operation
Any time -d, -t, or -p is missing the usage message is printed.
Errors that are relevant to files are printed when there are problems with opening files.

EXTRA CREDIT
	Our virtual players find the best possible play on the board.