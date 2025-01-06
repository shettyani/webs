#include <iostream>
using namespace std;

// Function to perform binary search
int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        // Check if the target is at mid
        if (arr[mid] == target)
            return mid;

        // If the target is smaller than mid, it is in the left subarray
        if (arr[mid] > target)
            right = mid - 1;
        else
            // If the target is larger than mid, it is in the right subarray
            left = mid + 1;
    }
    return -1; // Target not found
}

// Function to print the result
void printResult(int index, int target) {
    if (index != -1)
        cout << "Element " << target << " found at index " << index << "." << endl;
    else
        cout << "Element " << target << " not found in the array." << endl;
}

// Main function
int main() {
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 10;

    cout << "Array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    // Perform binary search
    int result = binarySearch(arr, 0, n - 1, target);

    // Print the result
    printResult(result, target);

    return 0;
}
