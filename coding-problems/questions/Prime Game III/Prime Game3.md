## Prime game III

John and Doe are playing a game. Initially then have an integer $n$. They take turns in playing the game and John starts first. At every move the player can subtract any common prime factor of the number $x$ and $n$ (1 is not a prime).

A player wins if the other player cannot move.

Print **YES** if and only if John wins the game else print **NO**. Consider both the player play optimally.

### Constraints

$0\le N\le{10}^6$
$2 \leq x \le 10^{17}$

### Input

$N \quad x$

### Output

Print **YES** if and only if John wins else print **NO**.

### Example

Input

```
6 3
```

Output

```
NO
```

$3$ is common prime factor of $6$ and $3$, John subtracts $3$ from $6$, so they are left with $3$
Then Doe subtracts $3$ from $3$, so they are left with $0$
Now John cannot make any move, hence Doe wins

### Test cases

**Edge cases**

```
1 100

Output: NO
```

```
7 3

Output: NO
```

```
7 7

Output: YES
```

```
0 1

Output: NO
```

**Large input test cases**

```
10000000 100000000000000000
```

```
99999 900000000009
```

### Hints

- Try to get the answer for $n$=$2$,$3$,$4$,$5$. Do you see any pattern?
- Are we recalculating same values when we find the answer for $n=2,3,4,5$? If yes how can we optimize it ?
- Notice that $x$ can be very large.
- Do you think we can use $gcd$ to find common factors?
- If we are given the results of $n-1$ matches, can we use it to find the result of nth match?

### Editorial

**Prerequisites**

- Dynamic Programming
- Basic number theory to find prime factors

**Optimal Solution $O(N\log{min(x,N)})$**

Our aim is to find if the player starting the game (in this case Alex) with n stones can win.
So to ensure Alex to win the player stating the game with $n - y$ should always lose. (Here y is any prime factor of n). So we can divide each $i$ from $0 \leq i \leq N$ into two categories

- Winning number (If player starts here he will always win)
- Losing number (If player starts here he will always lose)

So for each $i$ if there is any move to make it a winning number then we take that move.

As you can see that we are dependent on the outcomes of the previous $n$, and therefore we must store it.

Now all that remains is to find the common prime factors of each $i$ and $x$. Here we will make $2$ important observations.

- Common prime factors of $x$ and $i$ = Common prime factors of $gcd(x,i)$
- $gcd(x,i) \leq min(x,i) \leq 10^6$, so we can use sieve to find all prime factors for $x$ and $i$

**Recurrence relation**

$dp[i]$ = $true$ (if John wins the $i$th else it will be false)
$dp[0]$ = $dp[1]$ = $false$
$dp[i]$ = $dp[i - cp_1] \quad || \quad !dp[i-cp_] \quad ... \quad !dp[i-cp_k]$
(cp is the common prime factor of $i$ and $x$)

Pre-computation of $spf$ takes $O(N\log\log{N})$
Calculating $gcd$ for all $i$ takes $O(N\log{min(x,N)})$
Calculating prime factor for all $i$ takes $O(N\log\log{min(x,N)})$

**Time complexity :**$O(N\log{min(x,N)})$
**Space complexity :** $O(N)$

**Resource links**

- [Aditya Verma DP series](https://www.youtube.com/watch?v=nqowUJzG-iM&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)

- [Striver DP series](https://www.youtube.com/playlist?list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY)

- [Prime factorization in O(logN)](https://www.geeksforgeeks.org/prime-factorization-using-sieve-olog-n-multiple-queries/)

- [Euclidean GCD (Basic)](https://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/)

**Related problems**

- [Stone game IV](https://leetcode.com/problems/stone-game-iv/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

vector<int> calculate_spf(int n) {
	vector<int> spf(n);

	for (int i = 1; i < n; i++)
		spf[i] = i;

	for (int i = 4; i < n; i += 2)
		spf[i] = 2;

	for (int i = 3; i * i < n; i++) {
		if (spf[i] != i) continue;

		for (int j = i * i; j < n; j += i)
			if (spf[j] == j)
				spf[j] = i;
	}

	return spf;
}


vector<int> calculate_factors(int n , vector<int>& spf) {
	vector<int> factors;

	while (n != 1) {
		factors.push_back(spf[n]);
		n /= spf[n];
	}

	return factors;
}

long long gcd(long long a , long long b) {
	if (a == 0)
		return b;
	return gcd(b % a, a);
}


int main() {
	int n;
	long long x;
	cin >> n >> x;


	vector<int> spf = calculate_spf(n + 1);
	vector<bool> dp(n + 1, false);


	for (int i  = 2; i <= n; i++) {

		int g = (int)gcd(i, x);
		vector<int> common_factors = calculate_factors(g , spf);

		for (int cp : common_factors)
			dp[i] = dp[i] || !dp[i - cp];

	}


	if (dp[n]) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}
```
