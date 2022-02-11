## More queries

You are given $N$ integers, and you have to process $Q$ queries on them.

There are two types of queries:

- $1 \ pos \ x$
  In this query you have to replace $a_{pos}$ with x. ($a_{pos} = x$)

- $2 \ l \ r$
  In this query you have to print the number of distinct integers in $[l,r]$ inclusive.

For each query of $2$nd print one integer, number of distinct integers in the given range.

**There will be atleast on query of type 2**

### Constraints

$1 \leq N \leq 2*10^5$
$1 \leq Q \leq 2*10^5$
$1 \leq a_i \leq 50$
$0 \leq pos < N$
$1 \leq x \leq 50$
$0 \leq l \leq r < N$

### Input

$N \ \ \ Q$
$a_0 \ \ \ a_1 \ \ \ a_2 \quad \dots \ \ \ a_{N-1}$
$q_{1} \ \ \ arg_1 \ \ \ arg_2$
$q_{2} \ \ \ arg_1 \ \ \ arg_2$
$\vdots$
$q_{Q} \ \ \ arg_1 \ \ \ arg_2$

### Output

For each query of $2$nd type print one integer in new line, number of distinct integers in the given range.

$ans_1 \\ ans_2 \\ \vdots$

### Example

Input

```
5 5
1 5 2 3 9
2 0 3
1 0 3
2 0 4
1 4 10
2 4 4
```

Output

```
4
4
1
```

Explaination:

- $1st$ Query: Number of distinct integers in $[1,5,2,3]$ is $4$.

- $2nd$ Query: Updating $a_0$ with $3$. So the updated array looks like $[3,5,2,3,9]$

- $3rd$ Query: Number of distinct integers in $[3,5,2,3]$ is $3$.

- $4th$ Query: Updating $a_4$ with $10$. So the updated array looks like $[3,5,2,3,10]$

- $5th$ Query: Number of distinct integers in $[10]$ is $1$.

### Test cases

**Edge cases**

```
3 7
1 2 3

2 0 0
2 1 1
2 2 2
2 0 2
1 0 3
1 1 3
2 0 2

Output:
1
1
1
3
1
```

**Large input test cases**

```
200000 200000
1 1 1 1 1 1 .... 1 (200000 times)

2 0 199999
2 0 199999
.
.
.
2 0 199999 (200000 queries)
```

```
200000 200000
50 50 50 50 50 50 .... 50 (200000 times)

2 0 199999
2 0 199999
.
.
.
2 0 199999 (200000 queries)
```

```
200000 200000
1 2 3 4 5 6 .... 50 1 2 ...  (200000 times)

2 0 199999
2 0 199999
.
1 199999 1
1 0 50
.
2 0 199999 (200000 queries)
```

### Hints

- Suppose the second query was - **Check if $x$ was present in range $[l,r]$** then can you process all the queries?

- Have a look at the constraint of $a_i$.

- What is the maximum number of distinct character in an array range $[0,N-1]$?

### Editorial

**Prerequisites**

- Set in C++ STL or TreeSet in java

**Optimal Solution $O(N\log{N})$**

**Prerequisites**

- Set in C++ STL or TreeSet in java

**Optimal Solution $O(N\log{N})$**

At first, it might look like we need to use Mo's algorithm here. But the constraint on $N$ will barely allow it.

Notice that the range of values for $a_i$ is very small.

So for **each integer from $1$ to $50$, $(1 \leq a_i \leq 50)$ we can check if they are present in the range $[l,r]$**. If it is present we increment the answer by 1.

Now we need an effeient way to process the queries.

- To process the queries of first type we need a data structure that can add, remove elements effeciently.
- To process the queries of second type we need a data structure that can find `lower_bound` of any number.

This can be implemented using `set` in C++ or `TreeSet` in Java.

Let's have a look at the algorithm to process the queries.

```cpp
set<int> st[51]
```

Here the $i$th index of `st` stores all the occurences of integer $i$ in a sorted manner.

- **1st Query**
  We have to replace $a_i$ with $x$. So we remove $i$ from $st[a_i]$ and add $i$ to $x$. Because $x$ occurs at $i$ after the 1st query.

- **2nd Query**
  We iterate for each $y$ for $1 \leq y \leq 50$. We find occurence in $st[y]$ that is greater than or equal to $l$ (lower_bound). If there is exsist an occurence that is also less than or equal to $r$ then we increment the ansewer.

Insertion, Removal and lower_bound all have time complexity $O(\log{N})$.

**Time complexity :**$O(N*K*\log{N})$
**Spcae complexity :**$O(N*K)$
where K = range of $a_i$

**Things to keep in mind**

- Be careful with using lower_bound in c++ as it can return iterator that is out of bounds. If you dereference that iterator you will get error. So always check if the iterator is in bounds or not.

**Resource links**

- [Set in C++](https://www.geeksforgeeks.org/set-in-cpp-stl/)
- [TreeSet in Java](https://www.geeksforgeeks.org/treeset-in-java-with-examples/)
- [Lower bound in set in C++](https://www.geeksforgeeks.org/set-lower_bound-function-in-c-stl/)

### Code

```cpp
#include <bits/stdc++.h>


using namespace std;

/**
Notice that we are passing st by reference
*/
void process_query_1(vector<int>&a, vector<set<int>>& st) {
	int pos, x;

	cin >> pos >> x;

	st[a[pos]].erase(pos);
	a[pos] = x;
	st[x].insert(pos);

}

int process_query_2(vector<set<int>>& st) {
	int l, r, ans = 0;
	cin >> l >> r;

	for (int i = 1; i <= 50; i++) {
		auto index_in_bound = st[i].lower_bound(l);

		//We first check if the iterator is out of bounds or not
		if (index_in_bound != st[i].end() and (*index_in_bound) <= r)
			ans++;
	}

	return ans;
}

int main() {

	int n, q;
	int q_type;

	cin >> n >> q;

	vector<set<int>> st(51);
	vector<int> a(n);


	for (int i = 0; i < n; i++) {
		cin >> a[i];
		st[a[i]].insert(i);
	}


	for (int i = 0; i < q; i++) {
		cin >> q_type;

		if (q_type == 1)
			process_query_1(a, st);
		else {
			int q_ans = process_query_2(st);
			cout << q_ans << "\n";
		}

	}

	return 0;
}
```
