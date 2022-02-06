## Colorful flowers

There are N flowers arranged in a row from left to right.
Each of these flowers has one color that is one of the $10^{9}$ colors called Color 1, Color 2, …, and Color $10^{9}$.

For each $i=1,2,…,N$ the color of the $i$-th flower from the left is Color $c_i$.

From this row, you can choose $K$ consecutive flowers and get them.
That is, he can choose an integer $i$ such that $1 \leq i \leq N−K+1$ and get the $i$-th, ($i+1$)-th, ($i+2$)-th, …, ($i+K−1$)-th flower from the left.

Print the maximum possible number of distinct colors in flowers you can get.

### Constraints

$0 \leq K \leq N \leq 2×10^{5}$
$1 \leq c_{i} \leq 10_{9}$

### Input

$N \quad K$
$a_{1} \quad a_{2} \quad a_{3} \cdots a_{N}$

### Output

Print a single integer i.e., maximum possible number of distinct colors in flowers you can get.

### Example

Input

```
7 4
1 2 1 2 2 3 1
```

Output

```
3
```

$[1,2,1,2]$ Number of distinct colors = $2$
$[2,1,2,2]$ Number of distinct colors = $2$
$[1,2,2,3]$ Number of distinct colors = $3$
$[2,2,3,1]$ Number of distinct colors = $3$

So the maximum distinct color in a window of size $K$ is $3$

### Test cases

**Edge cases**

```
5 0
1 2 6 2 1

Output should be 0
```

```
0 0

Output should be 0
```

**Large input test cases**

```
2000000 200000
1 2 3 4 5 ... 2000000 (First 200000 numbers)
```

### Hints

- Can you solve this problem in $O(N*K)$ ?
- Are we revisiting same array multiple times in brute force approach? If yes, how can we optimize it ?
- How many values differ in two consecutive windows?

### Editorial

**Prerequisites**

- Basic use of hashmap

**Optimal Solution $O(Nlog{N})$**

Let us denote the $i$-th, ($i+1$)-th, ($i+2$)-th, …, ($i+K−1$)-th flowers by the segment $[i,i+K−1]$.

There are $N+K−1$ candidates of the segment of our choice, $[1,K]$,$[2,K+1]$,$[3,K+2]$, $\cdots$, and $[N−K+1,N]$.
It is sufficient to find for each segment “the number of colors of flowers in it” and output the maximum value as the answer.

In order to count the number of colors of flowers in a segment we can “inspect each of the K flowers in the segment and count the colors within it.”
However, this method requires K times of “inspection of a flower” for each segment, so if we do this for every of $N−K+1$ candidates of segments, we need $K*(N−K+1)$ number of operations of “inspecting a flower.” This method will result in **TLE**

So, we will speed up the method above.
Assume that we have just inspected $[i,i+K−1]$ and now want to inspect $[i+1,i+K]$ right after that. Here, note that adding the (i+K)-th flower to, and then instead removing the i-th flower from $[i,i+K−1]$, results in $[i+1,i+K]$. Note that there are only 2 elements that differ in both the segments i.e., $c_{i}$ and $c_{i+K}$. To evaluate the current segment we add $c_{i+K}$ to our window and remove $c_{i}$.

Let's discuss the algorithm to update answer for every window

- First we inspect $c_{1} , \quad c_{2} , \quad c_{K}$ and for each color of which at least one of flower in [1,K] has, store the number of flowers of that color in a hashmap.Every time we encounter a new color we update the $count$.

- Then we move to $c_{K+1}$. Now we do not need $c_{1}$ so we decrement the count of $c_{1}$ from the map. After the decrement if the value becomes $0$ that means we lost a distinct color so we decrement the $count$. Now we add $c_{K}$ and if the count of $c_{K}$ in hashmap is $0$ that means we have encountered a distinct color so we update
  the $count$.

- We repeat this process for $K \leq i < N$

For each flower, the addition to and removal from the associated array is done at most N times, so the time complexity for this algorithm is $O(N\log{N})$, which is fast enough to get accepted for this problem.

**Time complexity:** $O(N\log{N})$
**Space complexity:** $O(N)$

**Things to keep in mind**

- In C++, only use unordered_map if the time limit is too tight. For some case insertion in unordered_map can have the worst complexity of $O(N)$. You can refer to blog in the resource link.

**Resource links**

- [Blowing up unordered map in C++](https://codeforces.com/blog/entry/62393)
- [Map in c++](https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/)
- [Map in JAVA](https://www.javatpoint.com/java-hashmap)

**Similar problems**

- [Subarray product less than K](https://leetcode.com/problems/subarray-product-less-than-k/solution/)
- [ Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, k;
	int max_distinct_colors = 0 , current_distinct_colors = 0;
	map<int, int> freq_colors;

	cin >> n >> k;

	if (n == 0 || k == 0) { //Edge case handling
		cout << 0 << "\n";
		return 0;
	}

	vector<int> arr(n);

	for (int&e : arr)
		cin >> e;


	for (int i = 0; i < k; i++) {
		//Here we are first checking if the color was already present or not
		//Then we update the frequency
		//NOTE: This is post-increment operator
		if (freq_colors[arr[i]]++ == 0) current_distinct_colors++;
	}

	max_distinct_colors = current_distinct_colors;


	for (int i = k; i < n; i++) {

		if (--freq_colors[arr[i - k]] == 0) current_distinct_colors--;
		if (freq_colors[arr[i]]++ == 0) current_distinct_colors++;

		max_distinct_colors = max(max_distinct_colors , current_distinct_colors);
	}

	cout << max_distinct_colors << "\n";

	return 0;
}
```
