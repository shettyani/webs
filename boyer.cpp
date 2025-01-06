//Below is the complete code for the Boyer-Moore Algorithm in C++:

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to create the bad character heuristic table
void badCharHeuristic(const string& pattern, vector<int>& badCharTable) {
    int m = pattern.size();
    int NO_OF_CHARS = 256;

    // Initialize all occurrences as -1
    badCharTable.resize(NO_OF_CHARS, -1);

    // Fill the actual value of the last occurrence of each character
    for (int i = 0; i < m; i++) {
        badCharTable[pattern[i]] = i;
    }
}

// Boyer-Moore pattern searching algorithm
void boyerMoore(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    if (m == 0 || n == 0 || m > n) {
        cout << "No match found!" << endl;
        return;
    }

    // Create the bad character table
    vector<int> badCharTable;
    badCharHeuristic(pattern, badCharTable);

    int shift = 0; // Shift of the pattern over the text

    while (shift <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j while characters of pattern and text are matching
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        // If the pattern is found
        if (j < 0) {
            cout << "Pattern found at index " << shift << endl;

            // Shift the pattern so that the next character in the text aligns with
            // the last occurrence of it in the pattern. If it does not occur, shift
            // the pattern by m (pattern length).
            shift += (shift + m < n) ? m - badCharTable[text[shift + m]] : 1;
        } else {
            // Shift the pattern to align the bad character with its last occurrence
            // in the pattern. If the bad character is not in the pattern, shift by (j + 1).
            shift += max(1, j - badCharTable[text[shift + j]]);
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

    boyerMoore(text, pattern);

    return 0;
}


/*---

Explanation:

1. Bad Character Heuristic:

The badCharHeuristic function builds a table of the last occurrence of every character in the pattern.

This table is used to skip sections of the text when a mismatch occurs.



2. Search Algorithm:

The algorithm starts matching the pattern from the rightmost character.

On mismatch, it shifts the pattern based on the position of the mismatched character using the bad character heuristic.



3. Time Complexity:

Best case: , where  is the text length and  is the pattern length.

Worst case: , but this is rare.





---

Example Input/Output:

Input:

Enter the text: abracadabra
Enter the pattern: abra

Output:

Pattern found at index 0
Pattern found at index 7
*/
