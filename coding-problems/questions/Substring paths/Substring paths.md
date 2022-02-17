## Substrings path

You are given a graph with $N$ nodes and $M$ directed edges. One lowercase letter is assigned to each node. We define a **path's value as the number of the most frequently occurring letter**.

Find the path whose value is the largest. If the path value tends to infinity then print $-1$.

### Constraints

$1 \leq N \leq 10^5$
$1 \leq M \leq 10^5$
$1 \leq a_i,b_i \leq N$
$s_i = [a,z]$

### Input

$N \quad M$
$s$
$a_1 \quad b_1$
$a_2 \quad b_2$
$\vdots$
$a_M \quad b_M$

### Output

Print one integer, denoting the largest value or if it can be infinitely large print $-1$.

### Example

Input

```
5 4
abaca
1 2
1 3
3 4
4 5
```

Output

```
3
```

Explanation:

For path $1 \to 3 \to 4 \to 5$ the characters will be $aaca$. So $a$ is the most frequently occurring character, and it occurs $3$ times so the answer is $3$.

### Test cases

**Edge cases**

```
4 3
bbba
1 2
2 3
3 4

Output: 3
```

```
4 4
adgc
1 2
2 3
3 4
4 1

Output: -1
```

```
5 5
afcwa
1 2
2 3
3 4
4 1
4 5

Output: -1
```

```
4 3
bbaa
1 2
2 3
3 4

Output: 2
```

```
4 3
abcd
1 2
2 3
3 4

Output: 1
```

```
4 4
abca
1 2
2 3
3 4
1 4

Output: 1
```

### Hints

- Notice that the edges are **one-way**.
- First try to think of the case for which the answer will be $-1$
- Will the answer be $-1$ when there is a cycle?
- For node $a_i$ store the frequencies of all characters till $a_i$.
- Before evaluating node $a_i$ we need to evaluate all its parent. Is there any algorithm to do that?

### Editorial

**Prerequisites**

- Topological sorting

**Optimal Solution**

We can make an array
$dp[i][j]$ = respect when you are at the point $i$, then how many letters $j$ you can get. Note that $i$ is ranging from $1$ to $N$ and $j$ is from $1$ to $26$.

Then, you can do this dynamic programming algorithm by topological sorting. Specifically, you can use $in[i]$ to show how many edges that end at point $i$. First put all points i which satisfy $in[i]=0$ into a queue. When the queue is not empty, do the following steps repeatedly.

- Take one point from the front of the queue. We say it is i. Iterate all edges which begin at the point i.
- We say the endpoint of the edge is $k$. Then we update $dp[k][⋅]$ using $dp[i][⋅]$. Finally, we make $deg[k]$ minus by 1. If $in[k]=0$, then we add the point k into the queue.
- Make a variable $cnt$ plus by 1.
  When there is no cycle in the graph, the queue will be empty with $cnt=N$. Then the answer is the maximum number among $dp[i][j]$. If there are cycles in the graph, then $cnt$ cannot be n. Thus, the answer can be arbitrarily large. In that situation, we should output $-1$.

**Recurrence relation**

**$dp[k][x]$ = $max(dp[k][x], dp[e][x]$ + $(s[k] == x?1:0))$**

Where $e$ points to $k$ and $x$ ranges from $0 \leq x < 26$

**Time complexity :**$O(M*y)$ where $y$ = number of characters
**Space complexity :**$O(N*y)$ where $y$ = number of characters

**Things to keep in mind**

- Whenever the graph is directed, and you want to perform dynamic programming on it, then there is a chance that you might need to use topological sort.

**Resource links**

- [Topological sort using DFS](https://www.geeksforgeeks.org/topological-sorting/)
- [Topological sort using BFS (Kahn's Algorithm)](https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/)
- [Striver Graph series](https://www.youtube.com/watch?v=YTtpfjGlH2M&list=PLgUwDviBIf0rGEWe64KWas0Nryn7SCRWw)

### Code

```cpp

#include <bits/stdc++.h>

using namespace std;

int n , m;
vector<vector<int>> graph;
vector<vector<int>> dp;
vector<int> in;
string s;


int findAnswer() {
	queue<int> q;
	int cnt = 0, ans = -1;

	//We are selecting all the parent nodes
	for (int i = 1; i <= n; i++)
		if (in[i] == 0) {
			q.push(i);
			dp[i][s[i] - 'a']++;
		}

	while (!q.empty()) {
		int e = q.front();
		q.pop();
		cnt++;

		for (int k : graph[e]) {
			for (int i = 0; i < 26; i++)
				dp[k][i] = max(dp[k][i] , dp[e][i] + (int)(s[k] - 'a' == i));

			in[k]--;
			if (in[k] == 0) //All the parents of k have been processed so we can add it to the queue
				q.push(k);
		}
	}

	if (cnt != n) return ans;

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 26; j++)
			ans = max(ans , dp[i][j]);

	return ans;

}


int main() {

	int x, y;
	cin >> n >> m >> s;

	graph.resize(n + 1);
	dp.assign(n + 1 , vector<int>(26, 0));
	in.assign(n + 1 , 0);

	s = "#" + s; // This is done to make it 1 based index

	while (m--) {
		cin >> x >> y;
		graph[x].push_back(y);
		in[y]++;
	}

	cout << findAnswer() << "\n";

	return 0;
}
```
