## Colorful Cities

There are $N$ cities, numbered $1,2,…,N$ and $N-1$ roads that connect these cities. You want to assign each city `1` or `0`. However, it is **not allowed** for two adjecent cities to be assigned `1`. Find the number of ways in which the cities can be assigned number modulo $10^9 + 7$.

There are **no loops**. There are **no multiple roads** between any two cities, and it is **always possible to travel from one city to another**.

### Constraints

$1 \leq N \leq 2*10^5$
$1 \leq a_i,b_i \leq N$

### Input

$N$
$a_1 \ \ b_1$
$a_2 \ \ b_2$
$\vdots$
$a_{N-1} \ \ b_{N-1}$

### Output

Print one integer, the number of ways in which the cities can be assigned number modulo $10^9 + 7$.

### Example

Input

```
3
1 2
2 3
```

Output

```
5
```

All the possible ways are listed below

$(1_0 , 2_0 , 3_0)$
$(1_1 , 2_0 , 3_0)$
$(1_0 , 2_1 , 3_0)$
$(1_0 , 2_0 , 3_1)$
$(1_1 , 2_0 , 3_1)$

### Test cases

**Edge cases**

```
1

Output: 2
```

```
2 1
1 2

Output: 3
```

```
4
1 2
1 3
1 4

Output: 9
```

### Hints

- Notice the number of edges. Is this a special type of graph?
- We don't want adjacent cities to be assigned `1`. So we only need to look at the adjacent cities when assigning number.
- For each city what all information should we store that can help us later?
- Let us consider a city $v_i$. If I give you the number of ways to assign `0` and `1` for each adjacent city of $v_i$ can you use it to find the answer for $v_i$?

### Editorial

**Prerequisites**

- DFS Traversal
- Basic Dynamic programming

**Optimal Solution $O(N)$**

Let us assume each city as a node and each road as an unweighted bidirectional edge. As there are only $N-1$ edges it is a tree.

For each node we want to store $2$ values, the number of ways it can be assigned $1$ and the number of ways it can be assigned $0$.

$dp[i][j]$ = number of ways to assign subtree of node $i$ by assigning $j$ to node $i$.

There are two cases

- First, let's have a look at the leaf nodes. There are only $2$ ways to assign number.
  **Recurrence relation**
  $dp[i][1] = dp[i][0] = 1$

<br/>

- For parent $v_i$ to be $1$ all its child $c_i$ should be $0$ (to fulfill the condition). We want to find **all possible ways**

  **Recurrence relation**
  $dp[i][1] = dp[c_1][0] * dp[c_2][0] * \dots * dp[c_k][0]$

<br />

- For parent $v_i$ to be $0$ all its child $c_i$ can be either $0$ or $1$.

  **Recurrence relation**
  $dp[i][j] = (dp[c_1][0] + dp[c_1][1])*(dp[c_2][0] + dp[c_2][1])* \dots * (dp[c_k][0] + dp[c_k][1])$

So we can calculate the values for child nodes and move to its parent nodes. This can be achieved in $O(N)$ using DFS.

**Time complexity :** $O(N)$
**Space complexity :** $O(N)$

**Resource links**

- [Aditya Verma DP on trees](https://www.youtube.com/playlist?list=PL_z_8CaSLPWfxJPz2-YKqL9gXWdgrhvdn)

- [Aditya verma DP series](https://www.youtube.com/watch?v=nqowUJzG-iM&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)

- [Striver DP series](https://www.youtube.com/playlist?list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY)

- [Graph traversal (DFS)](https://cp-algorithms.com/graph/depth-first-search.html)

### Code

```cpp
#include <bits/stdc++.h>


using namespace std;

constexpr long long MOD = 1e9 + 7;

void dfs(int v ,
         int parent,
         vector<vector<int>>& adj,
         vector<vector<long long>>& dp) {

	long long ways_to_assign_0 = 1;
	long long ways_to_assign_1 = 1;


	for (int e : adj[v]) {
		if (e == parent) continue;

		//We will first evaluate the children
		dfs(e , v , adj , dp);

		//At this point we have evaluated all children of v

		ways_to_assign_1 = (ways_to_assign_1 * dp[e][0] % MOD) % MOD;
		ways_to_assign_0 = (ways_to_assign_0 * (dp[e][1] + dp[e][0]) % MOD) % MOD;
	}

	/**
	*Notice that we are also covering the base case here. In case v is a leaf node then dp[v][0] = dp[v][1]=1
	*/
	dp[v][0] = ways_to_assign_0;
	dp[v][1] = ways_to_assign_1;

}


int main() {

	int n, a, b;
	cin >> n ;

	vector<vector<int>> adj(n + 1);
	vector<vector<long long>> dp(n + 1 , vector<long long>(2, 0));


	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}


	dfs(1, -1, adj, dp);

	long long ans = (dp[1][0] % MOD + dp[1][1] % MOD) % MOD;

	cout << ans << "\n";


	return 0;
}
```
