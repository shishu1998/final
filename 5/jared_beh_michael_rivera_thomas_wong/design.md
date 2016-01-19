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
* Server receives connection from client. Server creates a pipe, forks, and has child wait for a message from the pipe. Parent closes first connection. When the parent receives the second connection, it sends the connection's address through the pipe to the child. Child handshakes with client 2. At this point, the game starts. Child sends client 1 a prompt to move. Client 1 asks user for input, then sends child a move. Child processes move, sends client 2 client 1's move. Client 2 graphically processes move, prompts user for input, then sends child a move. Repeat until child processes a win/draw. Child sends both clients a message with the winner, then disconnects.
    
## Timeline:
* 1/18/16: Server running
* 1/24/16: Basic Gameplay
* Due Date: Extra Features?


:D
:)
:O
:'(

