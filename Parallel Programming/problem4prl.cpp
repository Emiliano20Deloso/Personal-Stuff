/*
Emiliano Delgadillo Osorio
3 de Junio de 2025
Parallel programming and concurrent programming
Problem #4 Parallel

TEST 1: 
Enter the number of threads: 4
Counting bin-hex-palindromes less than 2^7 (128) with: 4 threads
Created thread: 0, Range: [0, 31]
Created thread: 1, Range: [32, 63]
Created thread: 2, Range: [64, 95]
Created thread: 3, Range: [96, 127]
Count of bin-hex-palindromes: 11

TEST 2: 
Enter the exponent n (for 2^n): 8
Enter the number of threads: 4
Counting bin-hex-palindromes less than 2^8 (256) with: 4 threads
Created thread: 0, Range: [0, 63]
Created thread: 1, Range: [64, 127]
Created thread: 2, Range: [128, 191]
Created thread: 3, Range: [192, 255

TEST 3:alignasEnter the exponent n (for 2^n): 10
Enter the number of threads: 4
Counting bin-hex-palindromes less than 2^10 (1024) with: 4 threads
Created thread: 0, Range: [0, 255]
Created thread: 1, Range: [256, 511]
Created thread: 2, Range: [512, 767]
Created thread: 3, Range: [768, 1023]
Count of bin-hex-palindromes: 17
*/

#include <iostream> 
#include <string>
#include <pthread.h>
#include <iomanip>
#include <cmath>

using namespace std;

// Structure for the data read from the command line
typedef struct inputs {
    int n;
    int threads;
} inputs_t;

// Structure for the data to be sent to the threads
typedef struct thread_data {
    int id;
    pthread_t tid;
    pthread_mutex_t * mutex;
    int start;
    int stop;
    long long * total_count;
} thread_data_t;

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

// Thread function that will count bin-hex-palindromes in a specific range
void * count_bin_hex_palindromes_range(void * data) {
    // Cast the pointer to void into the type we actually use
    thread_data_t * local_data = (thread_data_t *)data;
    // This will be the local counter, independent in each thread
    long long local_count = 0;
    
    for (int i = local_data->start; i <= local_data->stop; i++) {
        if (is_bin_hex_palindrome(i)) {
            local_count++;
        }
    }
    
    // Lock access to the shared variable before modifying it.
    // This will be done only once per thread
    pthread_mutex_lock(local_data->mutex);
        // Dereference the pointer to the total variable
        (*local_data->total_count) += local_count;
    pthread_mutex_unlock(local_data->mutex);

    pthread_exit(NULL);
}

// Function to count all bin-hex-palindromes using multiple threads
long long count_bin_hex_palindromes(inputs_t inputs) {
    int limit = (int)pow(2, inputs.n);
    int range = limit / inputs.threads;
    
    // Create an array of data structures
    thread_data_t * data = new thread_data_t[inputs.threads];
    // Create the mutex that will be shared by all threads
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    // Main result variable that will be shared by all threads
    long long total_count = 0;
    // Variable to store the return value of the pthread functions
    int status;

        // Start all the threads
    for (int i = 0; i < inputs.threads; i++) {
        // Fill the data for each of the threads
        data[i].id = i;
        data[i].total_count = &total_count;
        data[i].mutex = &mutex;
        
        // Compute the start and stop values used by each thread
        data[i].start = range * i;
        if (i == inputs.threads - 1) {
            data[i].stop = limit - 1;
        } else {
            data[i].stop = (range * (i + 1)) - 1;
        }

        status = pthread_create(&data[i].tid, NULL, &count_bin_hex_palindromes_range, (void *)&data[i]);
        printf("Created thread: %d, Range: [%d, %d]\n", i, data[i].start, data[i].stop);
        if (status == -1) {
            perror("ERROR: pthread_create");
        }
    }

    // Wait for the threads to finish
    for (int i = 0; i < inputs.threads; i++) {
        status = pthread_join(data[i].tid, NULL);
        if (status == -1) {
            perror("ERROR: pthread_join");
        }
    }
    return total_count;
}

// Verify if we got command line arguments
// Otherwise ask the user for them (defaults to 4 threads)
inputs_t get_args(int argc, char* argv[]) {
    inputs_t inputs;
    if (argc == 3) {
        inputs.n = atoi(argv[1]);
        inputs.threads = atoi(argv[2]);
    } else if (argc == 2) {
        inputs.n = atoi(argv[1]);
        inputs.threads = 4; 
    } else {
        cout << "Enter the exponent n (for 2^n): ";
        cin >> inputs.n;
        cout << "Enter the number of threads: ";
        cin >> inputs.threads;
    }
    return inputs;
}

// Entry point for the program
int main(int argc, char* argv[]) {
    inputs_t inputs = get_args(argc, argv);
    
    int limit = (int)pow(2, inputs.n);
    cout << "Counting bin-hex-palindromes less than 2^" << inputs.n << " (" << limit << ") with: " << inputs.threads << " threads" << endl;
    
    long long palindrome_count = count_bin_hex_palindromes(inputs);
    
    cout << "Count of bin-hex-palindromes: " << palindrome_count << endl;
    
    return 0;
}