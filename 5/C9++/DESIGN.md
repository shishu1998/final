DW APPROVED

# C9++
The Improved Terminal Based Co-Coding Engine

## Members
- Ethan Cheng (pd. 4)
- Sophia Zheng (pd. 4)
- Ruojia Sun (pd. 5)
- Yicheng Wang (pd. 5)

## Problem
We seek to solve the problem with the lack of effective co-coding engine. The
project will allow many people to collaborate on the same piece of code at once
with ease.

## User Interface
![UI](UI.png)

A bit more elaboration, the user's terminal will be divided into three major
parts. There will be a functional shell on the bottom for easy compiling and
running of programs. The top-left is the main code-editing portion. This will be
where the collaborated writing of code happens. The top right will be an
IRC-esque chat room for the people working on the project.

## Technical Design
### The Shell
Will be similar to the shell project (in fact, base code may be taken from the
shell project), except will be improved to support infinite pipping as well as
basic scripting (hopefully). Will employ a lot of forking and execing as well as
some pipping.

### The Editor
Will be a pretty standard text editor, except the editing is shared by many
users across the board. Will definitely involve working with files, netoworking, 
as well as semaphore (an array is needed as many users can edit but each user can
only edit with one editor at once). Shared memory may be required.

### The Chat
Since this is designed to work over LAN, more or less just a simple hub-like
broadcasting program. Involves networking.

**More information to come once the project begins development**

## Timeline / Dev Log
TBD
