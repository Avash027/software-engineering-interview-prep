## Prime game II

Alex and Jones are playing a game. Initially then have an integer $N$. They take turns in playing the game and Alex starts first. At every move the player can subtract either the smallest prime factor or the largest prime factor.

A player wins if the other player cannot move.

Print **YES** if and only if Alex wins the game else print **NO**. Consider both the player play optimally.

### Constraints

$0\le N\le{10}^6$

### Input

```
N
```

### Output

Print **YES** if and only if Alex wins else print **NO**.

### Example

Input

```
8
```

Output

```
NO
```

Alex subtracts $2$ from $8$, so they are left with $6$
Then Jones subtracts $2$ from $6$, so they are left with $4$
Then Alex subtracts $2$ from $4$, so they are left with $2$
Then Jones subtracts $2$ from $2$, so they are left with $0$
Now Alex cannot make any move, hence Jones wins.

### Test cases

**Edge cases**

```
 1

 Output: NO
```

```
0

Output: NO
```

```
7

Output: YES
```

**Large input test cases**

```
999983

Output: YES
```

```
1000000
```

### Hints

- Try to get the answer for $n$=$2$,$3$,$4$,$5$,$6$. Do you see any pattern?
- Did you see any pattern when trying to find the answer for $n = 6$?
- If we are given the results of $n-1$ matches. Can we use it to find the result of nth match?
- Notice that the $n$ can be large.
- Can we precompute the smallest prime factor and the largest prime factor

### Editorial

**Prerequisites**

- Dynamic Programming
- Sieve of Eratosthenes.

**Optimal Solution $O(N\log{N})$**

Let,
$spf_i$ = Smallest prime factor of $i$.
$hpf_i$ = Largest prime factor of $i$.

Our aim is to find if the player starting the game (in this case Alex) with n stones can win.
So to ensure Alex to win the player stating the game with $n - y$ should always lose. (Here y is any prime factor of n). So we can divide each $i$ from $0 \leq i \leq N$ into two categories

- Winning number (If player starts here he will always win)
- Losing number (If player starts here he will always lose)

So for each $i$ if there is any move to make it a winning number then we take that move.

As you can see that we are dependent on the outcomes of the previous $n$, and therefore we must store it.

Let us look at an example

- **For $n=0$**
  $spf_0 = X$
  $hpf_0 = X$
  Alex cannot make a move, so he looses.
- **For $n=1$**
  $spf_1 = X$
  $hpf_1 = X$
  Alex cannot make a move, so he looses.
- **For $n=2$**
  $spf_2 = 2$
  $hpf_2 = 2$
  Alex can subtract $2$ from the $N$. After subtracting we check what is left ($n-y$). Here it is 0, As Jones cannot make any move he loses and Alex wins.
- **For $n=3$** Alex wins.
- **For $n=4$** Alex loses.
- **For $n=5$** Alex wins.
- **For $n=6$**
  $spf_6 = 2$
  $hpf_6 = 3$
  Alex can subtract $2$ or $3$. Now we want the other player to land on a losing number. If we subtract $3$ then Jones will win as $3$ is a winning number. So Alex can subtract $2$ and win and Jones will land on $4$. There is no way Jones can win, so Alex wins.

Now all that remains is to find the $spf_i$ and $hpf_i$ for each $i$. The naive way will have a time complexity of $O(\sqrt{N})$, so the total time complexity will be $O(N\sqrt{N})$ which is too slow.

Now we can modify Sieve of Eratosthenes to find the smallest and largest prime factor.

Algorithm to find the $spf$ is given below

- Iterate $i$ from $2$ to $N$.
- If $i$ is not a prime then continue.
- If $i$ is prime then $spf$ all the multiples of $i$ will be $i$.

Algorithm to find the $hpf$ is given below

- We start with number $x$.
- We divide $x$ with $spf_x$ and store the result
- The largest of all the results is $hpf_x$.

**Recurrence relation**

$dp[i]$ = $true$ (if Alex wins the $i$th else it will be false)
$dp[0]$ = $dp[1]$ = $false$ (Base case)
$dp[i]$ = $!dp[i - spf[i]] \quad || \quad !dp[i-hpf[i]]$

<br />

Pre-computation of $spf$ takes $O(N\log\log{N})$
Calculating $hpf$ for all $i$ takes $O(N\log{N})$

**Time complexity :** $O(N\log{N})$
**Space complexity :** $O(N)$

**Resource links**

- [Aditya Verma DP series](https://www.youtube.com/watch?v=nqowUJzG-iM&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)

- [Striver DP series](https://www.youtube.com/playlist?list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY)

- [Prime factorization in O(logN)](https://www.geeksforgeeks.org/prime-factorization-using-sieve-olog-n-multiple-queries/)

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


int calculate_hpf(int n , vector<int>& spf) {
	int hpf = 0;

	while (n != 1) {
		hpf = max(hpf , spf[n]);
		n /= spf[n];
	}

	return hpf;
}


int main() {
	int n;
	cin >> n;


	vector<int> spf = calculate_spf(n + 1);
	vector<bool> dp(n + 1, false);

	for (int i  = 2; i <= n; i++) {
		int hpf = calculate_hpf(i, spf);


		dp[i] = (!dp[i - spf[i]])  || (!dp[i - hpf]);
	}


	if (dp[n]) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}
```
