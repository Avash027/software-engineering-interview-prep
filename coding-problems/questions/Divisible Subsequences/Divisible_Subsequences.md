## Divisible Subsequences

You are given two integers $n$ and $k$. You have to find the number of subsequences of length $k$ that follow the rules below

- $1 \leq a_i \leq n$, for all $1 \leq i \leq k$
- $a_i \leq a_{i+1}$, for all $1 \leq i \leq k-1$
- $a_{i+1}$ is divisible by $a_i$, for all $1 \leq i \leq k-1$.

As the answer can be rather large print it modulo $10^9 + 7$.

### Constraints

$1\leq n\leq 1000$
$1\leq k\leq 1000$

### Input

$m \quad k$

### Output

Print one integer, the number of valid subsequences modulo $10^9+7$.

### Example

Input

```
3 2
```

Output

```
5
```

Explanation

The $5$ subsequences are:

$[1,1]$, $[1,2]$, $[1,3]$, $[2,2]$, $[3,3]$.

### Test cases

**Edge cases**

```
1 1

Output: 1
```

```
2 2

Output: 3
```

```
1000 1

Output: 1000
```

```
1 1000

Output: 1
```

```
6 4

Output: 39
```

**Large input test cases**

```
1000 1000
```

### Hints

- Notice the constraints of $n$ and $k$. Can you make a 2-D array?
- Try to solve the for $n=3$ and $k=3$.
- When we solve for $n=3$ can we use the values of $n=2$?
- If we choose $x$ as $b_i$ then we have to choose multiple of $x$ for $b_{i+1}$. So you can see that the previous values affect the choice of our current value.
- Try to store answer for all $n$ for each size of subsequence.

### Editorial

**Prerequisites**

- Basic dynamic programming
- Basic number theory

**Optimal Solution**

Let's try to build a table for $n=3$ and $k=3$ to find the answer. Here the column would represent the length of subsequence and row will represent the value we are taking at that index.

|     | 1   | 2       | 3      |
| --- | --- | ------- | ------ |
| 1   | 1   | 1       | 1      |
| 2   | 1   | 2       | 2      |
| 3   | 1   | 3 [2+1] | 3[2+1] |

- For $k=1$ there is only $1$ way to make subsequence for each $n$.

- For $k=2$

  - If we pick $1$ for $2nd$ position then we can only pick $1$ for the first position. So there is only $1$ way to make subsequence
  - If we pick $2$ for $2nd$ position then we can pick $1$ and $2$ for the first position. So there are $2$ ways to make subsequence.
  - Same as $2$.

- For $k=3$
  - If we pick $1$ then there is only $1$ way to make subsequence
  - Now if we pick $2$ there are two options, $1$ and $2$ for second position. If we pick 1 (for $2nd$ position) we can make $1$ type of subsequence and if we pick $2$ we can make two type of subsequence. So in total we can make $3$ types of subsequence.
  - Same as $2$

So we are using the number of subsequences of $k-1$ length to find the answer for $kth$ length.

Now let's define a recurrence relation:

$dp[i][j]$ = number of sequences of length $i$ that ends in $j$.

Let's denote multiples of $j$ by $m_1, m_2, ..., m_l$ Then,
**$dp[i+1][m_r] += dp[i][j]\%(10^9+7) \quad$ where $1 \leq r \leq l$.**

Base case
$dp[1][j]$ = $1$ for all $1 \leq j \leq n$

Note: It takes $O(\log{n})$ to find all multiple of $x \leq n$.

**Time complexity :**$O(n*k*\log{n})$

**Space complexity :**$O(n*k)$

**Resource links**

- [Aditya Verma DP series](https://www.youtube.com/watch?v=nqowUJzG-iM&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)

- [Striver DP series](https://www.youtube.com/playlist?list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

constexpr long long MOD = 1e9 + 7;

int main() {

	int n, k;
	cin >> n >> k;

	vector<vector<long long>> dp(k + 1 , vector<long long>(n + 1 , 0));

	for (int i = 1; i <= n; i++)
		dp[1][i] = 1;


	for (int i = 1; i < k; i++) {
		for (int j = 1; j <= n; j++) {
			for (int m = j; m <= n; m += j) //This loop is to calculate all the mutliples of j
				dp[i + 1][m] = (dp[i][j] % MOD + dp[i + 1][m] % MOD) % MOD;
		}
	}

	long long sum = 0;

	for (int i = 1; i <= n; i++) {
		sum += dp[k][i];
		sum %= MOD;
	}

	cout << sum << "\n";

	return 0;
}
```
