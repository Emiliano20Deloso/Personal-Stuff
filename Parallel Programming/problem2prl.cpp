/*
Emiliano Delgadillo Osorio
3 de Junio de 2025
Parallel programming and concurrent programming
Problem #2 Parallel

TEST 1: 
Enter a positive integer number: 82
Enter the number of threads: 4
Computing sum of primes (82) with: 4 threads
Created thread: 0, Range: [2, 21]
Created thread: 1, Range: [22, 41]
Created thread: 2, Range: [42, 61]
Created thread: 3, Range: [62, 82]
Sum of primes: 791

TEST 2:
Enter a positive integer number: 10
Enter the number of threads: 4
Computing sum of primes (10) with: 4 threads
Created thread: 0, Range: [2, 3]
Created thread: 1, Range: [4, 5]
Created thread: 2, Range: [6, 7]
Created thread: 3, Range: [8, 10]
Sum of primes: 17

TEST 3: 
Enter a positive integer number: 115
Enter the number of threads: 4
Computing sum of primes (115) with: 4 threads
Created thread: 0, Range: [2, 29]
Created thread: 1, Range: [30, 57]
Created thread: 2, Range: [58, 85]
Created thread: 3, Range: [86, 115]
Sum of primes: 1593

*/

#include <iostream> 
#include <cmath>
#include <pthread.h>
#include <iomanip>

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
    long long * total_sum;
} thread_data_t;

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

// Thread function that will compute the sum of primes in a specific range
void * compute_prime_sum_range(void * data) {
    // Cast the pointer to void into the type we actually use
    thread_data_t * local_data = (thread_data_t *)data;
    // This will be the local counter, independent in each thread
    long long local_sum = 0;
    
    for (unsigned long long i = local_data->start; i <= local_data->stop; i++) {
        if (is_prime(i)) {
            local_sum += i;
        }
    }
    // Lock access to the shared variable before modifying it.
    // This will be done only once per thread
    pthread_mutex_lock(local_data->mutex);
        // Dereference the pointer to the total variable
        (*local_data->total_sum) += local_sum;
    pthread_mutex_unlock(local_data->mutex);

    pthread_exit(NULL);
}

long long compute_prime_sum(inputs_t inputs) {
    long long range = (inputs.n - 1) / inputs.threads;  
    // Create an array of data structures
    thread_data_t * data = new thread_data_t[inputs.threads];
    // Create the mutex that will be shared by all threads
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    // Main result variable that will be shared by all threads
    long long total_sum = 0;
    // Variable to store the return value of the pthread functions
    int status;

    // Start all the threads
    for (int i = 0; i < inputs.threads; i++) {
        // Fill the data for each of the threads
        data[i].id = i;
        data[i].total_sum = &total_sum;
        data[i].mutex = &mutex;
        
        // Compute the start and stop values used by each thread
        data[i].start = 2 + (range * i);
        if (i == inputs.threads - 1) {
            data[i].stop = inputs.n;
        } else {
            data[i].stop = 2 + (range * (i + 1)) - 1;
        }

        status = pthread_create(&data[i].tid, NULL, &compute_prime_sum_range, (void *)&data[i]);
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
    return total_sum;
}

// Verify if we got command line arguments
// Otherwise ask the user for them 
inputs_t get_args(int argc, char* argv[]) {
    inputs_t inputs;
    if (argc == 3) {
        inputs.n = atoi(argv[1]);
        inputs.threads = atoi(argv[2]);
    } else if (argc == 2) {
        inputs.n = atoi(argv[1]);
        inputs.threads = 4;  
    } else {
        cout << "Enter a positive integer number: ";
        cin >> inputs.n;
        cout << "Enter the number of threads: ";
        cin >> inputs.threads;
    }
    return inputs;
}

// Entry point for the program
int main(int argc, char* argv[]) {
    inputs_t inputs = get_args(argc, argv);
    
    cout << "Computing sum of primes (" << inputs.n << ") with: " << inputs.threads << " threads" << endl;
    
    long long prime_sum = compute_prime_sum(inputs);
    
    cout << "Sum of primes: " << prime_sum << endl;
    
    return 0;
}