# Shortcuts

There are N cities numbered from $1$ to $N$. Walking from $i$th city to $j$th city takes $|i-j|$ units of time. However, in every city there is a shortcut $a_i$. This shortcut allows you to travel from $i$ to $a_i$ in $1$ unit of time.

You are currenly in $1$st city and want to reach $N$th city. What is the minimum amount of time required to reach the $N$th city.

### Constraints

$1 \leq N \leq 10^{5}$
$1 \leq a_i \leq N$

### Input

$N$
$a_1 \ a_2 \ a_3 \ \dots \ a_N$

### Output

Print one integer, the minimum amount of time required to reach the $N$th city.

### Example

Input

```
7
2 6 4 4 6 6 7
```

Output

```
3
```

First you move from city $1$ to city $2$.
Then you take a shortcut from city $2$ to city $6$.
Then you move from city $6$ to the city $7$.

### Test cases

**Edge cases**

```
1
1

Output: 0
```

```
9
1 2 3 4 5 6 7 8 9

Output: 9
```

```
9
9 2 3 4 5 6 7 8 9

Output: 1
```

```
5
1 2 3 1 4

Output: 5
```

### Hints

- If we remove the shortcuts what is the quickest way to reach from $1$ to $N$ ?
- Try to solve this as a graph problem.

### Editorial

**Prerequisites**

- BFS Traversal

**Optimal Solution $O(N)$**

Each city can be treated as a node in a graph. Now we need to add edges. We can travel from $i$th node to $i+1$th and $i-1$th node in one unit time ($|i - (i+1)| = 1$). So we can add an edge connecting node $i$ to $i-1$ and $i+1$.

Now we need to deal with the shortcuts. A shortcut of $a_i$ takes us from $i$ to $a_i$th index. So we can add a **directed edge** from $i$ to $a_i$.

All that remains is to perform a BFS traversal with node $1$ as source.

**Time complexity: $O(N)$**
**Space complexity: $O(N)$**

**Resource links**

- [BFS Traversal](https://cp-algorithms.com/graph/breadth-first-search.html)
- [Striver Graph series](https://www.youtube.com/watch?v=YTtpfjGlH2M&list=PLgUwDviBIf0rGEWe64KWas0Nryn7SCRWw)

**Related problems**

- [BFS](https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1)

- [Bipartite check using BFS](https://leetcode.com/problems/is-graph-bipartite/)

- [Topological sort using BFS](https://practice.geeksforgeeks.org/problems/topological-sort/1)

### Code

```cpp
#include <bits/stdc++.h>


using namespace std;


/**
We have passed distance array by reference
*/
void bfs(int src ,
         vector<vector<int>>& graph,
         vector<bool>& visited ,
         vector<int>& distance)
{
	queue<int> q;
	q.push(src);
	visited[src] = 1;
	distance[src] = 0;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int&to : graph[cur])
		{
			if (!visited[to])
			{
				visited[to] = true;
				q.push(to);
				distance[to] = distance[cur] + 1;
			}
		}
	}
}

/**
* Constructing graph
**/
void makeGraph(vector<vector<int>>& graph, int n) {
	int a;
	for (int i = 1; i <= n; i++) {
		cin >> a;

		if (i != 1) {
			graph[i].push_back(i - 1);
			graph[i - 1].push_back(i);
		}

		if (i != n) {
			graph[i].push_back(i + 1);
			graph[i + 1].push_back(i);
		}

		graph[i].push_back(a);
	}

}

int main() {


	int n, a;
	cin >> n;

	vector<vector<int>> graph(n + 1);
	vector<int> distance(n + 1 , 0);
	vector<bool> visited(n + 1, false);

	makeGraph(graph, n);

	bfs(1, graph, visited, distance);

	cout << distance[n] << "\n";

	return 0;
}
```
