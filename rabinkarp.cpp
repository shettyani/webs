#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Function to calculate (base^exp) % mod
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// Rabin-Karp Algorithm
vector<int> rabinKarp(const string& text, const string& pattern, int prime) {
    int n = text.size();
    int m = pattern.size();
    int base = 256; // Number of characters in the input alphabet
    long long hashText = 0; // Hash value for the text
    long long hashPattern = 0; // Hash value for the pattern
    long long h = 1; // Base^(m-1) % prime
    vector<int> result;

    // Calculate h = (base^(m-1)) % prime
    for (int i = 0; i < m - 1; i++) {
        h = (h * base) % prime;
    }

    // Calculate the hash value of the pattern and the first window of text
    for (int i = 0; i < m; i++) {
        hashPattern = (base * hashPattern + pattern[i]) % prime;
        hashText = (base * hashText + text[i]) % prime;
    }

    // Slide the pattern over the text one by one
    for (int i = 0; i <= n - m; i++) {
        // Check the hash values of the current window and the pattern
        if (hashText == hashPattern) {
            // Check for a spurious hit
            if (text.substr(i, m) == pattern) {
                result.push_back(i);
            }
        }

        // Calculate hash value for the next window of text
        if (i < n - m) {
            hashText = (base * (hashText - text[i] * h) + text[i + m]) % prime;

            // Make sure hashText is positive
            if (hashText < 0) {
                hashText += prime;
            }
        }
    }

    return result;
}

// Main function to test the Rabin-Karp Algorithm
int main() {
    string text, pattern;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    int prime = 101; // A prime number for hashing
    vector<int> occurrences = rabinKarp(text, pattern, prime);

    if (!occurrences.empty()) {
        cout << "Pattern found at indices: ";
        for (int index : occurrences) {
            cout << index << " ";
        }
        cout << endl;
    } else {
        cout << "Pattern not found." << endl;
    }

    return 0;
}
