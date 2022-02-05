## Min Max Array Splitting

Given an array of $N$ positive integers. Your task is to divide it into $K$ segments so that the maximum sum on the segment is the minimum possible.

### Constraints

$0 \leq K \leq N \leq 10^{5}$
$1 \leq a_{i} \leq 10^{9}$

### Input

$N \quad K$
$ a_1 \quad a_2 \quad ... \quad a_N $

### Output

Print one integer, minimum possible maximum sum on segment.

### Example

Input

```
10 4
1 3 2 4 10 8 4 2 5 3
```

Output

```
12
```

$1st$ Segment is $[0,3]$ , so sum is 10
$2nd$ Segment is $[4,4]$ , so sum is 10
$3rd$ Segment is $[5,6]$ , so sum is 12
$4th$ Segment is $[7,9]$ , so sum is 10

Therefore the minimum possible maximum sum of segments is $12$.

### Test cases

**Edge cases**

```
0 0
Output will be 0
```

```
5 0
1 2 3 4 5
Output will be 0
```

**Large input test cases**

```
100000 1
1000000000 1000000000 100000000 ... (100000 times)

If long is not used then it will cause oveflow.
```

### Hints

- If I give you a number of $x$ can you determine if we can split array into $K$ segments such that maximum of each segment's sum will be $ \leq x$ ?

- If to obtain a number $ \leq x$ we have to split the array into $K+1$ segments then what should we do ?

- If to obtain a number $ \leq x$ we have to split the array into $K-1$ segments then what should we do ?

### Editorial

**Prerequisites**

- Binary Search

**Optimal Solution $O(N\log{sum(a_{i})})$**

Let us assume we are given a number $x$ and we need to split - To obtain an answer $ \leq x$ we have to split the array into minimum number of segments. To implement this check the algorithm below

- We iterate from left to right and keep a $sum$ variable which stores the sum of current subarray.
- If adding the current element to sum exceeds $x$ then we increase the subarray count (make a split) and change the value of sum to $0$.
- Else we keep adding the value to sum.

So now after splitting the segment two cases arise

- **Number of segments $\leq K$** : In this case $x$ might be a valid answer and we can check for even smaller values.
  **Reason:** Every time we split a segment we reduce its sum. So we can split the segments and the value will always be $\leq x$.

- **Number of segments $> K$** : Then $x$ is not a valid answer and must check for larger value.
  **Reason:** Every time we combine a segment we increase the sum. As each segment has value $\leq x$, on combining its value will become greater than $x$.

Now all that remains is to efficiently find the value of $x$. And it can be easily done through binary search.

- If for certain $x$ number of segments $\leq K$ then we store $x$ as answer and check for smaller values

- Else we check for larger values

**Things to keep in mind**

- Whenever you are using binary search with large values. use the code below to prevent overflow.

```cpp
int mid = lo + (hi-lo)/2;
```

**Resource links**

- [Great Blog on Binary Search](https://www.topcoder.com/thrive/articles/Binary%20Search)

**Similar problems**

- [Allocate minimum number of pages](https://www.interviewbit.com/problems/allocate-books/)
- [Aggresive cows](https://www.spoj.com/problems/AGGRCOW/)
- [Koko eating bananas](https://leetcode.com/problems/koko-eating-bananas/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

bool can_split_into_atmost_K_segments(vector<long long>&a,
                                      long long max_sum_of_each_segment,
                                      int k
                                     ) {

	int num_of_segments = 1;
	long long sum_of_each_segment = 0;


	for (long long e : a) {
		if (e > max_sum_of_each_segment) return false;

		if (sum_of_each_segment + e > max_sum_of_each_segment) {
			sum_of_each_segment = 0;
			num_of_segments++;
		}

		sum_of_each_segment += e;
	}

	return num_of_segments <= k;

}

int main() {
	int n, k;
	cin >> n >> k;

	if (n == 0 || k == 0) {
		cout << 0 << "\n";
		return 0;
	}

	vector<long long> a(n);

	for (auto&e : a)
		cin >> e;


	long long lo = 0 , hi = 1e17;
	long long ans = 0;

	while (lo <= hi) {
		long long mid = lo + (hi - lo) / 2;

		if (can_split_into_atmost_K_segments(a , mid , k)) ans = mid , hi = mid - 1;
		else lo = mid + 1;
	}

	cout << ans << "\n";

	return 0;
}
```
