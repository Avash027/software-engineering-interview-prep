## Large Square

You are given a matrix $A$ filled with $5$ characters $a$, $b$, $c$, $d$, $e$. You have to find the square with the largest area consisting of same character and print its area.

### Constraints

$1≤N≤10^5$
$1≤M≤10^5$
$A_{i,j}∈{ a,b,c,d,e}$
$N∗M≤10^6$

### Input

$N \quad M$
$A_{1,1} \quad A_{1,2} \quad \dots \quad A_{1,M}$
$A_{2,1} \quad A_{2,2} \quad \dots \quad A_{2,M}$
$\vdots$
$A_{N,1} \quad A_{N,2} \quad \dots \quad A_{N,M}$

### Output

Print one integer, the maximum area of square containing only one character.

### Example

Input

```
4 5
a a a a b
a a a a c
a a a a d
a a a a a
```

Output

```
16
```

Explanation

The vertices of the largest square is $(1,1)$, $(1,4)$, $(4,1)$, $(4,4)$. It contains only one character $a$, so the area is $16$.

### Test cases

**Edge cases**

```
1 1
a

Output: 1
```

```
2 2
a a
a a

Output: 4
```

```
2 2
a b
a b

Output: 1
```

**Large input test cases**

```
1000 1000
a a a a a .... a
a a a a a .... a
.
.
.
a a a a a .... a

Output: 1000000
```

```
1000 1000
a b c d e .... a
a b c d e .... a
.
.
.
a b c d e .... a

Output: 1
```

```
1000000 1
a
b
c
a
a
a
.
.
a

Output: 1
```

### Hints

- Notice that there are only $5$ types of characters, so there can be only $5$ types of squares.
- Let's say I have a cell $A_{x,y}$ and I want to know that if it is a part of $2*2$ square. How can I find it ?
- For each cell assume it is the lower right vertex of a square. Now how can you find the largest square?

### Editorial

**Prerequisites**

- Basic dynamic programming

**Optimal Solution**

First we notice that there are only 5 characters, so we can find the greatest square for each type of character.

- We iterate from $a$ to $e$. Let's say that the current character is $cur_c$
- If $A_{i,j} == cur_c$ then we mark it as $1$ else we mark it as $0$

Let's say the new matrix is $B$.

So now we have reduced the problem to finding the largest square with all 1's for each character.

Now to find the largest square of 1's we can use the following algorithm

- We will copy the first row and column into a matrix say $C$
- For other cells we use the **recurrence relation**

  **if $B_{i,j}$ is 1
  $\quad C_{i,j} = min(C_{i,j-1} , C_{i,j-1} , C_{i-1,j-1})+1$
  else
  $\quad  C{i,j} = 0$**

  _We are taking minimum value of all sides because we want all sides of square to be even_

- Answer for current character will be the maximum value of $C_{i,j}$

**Time complexity :**$O(k*N*M)$, where $k$ = number of characters = $5$

**Space complexity :**$O(N*M)$, where $k$ = number of characters = $5$

**Resource links**

- [Aditya Verma DP series](https://www.youtube.com/watch?v=nqowUJzG-iM&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)

- [Striver DP series](https://www.youtube.com/playlist?list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY)

- [Maximum size square sub-matrix with all 1s](https://www.geeksforgeeks.org/maximum-size-sub-matrix-with-all-1s-in-a-binary-matrix/)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<char>> A;

vector<vector<int>> make_binary_array(char c) {
	vector<vector<int>> B(n , vector<int>(m));

	for (int i = 0; i < n; i++)
		for (int j  = 0; j < m; j++) {
			if (A[i][j] == c)
				B[i][j] = 1;
			else
				B[i][j] = 0;
		}

	return B;

}

int calculate_largest_square(vector<vector<int>>& B) {
	int ans_c = 1;
	vector<vector<int>> C(n , vector<int> (m, 0));

	for (int i = 0; i < n; i++)
		C[i][0] = B[i][0];

	for (int j = 0; j < m; j++)
		C[0][j] = B[0][j];

	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++) {
			if (B[i][j] == 1)
				C[i][j] = min({C[i - 1][j] , C[i][j - 1], C[i - 1][j - 1]}) + 1;
			else
				C[i][j] = 0;

			ans_c = max(ans_c , C[i][j]);
		}

	return ans_c * ans_c;
}


int main() {
	int ans = 1;

	cin >> n >> m;

	A.assign(n, vector<char>(m));


	for (int i = 0; i < n; i++)
		for (int j  = 0; j < m; j++)
			cin >> A[i][j];


	for (char c = 'a'; c <= 'e'; c++) {
		vector<vector<int>> B =  make_binary_array(c);
		ans = max(ans , calculate_largest_square(B));
	}

	cout << ans << "\n";

	return 0;
}
```
