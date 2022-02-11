## Count division

You are given an array of $N$ integers. You have to count the number of ways to split the array into three contiguous subarrays such that the sum of each subarray is same.

**Note :** Each element in the array must belong to any one of the subarray.

### Constraints

$1 \leq N \leq 10^6$
$1 \leq a_i \leq 10^9$

### Input

$N$
$a_1 \quad a_2 \quad a_3 \quad \dots \quad a_N$

### Output

Print one integer, the number of ways to split the array into three contiguous subarrays such that the sum of each subarray is same.

### Example

Input

```
5
1 2 3 0 3
```

Output

```
2
```

The two ways to divide the array are:

- $[1,2]$, $[3,0]$, $[3]$
- $[1,2]$, $[3]$, $[0,3]$

Input

```
4
0 1 -1 0
```

Output

```
1
```

### Test cases

**Edge cases**

```
1
1

Output: 0
```

```
2
3 3

Output: 0
```

```
3
1 2 5

Output: 0
```

```
3
1 1 1

Output: 1
```

```
4
3 3 1 2

Output: 1
```

### Hints

- Is there any case where it is impossible to divide the array?
- If the sum of the array is $S$ then what should be the sum of the three subarrays.
- Suppose at index $i$ I have a prefix sum $S/3$, what else do we need to find the number of subarrays?

### Editorial

**Prerequisites**

- Prefix sum
- Basic dynamic programming

**Optimal Solution $O(N)$**

**Things to keep in mind**

First we notice that if sum of all elements is equal $S$ then sum of each of three parts is equal to $S/3$. Therefore, if S is not divided by 3 — then answer is $0$.

Now let's divide the array into three parts:

- Prefix array with sum $S/3$: $[0,i]$
- Middle array with sum $S/3$: $[i+1,k]$
- Suffix array with sum $S/3$: $[k+1,N-1]$

Now we can store the suffix sum, but it will have a time complexity of $O(N^2)$. So we can use dynamic programming to optimize it.

**$dp[i]$ = number of subarrays from $i$ to $n-1$ which has a sum $S/3$.**

Now let's look at the algorithm.

- We iterate the left pointer from $0$ to $N-2$.
- If the $sum_{pref} \neq S/3$ we keep moving
- if $sum_{pref} == S/3$ then we have found the prefix array.
  We also have the $dp[]$ which whill give us the number of suffix array with sum $S/3$.

  So the **$answer_i = dp[i+2]$**
  **Reason :** We use $i+2$ because the middle array must have a length $\geq$ 1, and we want to count the maximum number of suffix arrays.
  Also, we can be sure that the middle array has a sum $S/3$ because,

  $pref_i + mid + suf = S$
  $pref_i = S/3 \ \ and \ \ suf = S/3$
  **$mid = S/3$**

**Time complexity :**$O(N)$
**Space complexity :**$O(N)$

**Resources**

- [Aditya verma DP series](https://www.youtube.com/watch?v=nqowUJzG-iM&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)

- [Striver DP series](https://www.youtube.com/playlist?list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {

	int n;
	long long sum = 0 , cur_sum = 0, pref_sum = 0;
	long long ans = 0;

	cin >> n;
	vector<long long> a(n);
	vector<long long> suffix(n , 0);

	for (auto&e : a) {
		cin >> e;
		sum += e;
	}

	if (sum % 3 != 0) {
		cout << 0 << "\n";
		return 0;
	}


	for (int i = n - 1; i >= 0; i--) {
		cur_sum += a[i];

		if (i == n - 1)
			suffix[i] = cur_sum == sum / 3;
		else
			suffix[i] = suffix[i + 1] + (long long)(cur_sum == sum / 3);
	}



	for (int i = 0; i < n - 2; i++) {
		pref_sum += a[i];

		if (pref_sum == sum / 3)
			ans += suffix[i + 2];
	}

	cout << ans << "\n";

	return 0;
}

```
