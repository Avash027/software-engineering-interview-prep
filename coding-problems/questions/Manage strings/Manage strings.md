## Manage Strings

You are given $N$ strings consisting of lowercase English letters. You want to sort them in lexicographical order, but you are not allowed to swap any of them. The only operation you are allowed is to **reverse any of them**.

To reverse the $i$-th string you need to spend $c_i$ units of energy. Find the minimum amount of energy you have to spend in order to have strings sorted in **lexicographical order**. If it is not possible to arrange the strings in order print $-1$.

String $X$ is lexicographically smaller than String $Y$ if,

- $X_i < Y_i$ for $0 \leq i < min(|X| , |Y|)$
- $|X| < |Y|$ and $X_i = Y_i$ for all $i$.

### Constraints

$1 \leq N \leq 2*10^4$
$1 \leq |s_i| \leq 100$
$1 \leq c_i \leq 10^9$

### Input

$N$
$s_1 \quad c_1$
$s_2 \quad c_2$
$\vdots$
$s_N \quad c_N$

### Output

Print one integer, minimum amount of energy spent to have strings sorted in **lexicographical order**. If it is not possible to arrange the strings in order print $-1$.

### Example

```
2
dbac 3
ccef 5
```

```
3
```

Explaination

- If we reverse $dbac$ then the strings will be sorted, and it will cost $3$ units.

- If we reverse $ccef$ then the strings will be sorted, and it will cost $5$ units.

So minimum cost will be $3$

```
2
zzz 2
aaa 2
```

```
-1
```

Explaination

Now matter what we do the strings will never be sorted.

### Test cases

**Edge cases**

```
1
a 1

Output: 0
```

```
3
a 1
b 1
c 3

Output: 0
```

```
3
c 1
b 1
a 1

Output: -1
```

```
3
xx 1
yx 5
xz 2

Output: 2
```

```
3
xx 1
yx 1
xz 5

Output: 1
```

### Hints

- What will be the optimal answer when there is only 1 string?
- There are two possible things we can do to a string. What are those?
- We can either reverse a string or leave it as long as it makes the strings sorted.
- Can you solve this problem in $O(|s|*2^N)$?
- Can you optimize the above solution? Do you feel we are calculating the same values again and again?

### Editorial

**Prerequisites**

- Basic Dynamic Programming

**Optimal Solution $(|s|*N)$**

So for every string we can make two moves.

- Reverse the string (if it makes the strings sorted)
- Do not reverse the string (if it makes the strings sorted)

So we for each string $s_i$ in the list we need to keep two states

- Minimum amount of energy required if we reverse $s_i$
- Minimum amount of energy required if we don't reverse $s_i$

Then we can use these states the to calculate minimum values for next string.

**$dp[i][1]$ = Minimum amount of energy required to sort first $i$ strings if we don't reverse $s_i$**

**$dp[i][0]$ = Minimum amount of energy required to sort first $i$ strings if we do reverse $s_i$**

**Recurrence relation**

We have to consider $4$ cases.
_Also remember we will only consider a case if after performing operations, strings are sorted._

- We don't reverse $s_i$ and $s_{i-1}$
  **$dp[i][1] = min(dp[i-1][1] , dp[i][1])$**

- We only reverse $s_{i-1}$
  **$dp[i][1] = min(dp[i-1][0] , dp[i][1])$**

- We only reverse $s_i$
  **$dp[i][0] = min(dp[i-1][1]+c_i , dp[i][0])$**

- We reverse both $s_i$ and $s_{i-1}$
  **$dp[i][0] = min(dp[i-1][0]+c_i , dp[i][0])$**

If all the $4$ cases fail, then there is no way to sort the strings.

**Time complexity :** $O(|s|*N)$
**Space complexity :** $O(N)$

**Resource links**

- [Aditya verma DP series](https://www.youtube.com/watch?v=nqowUJzG-iM&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)

- [Striver DP series](https://www.youtube.com/playlist?list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY)

- [string::compare in c++](https://www.geeksforgeeks.org/stdstringcompare-in-c/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;


struct Element
{
	string word;
	long long cost;
};

const long long INF = 1e11;

int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);

	int n;
	cin >> n;

	vector<Element> a(n);
	vector<vector<long long>> dp(n , vector<long long>(2 , INF)); //Any large value will be good

	for (auto&e : a)
		cin >> e.word >> e.cost;

	//Defining the base case

	dp[0][1] = 0;
	dp[0][0] = a[0].cost;


	for (int i = 1; i < n; i++) {

		string cur = a[i].word;
		string prev = a[i - 1].word;

		string cur_reverse = a[i].word;
		string prev_reverse = a[i - 1].word;

		reverse(cur_reverse.begin(), cur_reverse.end());
		reverse(prev_reverse.begin(), prev_reverse.end());


		//1st Case
		if (cur.compare(prev) >= 0)
			dp[i][1] = min(dp[i - 1][1] , dp[i][1]);

		//2nd Case
		if (cur.compare(prev_reverse) >= 0)
			dp[i][1] = min(dp[i - 1][0], dp[i][1]);

		//3rd Case
		if (cur_reverse.compare(prev) >= 0)
			dp[i][0] = min(dp[i - 1][1] + a[i].cost , dp[i][0]);

		//4th Case
		if (cur_reverse.compare(prev_reverse) >= 0)
			dp[i][0] = min(dp[i - 1][0] + a[i].cost , dp[i][0]);
	}

	long long ans = min(dp[n - 1][0] , dp[n - 1][1]);

	if (ans >= INF) ans = -1; //There is no way to sort the strings

	cout << ans << "\n";

	return 0;
}
```
