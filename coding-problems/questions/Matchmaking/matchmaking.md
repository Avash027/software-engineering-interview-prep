## Matchmaking

There are $N$ people in a town, and you want to organize a match between $2$ teams. However, there are $M$ pairs of people who are incompatible with each other.

So you have to fulfill two conditions,

- Each person must be in either of team.
- If $x$ and $y$ are incompatible then they should be in different team

If it is possible to make teams then print `YES` else print `NO`.

### Constraints

$1 \leq N \leq 10^5$
$0 \leq M \leq 10^5$
$1 \leq x_i,y_i, \leq N$

### Input

$N \quad M$
$x_1 \quad y_1$
$x_2 \quad y_2$
$\vdots$
$x_M \quad y_M$

### Output

Print `YES` if it is possible to make teams else print `NO`.

### Example

Input

```
3 2
1 2
1 3
```

Output

```
YES
```

Explanation:

We can put citizen 2 and 3 in one team and citizen 1 in the other team.

### Test cases

**Edge cases**

```
100 0

Output: YES
```

```
3 3
1 2
1 3
2 3

Output: NO
```

```
1 0

Output: YES
```

### Hints

- We are essentially dividing people into two disjoint set.
- Treat the $N$ people as $N$ nodes and the incompatibilities as edges.
- Two **adjacent** people cannot be in the same team
- If $x$ and $y$ are connected, and we put $x$ is team $1$ then we must put $y$ in $2$. If we cannot do, so then it is impossible to make teams.

### Editorial

**Prerequisites**

- Depth first search
- Bipartite Graphs

**Optimal Solution**

If we represent the citizens as nodes, we will have a graph where if two nodes (i.e, citizens) are incompatible there will be an undirected edge between them.
Now we have to put each of the nodes into one of two groups such that no two nodes belonging to the same group have an edge between them.
This is a standard case of bipartite checking.

We can implement bipartite checking using both BFS and DFS, but we will discuss the DFS method. The pseudocode for the algorithm is given below.

- We keep an additional array $teams$ which can have two values $0$ or $1$.
- We do a standard DFS traversal
- Each time we visit a, yet unvisited neighbor of a vertex assigned to one side, we assign it to the other side. When we try to go to a neighbor of a vertex assigned to one side which has already been visited, we check that is has been assigned to the other side; if it has been assigned to the same side, we conclude that the graph is not bipartite. Once we've visited all vertices and successfully assigned them to sides, we know that the graph is bipartite, and we have constructed its partitioning.

**Time complexity :**$O(N+M)$

**Space complexity :**$O(M+N)$

**Things to keep in mind**

Another way to look into this problem is, if there are no cycles in a graph of even length then teams can always be made. However, this method is too complicated.

**Resource links**

- [Bipartite checking](https://www.geeksforgeeks.org/bipartite-graph/)
- [Striver Graph series](https://www.youtube.com/watch?v=YTtpfjGlH2M&list=PLgUwDviBIf0rGEWe64KWas0Nryn7SCRWw)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> teams;
vector<bool> visited;

bool dfs(int v, int team_num) {

	visited[v] = true;
	teams[v] = team_num;

	for (int to : graph[v]) {
		if (!visited[to]) {
			if (dfs(to , team_num ^ 1) == false) return false;
		} else {
			if (teams[v] == teams[to]) return false;
		}

	}

	return true;
}

int main() {

	int x, y;
	cin >> n >> m;

	if (m == 0) {
		cout << "YES\n";
		return 0;
	}

	graph.resize(n + 1);
	teams.assign(n + 1, 0);
	visited.assign(n + 1, false);


	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	bool isPossible =  dfs(1, 0);

	if (isPossible) cout << "YES\n";
	else cout << "NO\n";


	return 0;
}
```
