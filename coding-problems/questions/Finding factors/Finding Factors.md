## Finding factors

You are given a number $N$ and you have to process $Q$ queries.

There are two types of queries you have to answer

- $1 \quad l \quad r$
  **Find the smallest divisor** of $N$ in the range $[l,r]$ inclusive. If there is no divisor in the range print $-1$.

- $2 \quad l \quad r$
  **Find the largest divisor** of $N$ in the range $[l,r]$ inclusive. If there is no divisor in the range print $-1$.

### Constraints

$1 \leq N \leq 10^9$
$1 \leq Q \leq 10^6$
$1 \leq l \leq r \leq N$
$q = 1,2$

### Input

$N \quad Q$
$q_1 \quad l_1 \quad r_1$
$q_2 \quad l_2 \quad r_2$
$\vdots$
$q_Q \quad l_Q \quad r_Q$

### Output

Print $Q$ lines, the required answer for each query.

### Example

```
24 5
1 3 7
2 3 7
1 13 15
1 1 30
2 4 26
```

```
3
6
-1
1
24
```

Explanation

Divisors of $24$ are $1,2,3,4,6,8,12,24$

Smallest prime factor in $[3,7]$ = $3$.
Largest prime factor in $[3,7]$ = $6$.
Smallest prime factor in $[13,15]$ = none, so the answer will be $-1$.
Smallest prime factor in $[1,30]$ = 1.
Largest prime factor in $[4,26]$ = 24.

### Test cases

**Edge cases**

```
1 2
1 1 1
2 1 1

Output:
1
1
```

```
1 2
1 3 5
2 6 8

Output:
-1
-1
```

**Large input test cases**

```
100000 100000
1 1 100000
2 1 100000
1 1 100000
.
.
.
1 1 100000
```

### Hints

- How do you find the all the divisors of $N$ efficiently? (Notice that $N$ is really large)
- Should we arrange the divisors of $N$ in a certain way so that we can answer the queries efficiently?
- You can use binary search to answer queries.

### Editorial

**Prerequisites**

- Basic binary search
- Factorization in $O(\sqrt{N})$

**Optimal Solution $O(\sqrt{N} + Q\log{N})$**

Notice that $N$ can be as large as $10^9$, so we need to find all the divisors of $N$ in at most $O(\sqrt{N})$.

After finding all the divisors of $N$ we can sort the divisors. Then we can use binary search to answer the queries.

- To answer the queries of type $1$

  - If $d < l$ then we have to check for a greater divisor.
  - If $d > r$ then we have to check for a smaller divisor.
  - If $l \leq d \leq r$ then this might be the answer or there might be a smaller answer, so we check for a smaller divisor.

- To answer the queries of type $1$
  - If $d < l$ then we have to check for a greater divisor.
  - If $d > r$ then we have to check for a smaller divisor.
  - If $l \leq d \leq r$ then this might be the answer or there might be a larger answer, so we check for a larger divisor.

**Time complexity :**$O(\sqrt{N} + Q\log{N})$

**Space complexity :** $O(\sqrt{N})$

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

vector<int> find_divisors(int n) {
	vector<int> divisors;

	for (int i  = 1; i * i <= n; i++) {
		if (n % i != 0) continue;
		divisors.push_back(i);
		if (i * i != n) divisors.push_back(n / i); // to remove duplication
	}

	return divisors;
}

int process_query_1(int l , int r , vector<int>& divisors) {

	int lb = 0 , rb = (int)divisors.size() - 1;
	int ans = -1;

	while (lb <= rb) {
		int mid = (lb + rb) / 2;

		int d = divisors[mid];

		if (d >= l and d <= r) ans = d , rb = mid - 1;
		else if (d < l) lb = mid + 1;
		else rb = mid - 1;
	}

	return ans;
}


int process_query_2(int l , int r , vector<int>& divisors) {

	int lb = 0 , rb = (int)divisors.size() - 1;
	int ans = -1;

	while (lb <= rb) {
		int mid = (lb + rb) / 2;

		int d = divisors[mid];

		if (d >= l and d <= r) ans = d , lb = mid + 1;
		else if (d < l) lb = mid + 1;
		else rb = mid - 1;
	}

	return ans;
}


int main() {

	int n, q;
	cin >> n >> q;

	vector<int> divisors = find_divisors(n);

	sort(begin(divisors), end(divisors));

	while (q--) {
		int q_type, l, r, q_ans;
		cin >> q_type >> l >> r;

		if (q_type == 1)
			q_ans = process_query_1(l, r, divisors);
		else
			q_ans = process_query_2(l, r, divisors);

		cout << q_ans << "\n";
	}



	return 0;
}
```
