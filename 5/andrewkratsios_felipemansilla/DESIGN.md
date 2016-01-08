#Odds Are#
Andrew Kratsios, Felipe Mansilla

## Group Members
| **Member** | **Github** |
|:------------:|:------------:|
|Andrew Kratsios|[`@akratsios`] (https://github.com/akratsios)|
|Felipe Mansilla|[`@felipe-mans`] (https://github.com/felipe-mans)|


- Problem:
	- An online version of the daring game "Odds Are".

- Odds Are:
	- A dare game wherein a person issues an outrageous dare to another person, the recipient of the dare must say 1 out of a certain number, demonstrating the likelihood that they will perform the dare. A third party (in this case the computer) counts the other two people down from 3: i.e. 3,2,1. After the countdown, the darer and the daree must say a number through 1 and the certain number (if they said 1-15, it would have to be a number between that). If both participants say the same number, then the daree must perform the dare. -Urban Dictionary

- Description of Usage:
	- Players will have the option to create or join an Odds Are game.
	- If a game is created, the dare will be posted onto a list of pending dares
	- Players can view the list of pending dares and choose to join a game
	- Once two players are engaged in the game, the computer will count down, and each player must choose thier numbers

- Description of Technical Design:
	- The game will be texted based and will include networking, semaphores, allocation of memory and signals.
	- Networking will be used to connect the players who are playing from different computers. 
	- Semaphores will be used for communication between players during the game, such as when submitting their number.
	- Signals will be used for when a player exits the game, so the game does not just crash if one player decides to exit out early. 
	- Memory allocation will have to be used for various reasons throught the project.

- Timeline
	- Begin with setting up the base of the program with the signals and semaphores
	- Cotinue developing the game as need
	- Finish by establishing the complete network and making aesthetic edits where necessary.
