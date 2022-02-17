## Cheap fair

There are $n$ towns connected by $m$ two-way roads between towns. You can reach any town from any other town using roads.
There are $k$ types of goods produced. And the $i$th town produces good of only one type denoted by $a_i$. To hold a fair you have to bring at least $s$ different types of goods.
It costs $dis_{u,v}$ to bring goods from town $u$ to town $v$ where $dis_{u,v}$ is the length of the shortest path from $u$ to v. Length of a path is the number of roads in this path.

Calculate the minimum travel cost to hold a fair in each of $n$ towns.

### Constraints

$1 \leq n \leq 10^5$
$0 \leq m \leq 10^5$
$1 \leq u,v \leq n$
$1 \leq s \leq k \leq min(n,20)$
$1 \leq a_i \leq k$

### Input

$n \quad m \quad s \quad k$
$a_1 \quad a_2 \quad \dots \quad a_N$
$u_1 \quad v_1$
$u_2 \quad v_2$
$\vdots$
$u_M \quad v_M$

### Output

Print $n$ integers separated by whitespace where, the $i$-th of them is the minimum amount you need to spend on travel expenses to hold a fair in town $i$.

### Example

Input

```
5 5 3 4
1 2 4 3 2
1 2
2 3
3 4
4 1
4 5

```

Output

```
2 2 2 2 3
```

Explanation :

To hold a fair in town 1 you can bring goods from towns $1$ (Rs $0$), $2$ (Rs $1$) and $4$ (Rs $1$). Total amount is $2$.

Town $2$: Goods from towns $2$ ($0$), $1$ ($1$), $3$ ($1$). Sum equals $2$.

Town $3$: Goods from towns $3$ ($0$), $2$ ($1$), $4$ ($1$). Sum equals $2$.

Town $4$: Goods from towns $4$ ($0$), $1$ ($1$), $5$ ($1$). Sum equals $2$.

Town $5$: Goods from towns $5$ ($0$), $4$ ($1$), $3$ ($2$). Sum equals $3$.

### Test cases

**Edge cases**

```
1 0 1 1
1

Output: 0
```

```
2 1 1 2
1 2
1 2

Output: 0 0
```

```
2 1 2 2
1 2
2 1

Output: 1 1
```

```
2 0 1 1
1 2

Output: 0 0
```

```
7 6 2 3
1 2 3 3 2 2 1
1 2
2 3
3 4
2 5
5 6
6 7

Output: 1 1 1 2 2 1 1
```

### Hints

- Notice that the value of $k$ is very small.
- The only way to get good $a_i$ is to get it from the town where it is produced.
- Can you use multisource BFS here?

### Editorial

**Prerequisites**

- Breadth first search

**Optimal Solution $(k(n+m))$**

Notice that the value of $k$ is very small, so it is efficient to find a cost to bring a good $a_i$ in each town. To do this we can use multisource BFS.  
In multisource BFS we find the shortest path to a node from a number of initial nodes. Its implementation is really similar to that of standard BFS.

Pseudocode for the algorithm is given below:

- For each good we will select all the towns that are producing it.
- These towns are the source, so we push them to queue
- Then we will follow the standard BFS algorithm
- We will keep an array $cost[i][j]$ which denotes the minimum cost to transport good $j$ to town $i$.

Now for each $i$ we can sort the $cost[i]$ in a non-decreasing order and select the first $s$ expenses.

**Time complexity :**$O(k(n+m))$

**Space complexity :**$O(max(m , n*k))$

**Resource links**

- [Standard BFS](https://www.hackerearth.com/practice/algorithms/graphs/breadth-first-search/tutorial/)
- [Rotten oranges tutorial](https://www.youtube.com/watch?v=pUAPcVlHLKA)
- [Striver Graph series](https://www.youtube.com/watch?v=YTtpfjGlH2M&list=PLgUwDviBIf0rGEWe64KWas0Nryn7SCRWw)

**Related problems**

- [Monsters](https://cses.fi/problemset/task/1194)
- [Rotten oranges](https://leetcode.com/problems/rotting-oranges/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

constexpr int INF = (int)1e8;

int n, m, s, k;
vector<vector<int>> graph;
vector<vector<int>> color_index;
vector<vector<int>> cost;

void bfs(int color)
{
	vector<int> dis(n + 1, INF);
	queue<int> q;


	for (int producer_town : color_index[color]) {
		q.push(producer_town);
		dis[producer_town] = 0;
	}

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int&to : graph[cur])
		{
			if (dis[to] > dis[cur])
			{
				q.push(to);
				dis[to] = dis[cur] + 1;
			}
		}
	}

	for (int i = 1; i <= n; i++)
		cost[i][color] = dis[i];
}


void input() {
	int x, y, c;

	cin >> n >> m >> s >> k;

	graph.resize(n + 1);
	color_index.resize(k + 1);
	cost.assign(n + 1 , vector<int>(k + 1 , INF));

	for (int i = 1; i <= n; i++) {
		cin >> c;
		color_index[c].push_back(i);
	}

	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
}

int main() {

	input();

	for (int color = 1 ; color <= k; color++) {
		bfs(color);
	}


	for (int i = 1; i <= n; i++) {
		sort(cost[i].begin(), cost[i].end());
		int ans_i = accumulate(cost[i].begin() , cost[i].begin() + s , 0);
		cout << ans_i << " ";
	}

	return 0;
}
```
