// C++ program for the above approach
#include <bits/stdc++.h>

// Function to find maximum continuous
// maximum sum in the array
int kadane(const std::vector<int> &v) {
  // Stores current and maximum sum
  int currSum = 0;
  int maxSum = INT_MIN;

  // Traverse the array v
  for (int i : v) {
    // Add the value of the
    // current element
    currSum += i;

    // Update the maximum sum
    if (currSum > maxSum) {
      maxSum = currSum;
    }

    if (currSum < 0) {
      currSum = 0;
    }
  }

  // Return the maximum sum
  return maxSum;
}

// Function to find the maximum
// submatrix sum
void maxSubmatrixSum(std::vector<std::vector<int>> A) {
  // Store the rows and columns
  // of the matrix
  int r = A.size();
  int c = A[0].size();

  // Create an auxiliary matrix
  std::vector<std::unique_ptr<int[]>> prefix(r);

  // Traverse the matrix, prefix
  // and initialize it will all 0s
  for (int i = 0; i < r; i++) {
    prefix[i] = std::make_unique<int[]>(c);
    for (int j = 0; j < c; j++) {
      prefix[i][j] = 0;
    }
  }

  // Calculate prefix sum of all
  // rows of matrix A[][] and
  // store in matrix prefix[]
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      // Update the prefix[][]
      if (j == 0)
        prefix[i][j] = A[i][j];
      else
        prefix[i][j] = A[i][j] + prefix[i][j - 1];
    }
  }

  // Store the maximum submatrix sum
  int maxSum = INT_MIN;

  // Iterate for starting column
  for (int i = 0; i < c; i++) {
    // Iterate for last column
    for (int j = i; j < c; j++) {
      // To store current array
      // elements
      std::vector<int> v;

      // Traverse every row
      for (int k = 0; k < r; k++) {
        // Store the sum of the
        // kth row
        int el = 0;

        // Update the prefix
        // sum
        if (i == 0)
          el = prefix[k][j];
        else
          el = prefix[k][j] - prefix[k][i - 1];

        // Push it in a vector
        v.push_back(el);
      }

      // Update the maximum
      // overall sum
      maxSum = std::max(maxSum, kadane(v));
    }
  }

  // Print the answer
  std::cout << maxSum << "\n";
}

// Driver Code
int main() {
  std::vector<std::vector<int>> matrix = {{0, -2, -7, 0}, {9, 2, -6, 2}, {-4, 1, -4, 1}, {-1, 8, 0, -2}};

  // Function Call
  maxSubmatrixSum(matrix);

  return 0;
}
