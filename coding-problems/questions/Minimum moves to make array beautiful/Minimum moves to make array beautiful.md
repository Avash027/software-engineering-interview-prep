## Minimum moves to make array beautiful

Given an array of $N$ positive integers. An array is called **beautiful** if it is non-decreasing i.e.,
$a_{i-1} \leq a_i \quad for \quad 1 \leq i < N$

In one move you can select any element from the array and replace it with any positive integer.

You have to find **minimum** moves to make the array beautiful.

### Constraints

$0 \leq N \leq 10^{5}$
$1 \leq a_{i} \leq 10^{6}$

### Input

$N$
$ a_1 \quad a_2 \quad ... \quad a_N $

### Output

Print one integer i.e., the minimum number of moves required to make array beautiful.

### Example

Input

```
5
6  2  5  7  1
```

Output

```
2
```

We can change $1$st element to 1
We can change $7$th element to 10.

After making moves we have array

```
1 2 5 7 10
```

Which is increasing, so minimum number of moves required is $2$.

### Test cases

**Edge cases**

```
0

Output shall be 0
```

```
1
1

Output shall be 0
```

```
5
1 1 1 1 1

Output shall be 0
```

```
5
5 4 3 2 1

Output shall be 4
```

**Large input test cases**

```
100000
100001 100000 9999 9998 9997 ... 1 (100000 times)

Output shall be 9999
```

### Hints

- Notice that we are asked to make the array **non-decreasing**.
- If the problem was to delete minimum number of elements to make the array beautiful then can you think of solution ?
- If we find the longest non-decreasing subsequence then can you use it to find the minimum moves.

### Editorial

**Prerequisites**

- Dynamic programming
- Basic greedy
- Binary Search (Concept of upper bound)

**Optimal Solution $O(N\log{N})$**

If we have a non-decreasing subsequence present in array then we do not need to change it, but we have to change rest of the elements to make the array non-decreasing. As we want to make the minimum number of moves so, it is always optimal to pick the longest subsequence.

Therefore, the minimum number of moves to make the array non-decreasing = **$N - LNDS(Array)$**, where $LNDS(Array)$ is the length of the Longest Non-Decreasing Subsequence of the array.

Let's try to visualize it with an example

Suppose we have an array,

$[13,12,11,1,6,7,2,8]$

In this case the $LNDS = [1,6,7,8]$, so we have to change rest of the element i.e., 4 elements.

So the final array should look like,

$[1,1,1,1,6,7,7,8]$

Now all that remains is to find $LNDS$ of array. The constraints won't allow for $O(N^2)$ algorithm to find $LNDS$. So we have to use $O(N\log{N})$ solution.

The algorithm to find longest non-decreasing subsequence is given below:

- We keep an array $Y$ to store the subsequence
- For each $a_i \quad for \quad 0 \leq i < N$

  - If $ a_i \geq $ last element of $Y$ then we append this to $Y$. (This means that the current element can be a part of $LNDS$).

  - If $ a_i <$ last element of $Y$ then we cannot append it. But we can find the smallest element in $Y$ which is $> a_i$ and replace it with $a_i$. As $Y$ is non-decreasing we can find the desired element in $O(\log{N})$ time complexity.

**Resource links**

- [Upper bound implementation](https://www.geeksforgeeks.org/implementing-upper_bound-and-lower_bound-in-c/)
- [All methods to solve the Longest increasing subsequence problem](https://cp-algorithms.com/sequences/longest_increasing_subsequence.html)

**Related problems**

- [Minimum Operations to Make the Array K-Increasing](https://leetcode.com/problems/minimum-operations-to-make-the-array-k-increasing/)
- [Find the Longest Valid Obstacle Course at Each Position](https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/)
- [Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;


int longest_non_decreasing_subsequence(vector<int>&a) {
	vector<int> lnds;

	for (int e : a) {
		if (lnds.size() == 0 || e >= lnds.back())
			lnds.push_back(e);
		else {
			auto index_to_replace = upper_bound(lnds.begin(), lnds.end() , e) - lnds.begin();
			a[index_to_replace] = e;
		}
	}

	return (int)lnds.size();
}

int main() {

	int n;
	cin >> n;

	if (n == 0) {
		cout << 0 << "\n";
		return 0;
	}

	vector<int> a(n);

	for (int&e : a)
		cin >> e;

	int minimum_moves = n - longest_non_decreasing_subsequence(a);

	cout << minimum_moves << "\n";

}
```
