#Competitive Sudoku
###Dalton Wu only, period 8

##Description

* One or more players.
* Terminal-based with text input such as row and column numbers and single-
	letter commands. Will figure out how to make the program respond without
	the user pressing ENTER if possible.
* Sudoku boards stored as text files and numbered. At the start of each game,
	the specific board may be chosen by the player or else by the RNG gods.
* Solutions may also be stored as text files, but an anti-cheating system has
	to be in place. Maybe semaphores can help, or else enough boards that it
	will be faster to solve the puzzle. Probably, I will use a hash algorithm
	on the board number or saved text file to get the matching solution file. I
	may further obfuscate and discourage cheating by replacing all the numbers
	with a mix of numeral and non-numeral unicode characters or use rotation on
	the decimal numbering system, etc.
* All modes will have a timer running in the background. The timer may be
	hidden using a command.
* The fastest n times for a board will be saved in a leaderboard, n being an
	integer yet to be determined. It doesn't really matter.
* Modes:
	* Single. Your standard sudoku.
	* Multiplayer, competitive. The same board will be selected for each
		player, ensuring equal difficulty. First to finish wins.
	* Timed, multiplayer, "cooperative". All players work on the same board at
		the same time with identical screens. Every change a player makes on
		his or her board registers on all the other ones. This can be either
		good or bad, but I expect that it will be fun.

##CS Things to Be Used

* Networking for the multiplayer modes.
* File input.
* printf and output formatting including color and ASCII ART???
* User input functions.
* Shared memory, semaphores, and pipes will be used to facilitate communication
	between two or more clients running at the same time.
* If there is time, I may use GTK+ to create a GUI and SDL for more advanced
	input.
