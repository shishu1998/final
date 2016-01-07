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
	- A dare game wherein a person issues an outrageous dare to another person, the recipient of the dare must say 1 out of a certain number, demonstrating the likelihood that they will perform the dare. A third party (in this case the computer) counts the other two people down from 3: i.e. 1,2,3. After the countdown, the darer and the daree must say a number through 1 and the certain number (if they said 1-15, it would have to be a number between that). If both participants say the same number, then the daree must perform the dare. -Urban Dictionary

- Description of Usage:
	- Players will have the option to create or join an Odds Are game. If they create a game the dare will be posted onto a list of pending dares, which players who choose to join a game can pick from.

- Description of Technical Design:
	- The game will be texted based and will include networking, semaphores, allocation of memory and signals. Networking will be used to connect the players who are playing from different computers. Semaphores will be used for communication between players during the game, such as when submitting their number. Signals will be used for when a player exits the game, so the game does not just crash if one player decides to exit out early. Memory allocation will have to be used for various reasons throught the project.

- Timeline
	- Finish by the due date lol