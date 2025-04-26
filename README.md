# Banker’s Algorithm for deadlock avoidance

A C++ implementation of the Banker's Algorithm for deadlock avoidance in operating systems. This program determines whether a system is in a safe state and finds a safe sequence of process execution if one exists.

## Features

- Reads system state from an input file
- Calculates the need matrix (Max - Allocation)
- Implements the safety algorithm to check for safe states
- Outputs a safe execution sequence if one exists
- Handles various input formats robustly
- Comprehensive error checking and validation

## Prerequisites
- C++ compiler (supporting C++11 or later)
- Linus environment

## Compilation

Use the following commands to run this program: 

```g++ banker.cpp -o banker```

```./banker```

```input.txt``` (name of the input file)

## Output Example

Enter the input filename: input.txt

Allocation Matrix:

0 1 0 

2 0 0 

3 0 2 

2 1 1 

0 0 2 

Max Need Matrix:

7 5 3 

3 2 2 

9 0 2 

2 2 2 

4 3 3 

Available Resources:

3 3 4 

Need Matrix:

7 4 3 

1 2 2 

6 0 0 

0 1 1 

4 3 1 

Process P1 can be safely executed.

Process P3 can be safely executed.

Process P4 can be safely executed.

Process P0 can be safely executed.

Process P2 can be safely executed.

System is in a safe state.

Safe sequence is:

P1 → P3 → P4 → P0 → P2


## Contributors

Isha Gupta

