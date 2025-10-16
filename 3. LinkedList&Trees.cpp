using namespace std;

/*
  LinkedList
  Simple data structure, like an array that isn't contiguous or world simplest graph.
  Nodes that hold values and point to next node. Can be doubly linked (prev and next ptr)
  Can also have back pointer. Usually just use pointers to solve problems
*/
struct ListNode {
    int val;
    Node* next;
}

/*
  FLoyd's Tortoise and Hare algorithm
  Use a fast and slow pointer to detect cycles. Can also find start of cycle
*/

// finding cycle (if exists)
bool hasCycle(ListNode *head) {
  // if head is nullptr return false
  if (!head) return false;
  ListNode* slow = head;
  ListNode* fast = head->next;
  while (fast != nullptr && fast->next != nullptr) {
    // if they point to same node we have a cycle
    if (slow == fast) return true;
    slow = slow->next;
    fast = fast->next->next;
  }
  return false;
}

// finding cycle start: array with n + 1 nums all in range [1, n] all unique except one repeats
int findDuplicate(vector<int>& nums) {
  // think of each index holding a pointer to the next node as val
  // 0th index is not part of list (since 0 not in range) but is head ptr
  // repeat number is a cycle
  // ie [1, 4, 3, 2, 2] is 4->2->3->2
  // we need to find start of cycle, first part of algo is detecting cycle
  int slow = nums[0];
  int fast = nums[slow];
  while (slow != fast) {
    slow = nums[slow];
    fast = nums[nums[fast]];
  }
  // now that we have found cycle, set one to start
  // then move both forward by one until they meet
  slow = 0;
  while (slow != fast) {
    slow = nums[slow];
    fast = nums[fast];
  }
  return slow;
}

/*
  Trees: Root is the top level node, has pointer to children. Heirarchecal, acyclic.
  A directed acyclic graph (DAG) where each node only has 1 parent and 1 node has no parents
*/

struct TreeNode {
  int val;
  // or array or vector of children if more than 2
  TreeNode* left;
  TreeNode* right;
}

// Depth first Search. Can be pre-order, post-order, or in-order
// (just place recursive calls in different places)
void recursive_dfs(TreeNode* root) {
  // base case: root is nullptr
  if (!root) return;
  // do something for pre-order here
  recursive_dfs(root->left);
  // do something for in-order here
  recursive_dfs(root->right);
  // do something for post-order here
}

// pre-order, harder to do in and post order iteratively
void iterative_dfs(TreeNode* root) {
  // edge case: root is null
  if (!root) return;
  stack<TreeNode*> s;
  stack.push(root);
  while (stack.size() > 0) {
    TreeNode* curr = s.top();
    s.pop();
    // do stuff here for pre-order
    if (curr->right) s.push(curr->right);
    if (curr->left) s.push(curr->left);
  }
}

/*
  Breadth First Search (BFS)
  level order traversal, useful if we want to print tree
  done iteratively usually.
*/

void bfs(TreeNode* root) {
  if(!root) return;
  queue<TreeNode*> q;
  q.push(root);
  // not necessary but commonly useful
  int level = 0;
  while (q.size() > 0) {
    int level_size = q.size();
    // for loop to traverse one level at a time
    for (int i = 0; i < level_size; i++) {
      TreeNode* curr = q.front();
      q.pop();
      if (curr->left) q.push(curr->left);
      if (curr->right) q.push(curr->right);
    }
    level++;
  }
}

/*
  Binary Search Trees (BSTs)
  Binary tree where for each node, all the elements in the left subtree are smaller and all
  elements in right are larger. O(log n) search time (binary search)
*/

// just special dfs
bool searchBST(TreeNode* root, int target) {
  // base case, not found
  if (!root) return false;
  // base case, found target
  if (root->val == target) return true;
  if (root->val > target) {
    // search left subtree
    return searchBST(root->left, target);
  } else {
    // search right
  return searchBST(root->right, target);
  }
}

// iterative version
bool searchBST(TreeNode* root, int target) {
  TreeNode* curr = root;
  while (curr) {
    if (curr->val == target) return true;
    if (curr->val > target) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  return false;
}

/*
  Tries
  Special trees used to store sets of strings in a space efficient way.
  Idea is to start with root node (that matches anything), and for children
  of each node to be a letter and for it to say whether it is end of word.
  That way we can store so words like "bar" and "ball" like so
            .
            b
            a
          l   r
          l
*/
// Implementation
class Trie {
private:

  class TrieNode {
  public:
    bool isWord;
    TrieNode* children[26];
    TrieNode(): isWord(false) {
      for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
  };

  TrieNode* root;

  // helper for freeing memory
  void clear(TrieNode* root) {
    if (!root) return;
    for (TrieNode* ptr: root->children) clear(ptr);
    delete root;
  }

public:
  Trie(): root(new TrieNode()) {}

  ~Trie() {
    clear(root);
  }

  bool add(string s) {
    if (s == "") {
      bool res = root->isWord;
      root->isWord = true;
      return res;
    }
    TrieNode* curr = root;
    for (char c: s) {
      if (!curr->children[c - 'a']) curr->children[c - 'a'] = new TrieNode();
      curr = curr->children[c - 'a'];
    }
    bool res = curr->isWord;
    curr->isWord = true;
    return res;
  }

  bool search(string s) {
    return search2(root, 0, s);
  }

  // dfs style search
  bool search2(TrieNode* root, int char_i, string& s) {
    if (!root) return false;
    if (char_i == s.size()) return root->isWord;
    return search2(root->children[s[char_i] - 'a'], char_i + 1, s);
  }
};
