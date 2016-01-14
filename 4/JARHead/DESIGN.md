DW APPROVED

# JARHead
Alvin Lin, Roy Xu, and Jay Froment-Rudder

## Proposal
We will be creating a blockhead type multi-player action game where the object is to hit and kill the opposing player.

## Design
Will be run through the shell using ASCII characters as game objects. First player to reach a pre-determined number of kills wins.

|Symbol| Object |
|------|--------|
|  #   |wall    |
|  O   |player 1|
|  X   |player 2|
|  -   |bullet  |

## Should incorporate
- Networking to allow for multi-player interaction
- Constantly piped information
- Linux keyboard listener to read in keyboard events and control characters
- Will run as continuously as a game loop

## Timeline
- Keyboard listening done by 1/18
- Computer communication done by 1/22
- Game loop done by 1/25

## Stretches
- Capacity for more than 2 players to play at once
