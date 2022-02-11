## Police Stations

There are $N$ cities connected by $M$ one-way roads. You want to build police stations at some cities. A police station at city $i$ can protect city $j$ if either $i = j$ or the police can go to $j$ from $i$ and then come back to $i$.

Also, building a police station in city $i$ costs $cost_i$.

You have to determine the minimum amount required to protect all $N$ cities.
Also, you have to find the number of ways to build stations to protect $N$ cities with minimum amount. As the answer can be too large you have to find it modulo $10^9 + 7$.

### Constraints

$1 \leq N \leq 10^5$
$1 \leq M \leq 3*10^5$
$1 \leq a_i , b_i \leq N$
$1 \leq cost_i \leq 10^9$

### Input

$N \quad M$
$cost_1 \quad cost_2 \quad cost_3 \quad \dots \quad cost_N$
$a_1 \quad b_1$
$a_2 \quad b_2$
$\vdots$
$a_M \quad b_M$

### Output

Print two integers separated by whitespace. First the minimum amount required and second the number of ways to build police stations.

### Example

Input

```
6 7
1 5 8 7 2 2
1 2
2 3
3 1
4 5
5 6
6 5
5 4
```

Output

```
3 2
```

<img src="./assets/example.png" height="400px" width="400px"/>

Explaination

- We can make a police station at city $1$ and protect cities $(1,2,3)$. It will cost $1$ units.

- Then we can make a police station at city $5$ or $6$ and protect cities $(5,6,7)$. It will cost $2$ units.

So minimum cost is $3$ units.

To achieve this price we have $2$ possible ways

- $City_1 \quad and \quad City_5$
- $City_1 \quad and \quad City_6$

### Test cases

**Edge cases**

```
4 4
1 1 1 1
1 2
2 3
3 4
4 1

Output: 1 4
```

```
4 4
1 2 3 4
1 2
2 3
3 4
4 1

Output: 1 1
```

```
6 8
1 5 8 7 2 2
1 2
2 3
3 1
4 5
5 6
6 4
1 5

Output: 3 2
```

### Hints

- Notice that the road are **unidirectional**.
- Try to think of 2 conditions when it is impossible to travel from city $i$ to city $j$ and then back to city $i$.
- In the graph $1 \to 2$. It is impossible to travel from $1$ to $2$ and back to $1$, same for $2$. So now can you use this example to find the minimum number of police stations required?

### Editorial

**Prerequisites**

- Kosarajau's algorithm
- Basic combinatorics

**Optimal Solution $O(N+M)$**

To travel from city $i$ to city $j$ and back to city $i$, city $i$ and city $j$ must be in the **strongly connected component.**

**A component is called strongly connected if every vertex is reachable from every other vertex.**

To find the number of strongly connected components we use Kosarajau's algorithm. The pseudocode of this algorithm is given below:

- Perform DFS traversal of the graph. Push node to stack before returning.

- Find the transpose graph by reversing the edges.

- Pop nodes one by one from the stack and again do DFS on the transpose graph.

So the **minimum number of police stations required = number of strongly connected components.**
We need to find the amount required. We can calculate it by finding a node with minimum cost in each strongly connected component.

In each strongly connected component if there is more than one node with minimum cost then there is more than one way to select node in a strongly connected component.

$num_1$ = Number of nodes with minimum cost in component $1$.
$num_2$ = Number of nodes with minimum cost in component $2$.
$\vdots$
$num_k$ = Number of nodes with minimum cost in component $k$.

So total possible ways = $(num_1 * num_2 * \dots * num_k)\%(10^9+7)$

**Time complexity: $O(N+M)$**

**Resource links**

- [Kosarajau's Algorithm](https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm)
- [Kosarajau's Algorithm implementation](https://www.geeksforgeeks.org/strongly-connected-components/)
- [Striver Graph series](https://www.youtube.com/watch?v=YTtpfjGlH2M&list=PLgUwDviBIf0rGEWe64KWas0Nryn7SCRWw)

### Code

```cpp
#include <bits/stdc++.h>


using namespace std;

constexpr long long MOD = 1e9 + 7;

int n, m;

vector<vector<int>> graph;
vector<vector<int>> transpose_graph;
vector<bool> visited;
vector<int> order;

vector<long long> cost;

//Kosarajau's algorithm
void dfs1(int v) {
	visited[v] = true;

	for (int e : graph[v]) {
		if (!visited[e])
			dfs1(e);
	}

	order.push_back(v);
}


void dfs2(int v ,
          long long& min_cost_in_component,
          unordered_map<long long, long long>& nodes_with_min_cost
         ) {

	visited[v] = true;

	min_cost_in_component = min(min_cost_in_component , cost[v]);

	nodes_with_min_cost[cost[v]]++;

	for (int e : transpose_graph[v]) {
		if (!visited[e])
			dfs2(e,
			     min_cost_in_component,
			     nodes_with_min_cost);
	}
}


void initGraph() {
	int a, b;

	cin >> n >> m;

	graph.resize(n + 1);
	transpose_graph.resize(n + 1);
	visited.assign(n + 1, false);
	cost.resize(n + 1);

	for (int i  = 1; i <= n; i++)
		cin >> cost[i];

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		transpose_graph[b].push_back(a);
	}
}

int main() {

	initGraph();


	/***
	* Code below is implementations of Kosarajau's algorithm
	* Check the resources to read about it in detail
	*/
	for (int i = 1; i <= n; i++)
		if (!visited[i]) dfs1(i);


	long long total_cost = 0;
	long long total_ways = 1;

	fill(visited.begin(), visited.end() , false); // Resetting the visited array for second dfs
	reverse(order.begin(), order.end());


	for (int i = 0; i < order.size(); i++) {
		if (visited[order[i]]) continue;

		long long min_cost_in_component = 1e10;//We take 10^10 because max cost can be 10^9

		unordered_map<long long, long long> nodes_with_min_cost;

		dfs2(order[i],
		     min_cost_in_component,
		     nodes_with_min_cost);


		total_cost += min_cost_in_component;
		total_ways = (total_ways * nodes_with_min_cost[min_cost_in_component] % MOD) % MOD;

	}


	cout << total_cost << " " << total_ways << "\n";

	return 0;
}
```
