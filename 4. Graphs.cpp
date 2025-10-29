/*
  Graphs
  Vertices connected by edges. Either directed or undirected, weighted or unweighted
  Trees are special types of graphs. DAG: directed acyclic graph also special
  A connected graph is one where a path exists between any two vertices
  Strongly connected if in a directed graph path exists starting from any
  Weakly connected if paths exist only if we treat all edges as undirected

  Graphs typically represented as adjacency lists
  maps vertice to list of all verticies it has an edge to
  Sometimes represented as  V x V matrix (where V = # vertices)

  For interviews typically given array of vertices
  in this case just turn it into adj_list before running algo

  Also look for problems that use maps ie matrix such as
    0 1 0
    0 1 1
    0 0 1
  where each 1 is a vertice/island and we can move
  horizontally or vertically. Note sometimes we want to do opposite, start from edge/0
*/

/*
  DFS
  Use vector<vector<int>> for adj list if all vertice indices are in one range
  other wise use an unordered_map<int, vector<int>>. Same with the visited set
*/
void dfs(int curr, vector<vector<int>>& adj_list, vector<bool>& visited) {
  visited[curr] = true;
  for (int next: adj_list[curr]) {
    if(!visited[next]) dfs(next, adj_list, visited);
  }
}

// Graph BFS (assuming strongly connected)
void bfs(int start, vector<vector<int>>& adj_list) {
  if (adj_list.size() == 0) return;
  vector<bool> visited(adj_list.size(), false);
  queue<int> q;
  q.push(start);
  visited[start] = true;
  while (q.size() > 0) {
    int curr = q.front();
    q.pop();
    for (int next: adj_list[curr]) {
      if (!visited[next]) {
        // by marking as visited here instead of at top
        // of while loop, we avoid adding things then skipping
        visited[next] = true;
        q.push(next);
      }
    }
  }
}

// map example problem: Number of islands in map
int numIslands(vector<vector<int>>& grid) {
  // going to use map as visited set by setting visited
  // squares to 
  if (grid.size() == 0) return 0;
  int res = 0;
  for (int r = 0; r < grid.size(); r++) {
    for (int c = 0; c < grid[0].size(); c++) {
      if (grid[r][c] == 1) {
        // can replace with bfs
        map_dfs(r, c, grid);
        res++;
      }
    }
  }
  return res;
}

void map_dfs(int r, int c, vector<vector<int>>& grid) {
  // mark as visited
  grid[r][c] = 0;
  int num_r = grid.size();
  int num_c = grid[0].size();
  // dirs for shifting by 1 in each direction
  // tbh should be global or passed in by reference but whatever
  vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  for (auto dir: dirs) {
    int new_r = r + dir.first;
    int new_c = c + dir.second;
    // check that it is in the grid
    bool in_grid = new_r >= 0 && new_c >= 0 && new_r < num_r && new_c < num_c;
    if (in_grid && grid[new_r][new_c] == 1) {
      // if also land/ part of same island recursive call
      map_dfs(new_r, new_c, grid);
    }
  }
}

void map_bfs(int start_r, int start_c, vector<vector<int>>& grid) {
  queue<pair<int, int>> q;
  q.push({start_r, start_c});
  grid[start_r][start_c] = 0;
  int num_r = grid.size();
  int num_c = grid[0].size();
  vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  while (q.size() > 0) {
    int r = q.front().first;
    int c = q.front().second;
    q.pop();
    for (auto& dir: dirs) {
      int new_r = r + dir.first;
      int new_c = c + dir.second;
      bool in_grid = new_r >= 0 && new_c >= 0 && new_r < num_r && new_c < num_c;
      if (in_grid && grid[new_r][new_c] == 1) {
        // mark as visited
        grid[new_r][new_c] = 0;
        q.push({new_r, new_c});
      }
    }
  }
} 

/*
  Union Find (disjoing sets)
*/

/*
  Topological Sort
  Given a DAG, it reads the entire graph in the order such that
  every node before a given node it read before that node is read.
  Ie every parent of a node come before it
*/

// Topological sort built on dfs, we use stack so we add node after children
// and we use visited set to not repeat. Let's say labelled [0, numN)
// this implementation will also detect cycles
vector<int> getTopo(int numN, vector<vector<int>>& adj_list) {
  stack<int> s;
  vector<bool> visited(numN, false);
  for (int i = 0; i < numN; i++) {
    if (!visited[i]) {
      vector<bool> path(numN, false);
      if(!topo(i, adj_list, path, visited, s)) return {};
    }
  }
  vector<int> res;
  while (s.size() > 0) {
    res.push_back(s.top());
    s.pop();
  }
  return res;
}

// return true if
bool topo(int node, vector<vector<int>>& adj_list, vector<bool>& path, vector<bool>& visited, stack<int>& s) {
  if (path[node]) return false;
  path[node] = true;
  for (int next: adj_list[node]) {
    if (!visited[next] && !topo(next, adj_list, path, visited, s)) return false;
  }
  visited[node] = true;
  s.push(node);
  return true;
}

// Dijkstra's


// Bellman-Ford

// Kruskal's

// Prim's
