## Watering Plants

You have a garden of lenght $L$ . You want to plant water spray such that the entire stretch of land $[0,L]$ is watered.

Each water spray has a range of $W$ so, when a water spray is placed at a position $x$ then it can water plant from $[x,x+W]$.

There are $N$ water spray position already present. The position of $i^{th}$ water spray is $a_{i}$.

Find the minimum number of water spray that needs to be added to water the entire stretch.

**Note:** It is perfectly fine for some stretch of land to be watered by multiple sprays.

### Constraints

$1 \leq N \leq 10^{5}$
$1 \leq W \leq L \leq 10^{16}$
$0 \leq a_i \leq L$

### Input

$N \quad L \quad W $
$a_1 \quad a_2 \quad \cdots \quad a_N$

### Output

Print minimum number of water spray that needs to be added to water the entire stretch.

### Example

Input

```
2 10 3
3 5
```

Output

```
2
```

### Test cases

**Edge cases**

- ```
    3 1000 5
    5 4 2
    Input is not sorted so it must be sorted first
  ```

- ```
    3 10 8
    2 12 14
    There is no need to consider spray after 2nd one.
  ```

**Large input test cases**

- ```
    1 10000000000000000 1
    0
  ```

### Hints

- Does relative ordering of initial sprays matter ?
- What is the maximum number of water sprays that can be used?
- Notice the large value of $L$. What algorithm do you think can be used?
- Suppose I tell you that we can water the entire stretch by using $y$ water sprays. Can you tell whether it is possible to water entire stretch using $y-1$ and $y+1$ water sprays ?

### Editorial

**Prerequisites**

- Binary Search
- Sorting

**Optimal Solution $O(N \log{L})$**

First let us assume that the minimum possible water sprays needed to water the entire stretch is $Y$.

$0$ sprays are not sufficient.
$1$ sprays are not sufficient.
$2$ sprays are not sufficient.
$\vdots$
$Y$ sprays are sufficient.
$Y+1$ sprays are sufficient.
$Y+2$ sprays are sufficient.
$\vdots$

_**Remember** (It is perfectly fine for some stretch of land to be watered by multiple sprays)_

So now we see a pattern here. After a certain number it is always possible to water the entire stretch. Now we need to find the minimum value. As ${L}$ is very large it is not possible to check each value $[0,L]$. But we don't need to, as we can perform binary search on _number of water sprays_.

Here's the algorithm.

- If the current number of sprays do not water the entire stretch then we need more sprays, so we move to a grater number
- If the current number of sprays is sufficient then we might have found the answer, so we store it and move to a smaller number to check if a smaller answer exist or not.

Now we need to find whether $Y$ number of sprays are sufficient or not. It can be done in $O(N)$ time complexity. (Refer to the code)

**Things to keep in mind**

- Whenever you are using binary search with large values. Use the code below to prevent overflow.

```cpp
int mid = lo + (hi-lo)/2;
```

**Resource links**

- [Great Blog on Binary Search](https://www.topcoder.com/thrive/articles/Binary%20Search)

**Similar problems**

- [Allocate minimum number of pages](https://www.interviewbit.com/problems/allocate-books/)
- [Aggresive cows](https://www.spoj.com/problems/AGGRCOW/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;


bool is_num_of_sprays_enough(vector<long long>&a ,
                             long long l ,
                             long long w,
                             long long max_extra_sprays) {

	//We initialize it with 0 because we are at 0 initially
	//This variable just keeps the track of the maximum distance we have watered.
	long long current_range = 0;

	for (int e : a) {

		if (e <= current_range) {//That means that the current index is covered so we dont need extra sprays here
			current_range = max(current_range , e + w);
		} else {

			//This is the formula to calculate ceil.
			//Here we are calculating minimum number of sprays required to reach till the current index
			// ceil(a/b) = (a+b-1)/b

			int count = (e - current_range + w - 1) / w;
			max_extra_sprays -= count;
			current_range = max(current_range + count * w , e + w);
		}


		//Once we have watered the entire stretched we can just exit the loop
		if (current_range >= l) break;
	}

	//If we still haven't reached the end yet then we have to add count
	if (current_range < l) {
		int count = (l - current_range + w - 1) / w;
		max_extra_sprays -= count;
	}


	return max_extra_sprays >= 0LL;
}

int main() {
	long long n , l , w;
	cin >> n >> l >> w;
	vector<long long> a(n);


	for (auto&e : a)
		cin >> e;

	sort(begin(a) , end(a));

	long long lo = 0 , hi = 1e17;
	long long ans = 0;

	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		if (is_num_of_sprays_enough(a , l , w, mid)) ans = mid , hi = mid - 1;
		else lo = mid + 1;

	}

	cout << ans << "\n";
}
```
