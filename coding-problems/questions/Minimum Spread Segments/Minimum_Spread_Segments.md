## Minimum Spread Segment

You are given an array of $N$ integers $a_i$. Let's say that a segment of this array $a[l..r]$ $(1≤l≤r≤N)$ is **good if the difference between the maximum and minimum elements on this segment is at most $k$.**

Your task is to find the number of different good segments.

### Constraints

$1 \leq N \leq 10^5$
$1 \leq k \leq 10^{16}$
$1 \leq a_i \leq 10^{16}$

### Input

$N \quad k$
$a_1 \quad a_2 \quad \dots \quad a_N$

### Output

Print one integer, the number of **different good segments**.

### Example

Input

```
4 3
1 2 3 4
```

Output

```
4
```

Explaination

$4$ segments are:

- $[1]$
- $[2]$
- $[3]$
- $[1,2]$

### Test cases

**Edge cases**

```
1 10000000000000000
10000000000000000

Output: 1
```

```
1 10000000000000000
1

Output: 1
```

```
1 1
10000000000000000

Output: 0
```

```
5 1
2 3 4 5 7

Output: 0
```

```
5 10
1 2 3 4 5

Output: 15
```

**Large input test cases**

```
1 1000000000000000
1 1 1 1 1 ... 1 (100000 times)

Output: 5000050000
```

### Hints

- Can you solve it in $O(n^2)$?
- Suppose in a range $[1,5]$ the difference between $min$ and $max$ is greater than $k$. How do you reduce it?
- Which data structure can you use to insert and delete and find min and max effeciently?
- Try to solve this using two pointer method.

### Editorial

**Prerequisites**

- Two pointers
- Set in C++ / TreeSet in Java
- \*Segment tree (optional)
- \*Sparse Table (optional)

**Optimal Solution**

- **$O(N\log{N})$ solution**

  Let $diff$ = maximum element in subarray - minimum element in subarray.

  We will maintain some segment of the array (its **left** and **right** boundaries will be two pointers), as well as the sum on the current segment.

  We will slowly move both boundaries of this segment to the right.

  - When we move the right border one element forward, and the $diff \leq k$, then we can leave the left border in place.

  - If we added a right element and the $diff > k$, then we need to move the left border forward. And we need to keep moving it forward until the $diff \leq k$ again.

  Two pointers always works here because once the right pointer raches an index such that $diff > k$ then no matter how right we go the $diff$ will always be greater than $k$. So we have to move the left pointer.

  There are multiple ways to find the min and max in a segment. Few methods are discussed below.
  <br/>

  - Every time we move the right pointer we add `pair(a[right],right)` in the set.
  - Every time we move the left pointer we remove `pair(a[left] , left)` from the set.
    Set keeps the element in sorted manner. So the first element in set is the minimum and the last element is maximum.
  - **Time complexity: $O(N\log{N})$**.
  - **Space complexity: $O(N)$**
    <br />

- **$O(N)$ solution**

  To write solution in $O(N)$ we can use a `minimum/maximum queue` that allows us to find the min/max in $O(1)$.

  The alogrithm is almost same as above. We insert `a[right]` in max queue and min queue. If the $diff > k$ then we remove both the extremes and update the left pointer. (Look at the implementation of clarity)

  - Check the resource link to read about it in detail.

**Things to keep in mind**

- Notice that the constraints are too large so use `long long`.
- When working with set in C++ always check if the iterator is `out_of_bounds` or not.

**Resource links**

- [Min/Max Queue](https://cp-algorithms.com/data_structures/stack_queue_modification.html#finding-the-minimum-for-all-subarrays-of-fixed-length)
- [Set in C++](https://www.geeksforgeeks.org/set-in-cpp-stl/)

**Related problems**

- [Container with Most Water](https://leetcode.com/problems/container-with-most-water/)
- [Subarray with product less than K](https://leetcode.com/problems/subarray-product-less-than-k/)
- [Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

### Code

**Solution with set**

```cpp
#include <bits/stdc++.h>

using namespace std;


int main() {


	int n;
	long long k , ans = 0;
	cin >> n >> k;

	vector<long long> a(n);
	set<pair<long long, int>> st;

	for (auto&e : a)
		cin >> e;

	int l = 0 , r = 0;

	while (r < n) {
		st.insert({a[r] , r}); // Set does not allow duplicate values so we also store the index
		//to allow store same values
		r++;

		while (!st.empty()) {
			int mn = st.begin()->first;
			int mx = st.rbegin()->first;

			if (mx - mn <= k) break;
			st.erase({a[l], l});
			l++;
		}

		ans += (long long)(r - l);

	}

	cout << ans << "\n";
	return 0;
}
```

**Solution with min/max queue**

```cpp
#include <bits/stdc++.h>

using namespace std;


struct min_queue {
	stack<pair<long long, long long>> s2, s1;


	long long getMin() {
		long long minimum;
		if (s1.empty() || s2.empty())
			minimum = s1.empty() ? s2.top().second : s1.top().second;
		else
			minimum = min(s1.top().second, s2.top().second);
		return minimum;
	}

	void push(long long new_element) {
		long long minimum = s1.empty() ? new_element : min(new_element, s1.top().second);
		s1.push({new_element, minimum});
	}

	void pop() {
		if (s2.empty()) {
			while (!s1.empty()) {
				long long element = s1.top().first;
				s1.pop();
				long long minimum = s2.empty() ? element : min(element, s2.top().second);
				s2.push({element, minimum});
			}
		}
		s2.pop();
	}
};

struct max_queue {
	stack<pair<long long, long long>> s2, s1;


	long long getMax() {
		long long maximum;
		if (s1.empty() || s2.empty())
			maximum = s1.empty() ? s2.top().second : s1.top().second;
		else
			maximum = max(s1.top().second, s2.top().second);
		return maximum;
	}

	void push(long long new_element) {
		long long maximum = s1.empty() ? new_element : max(new_element, s1.top().second);
		s1.push({new_element, maximum});
	}

	void pop() {
		if (s2.empty()) {
			while (!s1.empty()) {
				long long element = s1.top().first;
				s1.pop();
				long long maximum = s2.empty() ? element : max(element, s2.top().second);
				s2.push({element, maximum});
			}
		}
		s2.pop();
	}
};


int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);

	int n;
	long long k , ans = 0;
	cin >> n >> k;

	vector<long long> a(n);

	for (auto&e : a)
		cin >> e;

	int l = 0 , r = 0;

	max_queue mx_q;
	min_queue mn_q;

	while (r < n) {
		mx_q.push(a[r]);
		mn_q.push(a[r]);
		r++;

		while (mx_q.getMax() - mn_q.getMin() > k) {
			mx_q.pop();
			mn_q.pop();
			l++;
		}

		ans += (long long)(r - l);
	}

	cout << ans << "\n";
	return 0;
}
```
