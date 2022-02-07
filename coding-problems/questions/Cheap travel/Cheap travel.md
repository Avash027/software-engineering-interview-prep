## Cheap Travel

There are $N$ cities and $M$ roads that connect them. The cost of travelling from city $a_i$ to $b_i$ is $c_i$ for all $1 \leq i \leq N$. Currently, you are standing at City $1$ and you want to reach City $N$. You have a free pass that allows you to skip the cost of any one path in the route.

Find the cheapest route from $1$ to $N$.

There is always a way to reach from $1$ to $N$.

### Constraints

$2≤N≤10^5$
$1≤M≤2⋅10^5$
$1≤a,b≤N$
$1≤c≤10^9$

### Input

$N \ \ \ \ M$
$a_1 \ \ \ \ b_1 \ \ \ \ c_1$
$a_2 \ \ \ \ b_2 \ \ \ \ c_2$
$\vdots$
$a_M \ \ \ \ b_M \ \ \ \ c_M$

### Output

Print one integer, the cheapest route from $1$ to $N$.

### Example

Input

```
5 5
1 3 3
1 2 1
2 5 4
3 5 7
1 4 2
```

Output

```
1
```

Explaination:

There are 2 routes from $1$ to $5$

- $1 \to 3 \to 5 $.
   Total cost before paying free pass is $3$ + $7$ = $10$
  After we apply free pass total cost is $3$
- $1 \to 2 \to 5$
  Total cost before paying free pass is $1$ + $4$ = $5$
  After we apply free pass total cost is $1$

So the second path is cheaper. Hence, the answer is $1$.

### Test cases

**Edge cases**

```
1 2
1 2 5
Output will be 0
```

```
1 2
1 1 4
1 2 7
Output will be 0
```

```
3 4
1 2 4
1 2 6
3 4 1
3 4 2
Output will be 1
```

```
2 2
1 2 4
2 2 5
Output will be 0
```

### Hints

- Notice that $N$ and $M$ are large. So which algorithm can be used to find the shortest path?
- If I give you an edge $e_i$ can you find the cheapest path through that edge?
- Can you optimize it to find for each edge?

### Editorial

**Prerequisites**

- Dijkstra Algorithm

**Optimal Solution $O(N\log{N})$**

Let us **consider for a particular edge $e_i$** that connects city $x$ and city $y$. Now, we have to find the cheapest route from city $1$ to city $N$ that goes through road $e_i$.

To find the optimal route using the road $e_i$ we have to **find the shortest route from $1$ to $x$ and shortest route from $N$ to $y$.**

$answer_i \ \ =$ $min\ distance(1 \ \ to \ \ x) + min\ distance(N \ \ to \ \ y)$.

Now we have to effeciently find the $answer_i$ for each edge. This can be easily calculated using dijkstra algorithm.

- To find the distance from $1$ to $x$ we can use dijkstra algorithm with the source as $1$.
- To find the distance from $N$ to $y$ we can use dijkstra algorithm with the source as $N$, and we will use **transpose** graph.
  Transpose graph means the graph with reversed edges.

And the **final $answer$** = **$min(answer_i)$** for all **$1 \leq i \leq N$**

**Time complexity: $O(|M| + |N|\log{M})$**
**Space complexity: $O(|M|)$**

**Resource links**

- [Dijkstra Algorithm](https://cp-algorithms.com/graph/dijkstra.html)
- [Priority queue in C++](https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/)

**Related problems**

- [CF 20C](https://codeforces.com/contest/20/problem/C)
- [CF 986A](https://codeforces.com/contest/986/problem/A)
- [CF 229B](https://codeforces.com/contest/229/problem/B)

### Code

```cpp
#include <bits/stdc++.h>


using namespace std;

constexpr long long INF = 1e10;

struct Edge
{
	int x, y, cost;
};


/**
* Notice that we have passed the distance array by reference
*/
void dijkstra(vector<vector<pair<int, int>>>& g ,
              vector<long long>& dis,
              int src
             ) {

	priority_queue<pair<long long, int>, vector<pair<long long, int>>
	        , greater<pair<long long, int>>> pq;


	pq.push({0, src});
	dis[src] = 0;

	while (!pq.empty())
	{
		int u = pq.top().second;
		int dis_u = pq.top().first;

		pq.pop();

		if (dis[u] != dis_u) continue;

		for (auto e : g[u])
		{
			int v = e.first;
			int vd = e.second;
			if (dis[v] > dis[u] + vd)
			{
				dis[v] = dis[u] + vd;
				pq.push({dis[v], v});
			}
		}
	}

}


int main() {

	int n , m;
	cin >> n >> m;


	vector<vector<pair<int, int>>> graph(n + 1);
	vector<vector<pair<int, int>>> transpose_graph(n + 1);
	vector<Edge> edges(m);

	vector<long long> dis_1_to_x(n + 1, INF);
	vector<long long> dis_n_to_y(n + 1, INF);



	for (int i = 0; i < m; i++) {
		cin >> edges[i].x >> edges[i].y >> edges[i].cost;

		graph[edges[i].x].push_back({edges[i].y , edges[i].cost});
		transpose_graph[edges[i].y].push_back({edges[i].x , edges[i].cost});
	}


	dijkstra(graph , dis_1_to_x , 1);
	dijkstra(transpose_graph , dis_n_to_y , n);


	long long answer = INF;

	for (int i = 0; i < m; i++)
		answer = min(answer , dis_1_to_x[edges[i].x] + dis_n_to_y[edges[i].y]);


	cout << answer << "\n";

	return 0;
}
```
