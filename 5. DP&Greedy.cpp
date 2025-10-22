/*
  Dynamic Programming
  Idea behind DP is that we can find ways to not do repeated work.
  Easiest is to write a recursive solution and use a cache. This is called
  top down appraoch with memoization. We can also do bottom up with a loop
*/

// 1-Dimensional DP example, get nth fibonnaci number

// Non DP recursive solution, O(2^n) because for each n, two calls
int Fib(int n) {
  if (n == 1 || n == 2) return 1;
  return Fib(n - 1) + Fib(n - 2);
}

// memoization DP solution
int DP_Fib(int n) {
  // cache, can also use map
  vector<int> memo(n, -1);
  return memo_Fib(n, memo);
}

// Top down, memoization DP solution
// O(n) time, O(n) space, since we do less recursive calls 
// less because we cut subtree from call graph by caching
int memo_Fib(int n, vector<int>& memo) {
  // base case
  if (n == 1 || n == 2) return 1;
  // if result cached, return that
  if (memo[n-1] != -1) return memo[n-1];
  // otherwise calculate result
  int res = memo_Fib(n-1, memo) + memo_Fib(n-2, memo);
  // cache before returning
  memo[n-1] = res;
  return res; 
}

// Bottom-up, tabulation
// O(n) time, O(n) space.
int memo_Fib2(int n) {
  if (n <= 2) return 1;
  vector<int> memo(n);
  memo[0] = 1;
  memo[1] = 1;
  for (int i = 2; i < n; i++) memo[i] = memo[i-1] + memo[i-2];
  return memo[n-1];
}

// Optimal solution, bottom up DP
// O(n) time, O(1) space
int optimal_Fib(int n) {
  // stores n - 2
  int two_back = 1;
  // stores n
  int one_back = 1;
  for (int i = 3; i <= n; i++) {
    // calculates n
    int tmp = one_back + two_back;
    two_back = one_back;
    // n will always be stores in one_back
    one_back = tmp;
  }
  return one_back;
}

/*
  Greedy
  The greedy algorithm is to find the global optimal solution by at each step
  picking the local optimal step. 
*/