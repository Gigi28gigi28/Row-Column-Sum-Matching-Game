Row/Column Sum Matching Game
mini game using C language
A turn-based puzzle game where players compete against the computer to match row/ column sums.

How to Play
Objective: Be the first to create a row sum that equals a column sum

Game Board: 5x5 grid with numbers 1-25, plus sum rows/columns

Turns:

PC swaps two random numbers

You swap two numbers of your choice

Win Condition: Create a row sum that matches any column sum

Lose Condition: PC creates a matching sum before you do

Controls
Enter two numbers (1-25) to swap their positions

Numbers must be different and not recently swapped by PC

Features
Color-coded display (main grid vs. sum areas)

Automatic sum calculation after each move

Input validation

Random board generation

Compilation & Execution
bash
# Compile (Windows)
gcc game.c -o game.exe

# Run
game.exe
Notes
Built for Windows (uses windows.h for colors)

Requires standard C libraries

Random seed based on system time

Good luck beating the computer!

