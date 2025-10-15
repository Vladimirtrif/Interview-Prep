/*
  Queue: FIFO, O(1) for  back insertion (push()),front removal (pop()), front retrieval (front()).
  O(n) for other elements (call push/pop multiple times)

  Implementation: doubly linked list / linked list with pointer to back
*/

/*
  Stack: LIFO, same time complexity as queue just different order
  Look for: Parentheses patterm (most recent opened must be first one closed)
            Monotonic pattern: if elements in stack are always in sorted order, ie we 
                                keep growing stack until we get to next smallest, then we pop
                                everything that is larger than it.
            Paths and backtracking
  Implementation: Usually a linked list.
*/

// Stack example problem: Valid parentheses, make sure they are balanced with different types (, [, {
bool validParens(string s) {
  if (s.size() == 0) return true;
  if (s.size() == 1) return false;
  stack<char> st;
  for (char c: s) {
    if (c == '{' || c == '[' || c == '(') {
      st.push(c);
      continue;
    }
    if (st.size() == 0) return false;
    if (c == ')' && st.top() != '(') return false;
    if (c == '}' && st.top() != '{') return false;
    if (c == ']' && st.top() != '[') return false;
    st.pop();
  }
  return st.size() == 0;
}

/*
  Heap: Like a stack except largest element at front. 
  O(1) top() (largest element), O(log n) insertion, O(log n) removal of top
  In c++ called priority_queue<int> can choose what to use under the hood in c++ 
  and can pass in custom comparison function. Ie for a min heap we can do
  
  priority_queue<int, vector<int>, greater<int>> min_heap;

  Look for: Top k: ie keep track of k largest, or k smallest
            Finding median
            Greedy

  Heapify: if we are given all of the elements upfront, instead of O(n log n) for making a heap
  (inserting one by one), we can use heapify to make heap in O(n) time.
  In c++ this is just priority_queue<int> heap(vec.begin(), vec.end());

  Heapify Implementation: 

  Implementation: Tree where root is largest element and the tree is implemented using a vector. Insertion and deletion you have percolation
*/

// Example: Find kth largest element in array (not distinct)
int findKthLargest(vector<int>& nums, int k) {
  // Time: O(n log k), space: O(k)
  priority_queue<int, vector<int>, greater<int>> heap;
  for (int n: nums) {
      heap.push(n);
      if (heap.size() > k) {
          heap.pop();
      }
  }
  return heap.top();
  /* Slightly faster but worse space using heapify
  // Time: O(n + klogn) Space: O(n)
  priority_queue<int> heap(nums.begin(), nums.end());
  for (int i = 1; i < k; i++) {
      heap.pop();
  }
  return heap.top();
  */
}