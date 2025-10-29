using namespace std;

/*
 Quick note on Arrays, the c++ memory safe/resizable array is the std::vector
 contiguous in memory so fast for the cache, O(1) for inserting and remove from back,
 O(n) insert and remove from middle (need to shift arr), O(1) read/modify
*/

/*
  Hashing & Hashmaps
  Hashing: hash function that maps input to usually an int we use as an index for array
  This is basis for hashmap which allows use to have amortized (average) O(1) insertion, deletion, read/write
  in c++ this is:
  unordered_map<int, string> hashmap // maps int to string
  hashmap[1] = "hello";
  map.erase(1); // removes element 1 if it exists
  map.contains(1) for c++ 20, or map.find(1) != map.end() for older

  hashset like a hashmap except it is an unordered set, so just can check if it contains something or not

  For simple cases can use vector as hashmap. For example, for alphabet can do 
  char c;
  vector<int> map(26); // 26 for all lower case
  map[c - 'a] // maps a to 0, b to 1 etc

  For making hash functions modulo operator (%) is useful since it keeps things in a certain range
*/

/*
  Binary Search
  If we have a presorted array, instead of doing linear search O(n) or a random search
  we can do a binary search that has O(log n) complexity. We pick middle value, then based
  on whether or not it's larger than or less than the value we want to find, we repeat
  search on the corresponding half. O(log n) because we cut search space in half each time
*/

// start by calling with lo = 0, hi = arr.size() - 1
int recursive_binary_search(int lo, int hi, vector<int>& arr, int target) {
  // base case: target not found
  if (lo > hi) return -1;
  // get mid, this avoid overflow
  int mid = lo + (hi - lo)/2;
  // base case: found the value
  if (arr[mid] == target) return mid;
  if (arr[mid] < target) {
    // smaller than val so we need to search upper half of array
    // mid + 1 to avoid infinite recursion (in case mid == hi)
    return recursive_binary_search(mid + 1, hi, arr, target);
  } else {
    // larger than target, search lower half
    return recursive_binary_search(lo, mid - 1, arr, target);
  }
}

int iterative_binary_search(vector<int>& arr, int target) {
  int lo = 0;
  int hi = arr.size() - 1;
  while (lo <= hi) {
    int mid = lo + (hi - lo)/2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  // error, not found
  return -1;
}

/*
  2 Pointers
  Given an array, instead of doing an O(n^2) search, we can use 2 pointers
  to iterate over array to find the result in O(2 * n) = O(n) time.
  Classic example is 2sum. Given a sorted array, we want to find the indices
  of two elements that add up to a given value
*/
vector<int> twoSum(vector<int> arr, int target) {
  // error case
  if (arr.size() == 0) return {-1, -1};
  int ptr1 = 0;
  int ptr2 = arr.size() - 1;
  while (ptr1 < ptr2) {
    int curr_sum = arr[ptr1] + arr[ptr2];
    // base case, found vals
    if (curr_sum == target) return {ptr1, ptr2};
    if (curr_sum < target) {
      ptr1++;
    } else {
      // curr_sum > target
      ptr2--;
    }
  }
  // error case, not found
  return {-1, -1};
}

/*
  Sliding Window
  These questions give an array, then usually ask you to return a subarray/window view
  that achieves some maximum or minimum. Here we need to keep track of the window as well
  as the condition (ie current running total or something like that) to avoid repeated work.
  Sometimes the window will have a fixed size, other times it will be dynamically resizeable. 
  For example, given stock prices with days what is the best time to buy and sell to maximize profit.
  Or given a substring, what is the longest substring without repeating characters.
*/

// find the longest substring without repeating characters
int longestSubstring(string s) {
  if (s.size() == 0) return 0;
  if (s.size() == 1) return 1;
  // hash set to keep track of characters currently in window
  unordered_set<char> set;
  // our result
  int res = 1;
  // we can either do 2 pointers or base and bounds (ie 1 ptr and window size)
  // we will do 2 pointer, second will be for loop
  int ptr1 = 0;
  // ptr1 will always be in the set, so insert it to begin with
  set.insert(s[0]);
  // for loop index will be our pointer
  // start of each for loop ptr2 will be next potential char
  // so we must start at index 1
  for (int ptr2 = 1; ptr2 <  s.size(); ptr2++) {
    // each iteration we slide window forward expanding it
    while (set.contains(s[ptr2])) {
      // while our condition is false, we need to contract window until it is true
      // can optimize with hash map mapping char to index to jump to index 
      // instead of using while loop to shorten
      set.erase(s[ptr1]);
      ptr1++;
    }
    set.insert(s[ptr2]);
    // ptr2 - ptr1 + 1 is the window size
    res = max(res, ptr2 - ptr1 + 1);
  }
  return res;
}

/*
  Prefix Sums
  If we often need prefixes or suffixes in calculations it is useful to pre-compute
  an array of all prefix and/or postfix sums. For example, if we want to calculate
  the product of an array except self without division ie [5, 2, 3] -> [6, 15, 10]
  in O(n) time
*/

vector<int> productExceptSelf(vector<int>& nums) {
  vector<int> res(nums.size());
  // put prefixes into result
  int curr_total = 1; // microoptimzation can not use this for prefix
  for (int i = 0; i < nums.size(); i++) {
    res[i] = curr_total;
    curr_total *= nums[i];
  }
  // put postfixes in
  curr_total = 1;
  for (int i = nums.size() -1; i >= 0; i--) {
    res[i] *= curr_total;
    curr_total *= nums[i];
  }
}


/*
  Sorting

  built in c++ is sort(arr.begin(), arr.end()), runs in O(n log n)

  Main concepts for sorting are: 
    Time complexity 

    Space complexity: Called In-place if it doesn't use space outside of arr
                      (O(1) or just small recursive stack)

    Adaptability: whether it is faster when the input is already partially/completely sorted

    Stability: Whether it preserves relative order of elements with equal values.
               For example if I have an array of pairs [{1, "One"}, {1, "Two"}, {0, "Zero"}]
               and we sort by first (the int). Stable guarantees 
               [{0, "Zero"}, {1, "One"}, {1, "Two"}] while non-stable can change
               order of "One" and "Two"
*/

// Merge Sort
// Split array into sorted subarrays then merge, arr size 1 = sorted
// O(n log n), O(n) space (can be made into O(1))
// Stable, not adaptable
void mergeSort(int lo, int hi, vector<int>& nums) {
  if (lo >= hi) return;
  int mid = lo + (hi - lo)/2;
  mergeSort(lo, mid, nums);
  mergeSort(mid + 1, hi, nums);
  merge(lo, mid, hi, nums);
}

void merge(int lo, int mid, int hi, vector<int>& nums) {
  vector<int> arr1(nums.begin() + lo, nums.begin() + mid + 1);
  vector<int> arr2(nums.begin() + mid + 1, nums.begin() + hi + 1);
  int ptr1 = 0;
  int ptr2 = 0;
  for (int i = lo; i <= hi; i++) {
    bool pick1 = (ptr1 < arr1.size() && ptr2 < arr2.size() && arr1[ptr1] < arr2[ptr2]) || (ptr2 >= arr2.size());
    if (pick1) {
      nums[i] = arr1[ptr1];
      ptr1++;
    } else {
      nums[i] = arr2[ptr2];
      ptr2++;
    }
  }
  return;
}

// Quicksort

// Insertion Sort

// Bucket Sort

// Heap sort (See #2)