import numpy as np

class Solution:
    def climbStairs(self, n: int) -> int:
        if n == 1:
            return 1

        x = np.array([1, 1])
        X = np.array([[1, 1],
                      [1, 0]])
        y = np.dot(self.quickDot(X, n - 1), x)
        return int(y[0])
        

    def quickDot(self, X, n):
        if n == 1:
            return X

        if n == 2:
            return np.dot(X, X)
        
        if n % 2 == 0:
            return np.dot(self.quickDot(X, n//2), self.quickDot(X, n//2))
        else:
            return np.dot(self.quickDot(X, n//2), self.quickDot(X, (n + 1)//2))
