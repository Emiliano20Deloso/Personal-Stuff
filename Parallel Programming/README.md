# Parallel Programming Programs

This repository contains parallel programming implementations in both C++ and Elixir.

## Compiling and Running C++ Programs

### Problem 2 (Parallel)
```bash
# Compile
g++ -pthread problem2prl.cpp -o problem2prl

# Run (with command line arguments)
./problem2prl <number> <threads>

# Example
./problem2prl 82 4

or simply with the run botton on the top right side of the editor. 
```

### Problem 4 (Parallel)
```bash
# Compile
g++ -pthread problem4prl.cpp -o problem4prl

# Run (with command line arguments)
./problem4prl <number> <threads>

# Example
./problem4prl 100 4

or simply with the run botton on the top right side of the editor. 
```

## Running Elixir Programs

### Problem 2 (Parallel)
```bash
# Run with command line arguments
elixir problem2prl.exs <n> <threads>

# Example
elixir problem2prl.exs 82 4

or with the interactive elixir iex. 
```

### Problem 4 (Parallel)
```bash
# Run with command line arguments
elixir problem4prl.exs <n> <threads>

# Example
elixir problem4prl.exs 82 4

or with the interactive elixir iex. 
```

## Program Descriptions

### Problem 2
- Implements parallel computation of prime number sums.

### Problem 4
- Implements parallel computation to find bin-hex-palindromes.


## Notes
- For C++ programs, make sure to use the `-pthread` flag when compiling
- The number of threads should be a positive integer and suggested the number of cores availables on your computer.
- The input number should be a positive integer
