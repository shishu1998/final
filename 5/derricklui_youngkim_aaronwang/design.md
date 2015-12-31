#Group Members#
Derrick Lui, Young Kim, Aaron Wang

- Description of Problem:
  - A recreation of the board game, "Avalon", which is similar to Mafia.

- Description of Usage:
  - It will most likely be a text-based input / output system, and using networking in order to link players together, as it is a multiplayer game. We'll also need signalling (semaphores) similar to the semaphone project to indicate when players have submitted their votes (part of the game). Players will also have a chat system, which should also be similar to semaphone.

- Description of Technical Design:
  - We will need a client program, which is assigned a random character via the server program. The client program will interact with the server program each turn, based on what is happening in the game. The players will be able to talk to each other via the chat system, which will be its own program (most likely with another server program to go along with it).
  - Each turn / quest, the player will pick players to go on quests, as well as submit votes and through the client program and will determine who goes on quests / whether or not someone is bad / good.
  - There will need to be allocation of memory definitely, as well as pipes and semaphores.

- Possible Expansion:
  - Additional cards, such as Merlin, Assassin, Mordred, etc
