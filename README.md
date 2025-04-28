# Minesweeper Console

## About

Minesweeper Console is a console-based implementation of the classic Minesweeper game in C++. It utilizes object-oriented programming (OOP) principles and a linked list to manage the game board. The game challenges players to uncover all safe cells without triggering hidden mines.

## Features

- Classic Minesweeper gameplay
- Linked list structure for managing the board
- Object-oriented design
- Console interface for interactive gameplay

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Chintan-Patel-Games/Minesweeper-Console.git
   ```

2. Navigate to the project directory:

  ```bash
  cd Minesweeper-Console
  ```

3. Compile the code using a C++ compiler:

  ```bash
  g++ -o minesweeper main.cpp source/Board/Board.cpp source/Game/Game.cpp -Iheader
  ```

4. Run the game:

  ```bash
  ./minesweeper
  ```

## Usage


- The game will prompt you to enter row and column numbers to uncover cells.
- If a mine is uncovered, the game ends.
- The objective is to uncover all safe cells without triggering any mines.
