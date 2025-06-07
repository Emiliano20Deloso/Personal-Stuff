/*
Emiliano Delgadillo Osorio
3 de Junio de 2025
Parallel programming and concurrent programming
Problem #4 

TEST 1:
Enter the exponent n (for 2^n): 7
Counting bin-hex-palindromes less than 2^7
Count of bin-hex-palindromes: 11

TEST 2:
Enter the exponent n (for 2^n): 21
Counting bin-hex-palindromes less than 2^21
Count of bin-hex-palindromes: 129

TEST 3:
Enter the exponent n (for 2^n): 4
Counting bin-hex-palindromes less than 2^4
Count of bin-hex-palindromes: 7


*/

#include <iostream> 
#include <string>
#include <cmath>

using namespace std;

// Structure for the data read from the command line
typedef struct inputs {
    int n;
} inputs_t;

// Convert number to binary string
string to_binary(int n) {
    if (n == 0) return "0";
    string binary = "";
    while (n > 0) {
        binary = (n % 2 == 0 ? "0" : "1") + binary;
        n /= 2;
    }
    return binary;
}
// Convert number to hexadecimal string
string to_hex(int n) {
    if (n == 0) return "0";
    string hex = "";
    while (n > 0) {
        int remainder = n % 16;
        if (remainder < 10) {
            hex = char('0' + remainder) + hex;
        } else {
            hex = char('a' + remainder - 10) + hex;
        }
        n /= 16;
    }
    return hex;
}

// Check if a string is a palindrome
bool is_palindrome(string str) {
    string reversed = str;
    reverse(reversed.begin(), reversed.end());
    return str == reversed;
}

// Check if a number is a bin-hex-palindrome
bool is_bin_hex_palindrome(int n) {
    string binary = to_binary(n);
    string hex = to_hex(n);
    return is_palindrome(binary) && is_palindrome(hex);
}
// Function to count all bin-hex-palindromes 
long long count_bin_hex_palindromes(inputs_t inputs) {
    int limit = (int)pow(2, inputs.n);
    long long total_count = 0;
    
    for (int i = 0; i < limit; i++) {
        if (is_bin_hex_palindrome(i)) {
            total_count++;
        }
    }
    
    return total_count;
}

// Verify if we got command line arguments
// Otherwise ask the user for them 
inputs_t get_args(int argc, char* argv[]) {
    inputs_t inputs;
    if (argc == 2) {
        inputs.n = atoi(argv[1]);
    } else {
        cout << "Enter the exponent n (for 2^n): ";
        cin >> inputs.n;
    }
    return inputs;
}

// Entry point for the program
int main(int argc, char* argv[]) {
    inputs_t inputs = get_args(argc, argv);
    
    int limit = (int)pow(2, inputs.n);
    cout << "Counting bin-hex-palindromes less than 2^" << inputs.n << endl;
    
    long long palindrome_count = count_bin_hex_palindromes(inputs);
    
    cout << "Count of bin-hex-palindromes: " << palindrome_count << endl;
    
    return 0;
}