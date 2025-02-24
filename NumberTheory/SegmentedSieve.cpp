#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<long long> primes; // Global prime array

// Standard Sieve of Eratosthenes to find all primes up to `limit`
void sieve(long long limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (long long i = 2; i * i <= limit; ++i) {
        if (is_prime[i]) {
            for (long long j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (long long i = 2; i <= limit; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
}

// Segmented Sieve to find primes in the range [low, high]
vector<long long> segmented_sieve(long long low, long long high) {
    if (low < 2) low = 2; // 0 and 1 are not primes

    vector<bool> is_prime_segment(high - low + 1, true);

    for (long long p : primes) {
        if (p * p > high) break; // Optimization: No need to check further

        long long start = max(p * p, low + ((p - low % p) % p));
        for (long long j = start; j <= high; j += p) {
            is_prime_segment[j - low] = false;
        }
    }

    vector<long long> primes_in_segment;
    for (long long i = 0; i < is_prime_segment.size(); ++i) {
        if (is_prime_segment[i]) {
            primes_in_segment.push_back(low + i);
        }
    }

    return primes_in_segment;
}

// Function to check if a number is prime using the Segmented Sieve
bool is_prime(long long n) {
    if (n < 2) return false;

    // Check if n is in the precomputed primes list
    if (n <= primes.back()) {
        return binary_search(primes.begin(), primes.end(), n);
    }

    // Use Segmented Sieve for the range [n, n]
    vector<long long> result = segmented_sieve(n, n);
    return !result.empty();
}

int main() {
    // Precompute primes up to sqrt(10^12) = 10^6
    long long limit = 1e6;
    sieve(limit);

    // Test cases
    long long num;
    cout << "Enter a number to check if it is prime: ";
    cin >> num;

    if (is_prime(num)) {
        cout << num << " is a prime number." << endl;
    } else {
        cout << num << " is not a prime number." << endl;
    }

    return 0;
}
