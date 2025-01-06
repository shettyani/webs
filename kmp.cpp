//Below is the complete code for the Knuth-Morris-Pratt (KMP) Algorithm in C++:

#include <iostream>
#include <vector>
using namespace std;

// Function to build the LPS (Longest Prefix Suffix) array
void buildLPSArray(const string& pattern, vector<int>& lps) {
    int m = pattern.size();
    lps[0] = 0; // The first element is always 0
    int len = 0; // Length of the previous longest prefix suffix
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // Fallback to the previous prefix
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Pattern Searching Algorithm
void KMP(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    // Create the LPS array
    vector<int> lps(m);
    buildLPSArray(pattern, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = lps[j - 1]; // Continue searching for the next match
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1]; // Fallback in the pattern
            } else {
                i++;
            }
        }
    }
}

// Main function
int main() {
    string text, pattern;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern: ";
    getline(cin, pattern);

    KMP(text, pattern);

    return 0;
}

/*How the Code Works:

1. LPS Array:

The buildLPSArray function precomputes the Longest Prefix Suffix (LPS) array for the given pattern.

This helps in determining how much to shift the pattern after a mismatch.



2. Search Phase:

The KMP function uses the LPS array to efficiently search the pattern in the text.

Instead of starting over on mismatch, it uses the LPS array to skip unnecessary comparisons.



3. Time Complexity:

Preprocessing: , where  is the length of the pattern.

Searching: , where  is the length of the text.

Overall: .




Example Input/Output:

Input:

Enter the text: ababcababcabc
Enter the pattern: abc

Output:

Pattern found at index 2
Pattern found at index 7
Pattern found at index 10
  */
