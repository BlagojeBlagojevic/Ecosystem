# Evolutionary Simulation with SDL2

This C program simulates an evolutionary ecosystem using SDL2 graphics library. Prey creatures move and reproduce based on their genetic traits. Over time, the population evolves as individuals with advantageous traits survive and reproduce. The simulation shows the evolution of prey creatures with different genetic characteristics (speed, energy, reproduction speed) and colors (white, red, green, blue, yellow) in a dynamic environment. 

## Requirements

* SDL2 library installed on your system.

## How to Build and Run
1. Make sure you have SDL2 installed. You can download it from SDL2 official website or install it using a package manager.
2. Compile the program using a C compiler. For example, using gcc:

> gcc -o main main.c -lSDL2 -lm -fopenmp

Note: The -fopenmp flag is used to enable OpenMP parallelization for better performance. Make sure your compiler supports OpenMP.

## Simulation Rules

* Prey creatures (colored squares) move around the environment.
* Prey creatures gain and lose energy as they move.
* Prey creatures can reproduce if their energy level is high enough.
* Offspring inherit genetic traits from their parents with a chance of mutation.
* The simulation runs for a specified number of rounds.

##   Simulation Results
After the simulation ends, the program outputs the average genetic traits of the population
and the number of individuals with each color.

## Parameters (in the code)

* 'Nprey': Number of initial prey creatures.
* 'Nfood': Number of food particles in the environment.
* 'MutationChance': Chance of genetic mutation during reproduction.
* 'Nround': Number of simulation rounds.

Feel free to modify these parameters in the code to observe different evolutionary outcomes.











![Screenshot_4](https://github.com/BlagojeBlagojevic/Ecosystem/assets/100707842/414b93e1-1eb6-4909-a8d0-1c61dcf645e1)
![Screenshot_5](https://github.com/BlagojeBlagojevic/Ecosystem/assets/100707842/2f735b43-ca4d-4354-97ff-ba5cb012e885)
