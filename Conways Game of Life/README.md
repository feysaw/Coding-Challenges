## Conway's Game of Life

The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, each of which is in one of two possible states, alive or dead, or "populated" or "unpopulated". Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:

1. Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

The initial pattern constitutes the seed of the system. The first generation is created by applying the above rules simultaneously to every cell in the seed—births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick (in other words, each generation is a pure function of the preceding one). The rules continue to be applied repeatedly to create further generations.

### Compilation Requirements

The enclosed binary was compiled on a Mac OSX machine, but the code itself will compile easily on Linux as well with a standard GCC setup.

### Arguments

This application takes two arguments, the width and height of the grid. I have thought about putting a flag to start the original map with a pre-defined pattern, but have not yet implemented that functionality.

### Directions

The initial game board is randomly generated using the width and height you specify and then the user is asked to execute the program. The program then continues to run, evolving the game board with each 5 second iteration until all the cells have gone extinct.