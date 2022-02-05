## Prime game

John and Doe are playing a game. Initially then have an integer $n$. They take turns in playing the game and John starts first. At every move the player can subtract any prime factor of the number (1 is not a prime).

A player wins if the other player cannot move.

Print **YES** if and only if John wins the game else print **NO**. Consider both the player play optimally.

### Constraints

$0\le N\le{10}^5$

### Input

```
N
```

### Output

Print **YES** if and only if John wins else print **NO**.

### Example

Input

```
6
```

Output

```
YES
```

John subtracts $2$ from $6$ so they are left with $4$
Then Doe subtracts $2$ from $4$ so they are left with $2$
Then John subtracts $2$ from $2$ so they are left with $0$
Now Doe cannot make any move, hence John wins

### Test cases

**Edge cases**

- ```
  1
  ```

  ```
  Correct answer: NO
  ```

  > 1 is not prime nor composite and it has no prime factor so it is a losing number

- ```
    7
  ```

  ```
  Correct answer: YES
  ```

**Large input test cases**

- ```
  9931
  ```

- ```
  100000
  ```

### Hints

- Try to get the answer for $n$=$2$,$3$,$4$,$5$. Do you see any pattern?
- Are we recalculating same values when we find the answer for $n=2,3,4,5$? If yes how can we optimize it ?
- If we are given the results of n-1 matches. Can we use it to find the result of nth match?

### Editorial

**Prerequisites**

- Dynamic Programming
- Basic number theory to find prime factors

**Optimal Solution $O(n\sqrt{n})$**

Our aim is to find if the player starting the game (in this case John) with n stones can win.
So to ensure John to win the player stating the game with $n - y$ should always lose. (Here y is any prime factor of n).
As you can see that we are are dependent on the outcomes of the previous $n$ and therefore we must store it.

Let us look at an example

- For $n=0$ John cannot make a move so he looses.
- For $n=1$ John cannot make a move so he looses.
- For $n=2$ John can subtract 2 from the n. After subtracting we check what is left ($n-y$). Here it is 0, As Doe cannot make any move he loses and John wins
- For $n=3$ John can subtract 3 from the n. Here it is 0, As Doe cannot make any move he loses and John wins
- For $n=4$ John can subtract only $2$, so now $2$ is left.From our previous result we know player at 2 can win by subtracting 2 so Doe wins and John loses
- For $n=5$ John can subtract $5$ and win
- For $n=6$ John can subtract $2$ or $3$. Now we want the other player to land on a losing number. If we subtract $3$ then Doe will win as $3$ is a winning number. So John can subtract $2$ and win.

**Recurrence relation**

```
dp[i] = true (if John wins the ith else it will be false)
dp[0] = dp[1] = false
dp[i] = !dp[i - p1] || !dp[i-p2] ... !dp[i-pn] (p are the prime factor of i)
```

**Time complexity**

It will take at most $O(\sqrt{n})$ to calculate prime factors and we are interating from 1 to n.

Time Complexity: $O(n\sqrt{n})$

**Resource links**

- [Aditya verma DP series](https://www.youtube.com/watch?v=nqowUJzG-iM&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)

- [Striver DP series](https://www.youtube.com/playlist?list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY)

- [Prime factorization](https://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/)

- [Intermmediate number theory](https://cp-algorithms.com/#algebra)

**Related problems**

- [Stone game IV](https://leetcode.com/problems/stone-game-iv/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;


vector<int> getPrimeFactors(int n) {
	vector<int> prime_factors;

	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			prime_factors.push_back(i);
			while (n % i == 0) n /= i;
		}
	}

	if (n > 1) prime_factors.push_back(n);

	return prime_factors;
}

int main() {

	int n;
	cin >> n;

	vector<bool> dp(n + 1, false);


	for (int i = 2; i <= n; i++) {
		vector<int> prime_factors = getPrimeFactors(i);

		for (int factor_of_i : prime_factors)
			dp[i] = dp[i] or !dp[i - factor_of_i];//Notice the negation operater here
	}


	if (dp[n]) cout << "YES\n";
	else cout << "NO\n";

    return 0;
}
```
