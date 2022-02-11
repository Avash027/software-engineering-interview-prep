## Counting Progressions

You are given $N$ integers $a_i$, and an integer $k$.
Find the **number of geometric progressions of length $3$ with a common ratio $k$** are present in the array.

Note that the indices of the three integers in the G.P. should be strictly increasing. If $a_x , a_y , a_z$ are in G.P. then $x > y > z$.

A geometric progression with common ratio is a sequence of number of the form $b·k^0, b·k^1, ..., b·k^{r - 1}$

### Constraints

$1 \leq N,k \leq 10^6$
$-10^9 \leq a_i \leq 10^9$

### Input

$N \quad k$
$a_1 \quad a_2 \quad \dots \quad a_N$

### Output

Print one integer, **number of geometric progressions of length $3$ with a common ratio $k$**.

### Example

Input

```
4 3
1 1 2 6
```

Output

```
1
```

Three G.P. are:

$(1_0 , 2_2 , 6_4)$
$(1_1 , 2_2 , 6_4)$

### Test cases

**Edge cases**

```
4 4
1 6 3 4

Output: 0
```

```
1 1
1

Output: 0
```

```
2 2
1 2

Output: 0
```

```
3 1
1 1 1

Output: 1
```

```
5 4
2 2 8 8 32

Output: 4
```

### Hints

- Notice that we need only 3 elements.
- Each element in the G.P. must be divisibe by $k$.
- If I give you the middle element of the G.P., let's say $x$, then what else do you need to find the all the G.P.s having $x$?

### Editorial

**Prerequisites**

- Basic hashmap

**Optimal Solution $O(N)$**

First let's have a brief look at the naive solution. We iterate $i$ from $1$ to $N-2$.

We will consider the middle element of the G.P. As we need to find G.P.s of length $3$, so we will consider only one element back and one element ahead.

For each $i$

- If $a[i]\%k \neq 0$ then we will not consider this element
- We will iterate $j$ from $0$ to $i-1$ and count the number of occurence of $a[i]/k$. (let's say $cnt_1$)
- We will iterate $k$ from $i+1$ to $N-1$ and count the number of occurence of $a[i]*k$. (let's say $cnt_2$)

The **nummber of possible G.P.s for index $i$ will be $cnt_1* cnt_2$.**

This solution will result in a TLE. So we make a minor optimization.

Instead of

- Iterating from $0$ to $i-1$ we can have a prefix array.
  **$pref[x] = $ Number of occurence of $x$ from $0$ to $i-1$**
- Iterating from $i+1$ to $N-1$ we can have a suffix array.
  **$suf[x] = $ Number of occurence of $x$ from $i+1$ to $N-1$**

So, for each index $i$ we can caluclate the number of G.P.s in $O(1)$ time complexity

$ans_i$ = $pref[a_i/k] * suf[a_i*k]$

**Time complexity using Map(C++)**: $O(N\log{N})$
**Time complexity using Unordered Map(C++)**: $O(N)$\*
**Space complexity**: $O(N)$

**Things to keep in mind**

- \*In C++, only use unordered_map if the time limit is too tight. For some case insertion in unordered_map can have the worst complexity of $O(N)$. You can refer to blog in the resource link.

**Resource links**

- [Blowing up unordered map in C++](https://codeforces.com/blog/entry/62393)
- [Map in c++](https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/)
- [Map in JAVA](https://www.javatpoint.com/java-hashmap)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;


int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);

	int n, k;
	long long ans = 0;
	cin >> n >> k;

	vector<long long> a(n);
	map<long long, int> suffix;
	map<long long, int> prefix;

	for (auto&e : a) {
		cin >> e;
		suffix[e]++;
	}

	for (int i = 0; i < n; i++) {
		suffix[a[i]]--;

		if (a[i] % k == 0)
			ans += 1LL * prefix[a[i] / k] * suffix[a[i] * k];

		prefix[a[i]]++;
	}


	cout << ans << "\n";

	return 0;
}
```
