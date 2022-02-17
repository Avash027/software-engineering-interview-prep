## Class Schedule

You have to complete $N$ classes. There are $M$ requirements of the form "class $a$ has to be completed before class $b$". Each class has also class score $c_i$. If at any point you have the option to choose from multiple classes you have to select the class with the greatest $c_i$.

You have to find an order in which you can complete the courses. If there is no way to find the order then print $-1$

### Constraints

$1 \leq N \leq 10^5$
$1 \leq M  \leq 10^5$
$1 \leq a_i,b_i \leq N$
$1 \leq c_i \leq 10^9$
$All \quad c_i \quad are \quad unique$

### Input

$N \quad M$
$c_1 \quad c_2 \quad \dots \quad c_N$
$a_1 \quad b_1$
$a_2 \quad b_2$
$\vdots$
$a_M \quad b_M$

### Output

If it is possible to find answer print $N$ numbers separated by whitespace else print $-1$

### Example

```
4 4
3 2 5 7
1 2
1 3
2 4
3 4
```

```
1 3 2 4
```

Explanation

- We have to start from class number $1$.
- After we finish class number $1$ then we can either do class $2$ or class $3$. As $c_3 > c_2$ so we select class $3$.
- Then we can select class $2$.
- Now there is no prerequisite for class $4$, so we can complete class $4$.

### Test cases

**Edge cases**

```
2 2
1 3
1 2
2 1

Output: -1
```

```
6 4
1 2 3 4 5 6
1 2
2 3
4 5
5 6

Output: 4 5 6 1 2 3
```

```
5 4
5 3 1 5 2
1 2
3 4
4 5
5 3

Output: -1
```

```
3 3
1 2 3
1 1
2 2
3 3

Output: -1
```

### Hints

- How do we calculate the number of prerequisite for a class.
- Should we keep a count of number of in-edges for each node?
- After we process a parent node then how should we update the child node?

### Editorial

**Prerequisites**

- Topological sorting (Kahn's Algorithm)

**Optimal Solution $O(N+M)$**

Let's define $in_i$ as the number of edges pointing towards $i$.
To process $i$ we must process all the parents of $i$. Every time we process a node we reduce the $in$ value of its child by $1$. Once the $in$ value of a node is $0$ it means that all the parents of this node is processed, and we can process this node.

Now we need to make sure to print the classes number according to their class score. We can achieve this using max priority queue which compares two nodes based on their class score.

Now if there is a cycle in the graph then $in$ for some nodes will never be equal to $0$. So if number of nodes in answer $\neq$ N then answer will be $-1$.

Pseudocode for the above algorithm is given below:

- Store all the nodes in a max priority queue whose $in$ value is $0$.
- Pick the top node from the max priority queue.
- Add the node to the answer.
- Decrease the $in$ value of all its child by $1$.
- If the $in$ value of any child is $0$ then push it to the priority queue.

**Time complexity :**$O(N+M)$

**Space complexity :**$O(N)$

**Resource links**

- [Striver Graph series](https://www.youtube.com/watch?v=YTtpfjGlH2M&list=PLgUwDviBIf0rGEWe64KWas0Nryn7SCRWw)

- [Priority queue in C++](https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/)

- [Priority queue in Java](https://www.geeksforgeeks.org/priority-queue-class-in-java/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> in;
vector<int> class_score;

vector<int> KahnAlgo() {
	vector<int> ans;

	// The pair will store {class_score[i] , i}
	//This is a max priority queue so the class with higher priority queue will always be on top
	priority_queue<pair<int, int>> pq;

	for (int i = 1; i <= n; i++)
		if (in[i] == 0)
			pq.push({class_score[i], i});

	while (!pq.empty()) {
		int node = pq.top().second;
		pq.pop();
		ans.push_back(node);

		for (int child : graph[node]) {
			--in[child];

			if (in[child] == 0) // All the parents have been processed
				pq.push({class_score[child] , child});
		}
	}

	return ans;
}

void input() {
	int x, y;

	cin >> n >> m;
	graph.resize(n + 1);
	in.assign(n + 1 , 0);
	class_score.assign(n + 1 , 0);


	for (int i = 1; i <= n; i++)
		cin >> class_score[i];

	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		graph[x].push_back(y);
		in[y]++;
	}
}

int main() {

	input();
	vector<int> ans =  KahnAlgo();

	if ((int)ans.size() != n) cout << -1 << "\n";
	else {
		for (int node : ans)
			cout << node << " ";
		cout << "\n";
	}

	return 0;
}
```
