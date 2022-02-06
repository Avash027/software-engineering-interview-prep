## Length Summation

Given an array of $n$ integers $a_i$. We say that the segment of this array $(  0 \leq l \leq r <n)$ is _good_ if the sum of elements on this segment is at most $k$. You have to find the sum of all the _good_ segments.

### Constraints

$0 \leq n \leq 10^{5}$
$0 \leq k \leq 10^{16}$
$0 \leq a_{i} \leq 10^{9}$

### Input

$n \quad k$
$ a_1 \quad a_2 \quad \dots \quad a_n $

### Output

Print one integer i.e., the sum of all good segments.

### Example

Input

```
5 7
1 3 13 2 5
```

Output

```
22
```

All segments are:

- $1$ = $1$
- $1 + 3$ = $4$
- $3$ = $3$
- $2$ = $2$
- $5$ = $5$
- $2 + 5$ = $7$

Sum = $22$

### Test cases

**Edge cases**

```
0 1000

Output will be 0
```

```
1 0
0

Output will be 1
```

```
5 0
1 2 0 3 2

Output will be 1
```

**Large input test cases**

```
100000 0
0 0 0 0 0 0 0 0 0 0 0 0 .... (100000 times)
Output will be 5000050000 which will cause integer overflow.
```

### Hints

- Can you solve it in $O(n^2)$?
- Suppose I have a subsegment $a[2,6]$ such that it's sum is grater than $k$. What are the possible ways to reduce it?
- Let's say we have a good segment of length $6$. How many good subsegments can obtain from it ?

### Editorial

**Prerequisites**

- Two pointer
- Basic mathematics

**Optimal Solution $O(N)$**

We will maintain some segment of the array (its **left** and **right** boundaries will be two pointers), as well as the sum on the current segment.

We will slowly move both boundaries of this segment to the right.

- When we move the right border one element forward, and the sum on the new segment is no more than $k$, then we can leave the left border in place.

- If we added a right element and the sum has become more than $k$, then we need to move the left border forward. And we need to keep moving it forward until the sum on the segment again becomes less than or equal to $k$.

- Once we have a longest good segment we can divide it into smaller segments. These smaller segments will always be good because, `sum of smaller segment` $\leq$ `sum of largest segment` $\leq k$.

- We can calculate the number of subsegments of a larger segment of length $X$ using the formula : $X*(X+1)/2$

**Note:** The left and right boundaries only traverse the array at most once each.

**Time Complexity :** $O(N)$
**Space Complexity :** $O(N)$

**Resource links**

- [Two pointer GFG](https://www.geeksforgeeks.org/two-pointers-technique/)

**Related problems**

- [Container with Most Water](https://leetcode.com/problems/container-with-most-water/)
- [Subarray with product less than K](https://leetcode.com/problems/subarray-product-less-than-k/)
- [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;


long long sum_of_good_segments(vector<long long> a , long long k , int n) {

	int left_boundary = 0 , right_boundary = 0;

	long long sum_of_segment = 0LL , sum_of_length_of_segments = 0;


	while (right_boundary < n) {

		sum_of_segment += a[right_boundary++];

		while (sum_of_segment > k) {// It is not a good segment so we try to reduce its size
			sum_of_segment -= a[left_boundary];
			left_boundary++;
		}

		long long lenght_of_segment = right_boundary - left_boundary;

		sum_of_length_of_segments += (lenght_of_segment * (lenght_of_segment + 1)) / 2;

	}

	return sum_of_length_of_segments;


}


int main() {
	int n;
	long long k;

	cin >> n >> k;

	if (n == 0 || k == 0) {
		cout << 0 << "\n";
		return 0;
	}

	vector<long long> a(n);

	for (auto&e : a)
		cin >> e;

	cout << sum_of_good_segments(a, k, n) << "\n";

	return 0;
}
```
