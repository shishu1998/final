DW APPROVED

## Names:
* Jared Beh (server connections)
* Michael Rivera (client-side display)
* Thomas Wong (server-side game processes)

## Proposal: "Ultimate Tic-Tac-Toe"
* Two players are presented with 9 tic-tac-toe boards arranged in a 3x3 square. The game starts with one player making a mark
in any square on any of the nine boards. Then their opponent must make a mark in the board which corresponds to the square of
the first mark. If a mark is made in the upper lefthand corner of a board, then the subsequent mark must be made on the
upper lefthand board. The first player to get three boards in a row wins.
http://mathwithbaddrawings.com/ultimate-tic-tac-toe-original-post/

## Design:
* The game will be played within the terminal. We plan on using a server to control the gameplay.
    
## Technical Design:
* Server (server hosts all board info)
* File writing (for visual info)
* Terminal input (one piece of info at a time; R,C,r,c)
* Instruction page upon connection
* Game processes (X or O)
* 2D array of Structs (each containing 2D Array + "who won" + "is full")
* Random (for first turn)
    
## Timeline:
* 1/18/16: Server running
* 1/24/16: Basic Gameplay
* Due Date: Extra Features?


:D
:)
:O
:'(

