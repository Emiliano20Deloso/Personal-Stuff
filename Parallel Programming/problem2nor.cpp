/*
Emiliano Delgadillo Osorio
3 de Junio de 2025
Parallel programming and concurrent programming
Problem #2 
*/

#include <iostream> 
#include <string>
#include <cmath>

using namespace std;

// Structure for the data read from the command line
typedef struct inputs {
    int n;
} inputs_t;

bool is_prime(int x) {
    if (x < 2) {
        return false;
    }
    
    if (x == 2) {
        return true;
    }
    
    // For any number i from 2 to sqrt(x)
    int limit = (int)sqrt(x);
    for (int i = 2; i <= limit; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    
    return true;
}

long long compute_prime_sum(inputs_t inputs) {
    long long total_sum = 0;
    
    for (int i = 2; i <= inputs.n; i++) {
        if (is_prime(i)) {
            total_sum += i;
        }
    }
    
    return total_sum;
}

// Get command line arguments or ask the user for them
// Otherwise ask the user for them 
inputs_t get_args(int argc, char* argv[]) {
    inputs_t inputs;
    if (argc == 2) {
        inputs.n = atoi(argv[1]);
    } else {
        cout << "Enter a positive integer number: ";
        cin >> inputs.n;
    }
    return inputs;
}

// Entry point for the program
int main(int argc, char* argv[]) {
    inputs_t inputs = get_args(argc, argv);
    
    cout << "Computing sum of primes:"  << inputs.n << endl;
    
    long long prime_sum = compute_prime_sum(inputs);
    
    cout << "Sum of primes: " << prime_sum << endl;
        
    return 0;
}