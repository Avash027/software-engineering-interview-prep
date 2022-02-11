## Meetups

You are given a string $s$. You can delete the letters in a certain order, which is described as a permutation of indices of the letters of the word $s$: $a_1 \ , \ a_2 \ \dots a_{|s|}$. Note that after deleting a letter, the numbering does not change.

You are given another string $p$.

You have to find the maximum number of letters you can delete from $s$ such that it is possible to obtain $p$.

**Note:** You can obtain $p$ from remaining $s$ if $p$ is a subsequence of remaining $s$.

It is always possible to obtain $p$ from $s$.

### Constraints

$1 \leq |s| \leq 10^5$
$1 \leq |p| \leq |s| \leq 10^5$
$1 \leq |a_i| \leq |s|$

### Input

$s \\ p$
$a_1 \quad a_2 \quad \dots \quad a_{|S|}$

### Output

Print one number, the maximum number of characters you can delete.

### Example

Input

```
ababcba
abb
5 3 4 1 7 6 2
```

Output

```
3
```

Explaination

After deleting $s_5$, string will be $ababba$
After deleting $s_3$, string will be $abbba$
After deleting $s_4$, string will be $abba$

This is the maximum characters we can delete and still obtain $p$ from $s$.

Suppose we delete the index,

After deleting $s_1$, string will be $bba$

Now we cannot obtain $p$ from $s$, so we cannot delete this many characters.

### Test cases

**Edge cases**

```
aaa
aaa
1 2 3

Output: 0
```

```
aaaabbb
b
1 2 3 4 5 6 7

Output: 6
```

```
aaaabbb
b
7 6 5 1 2 3 4

Output: 2
```

```
cccaacc
a
4 1 2 3 7 6 5

Output: 6
```

**Large input test cases**

```
aaaaaaa....b (Length =  100000)
b
1 2 3 4 5 ... 99999 100000

Output: 99999
```

### Hints

- What is the minimum number of characters you need to delete to obtain $p$ from $s$?
- If I tell you that you can obtain $p$ from $s$ by deleting first $Y$ indices from the array, then is it possible to obtaib $p$ from $s$ by deleting $Y+1$ indices ?
- If I tell you that you can obtain $p$ from $s$ by deleting first $Y$ indices from the array, then is it possible to obtaib $p$ from $s$ by deleting $Y-1$ indices ?

### Editorial

**Prerequisites**

- Binary search

**Optimal Solution $O(N\log{N})$**

Let's look at the example and try to find some pattern.

- When we delete $0$ characters, we can obtain $p$.
- When we delete $1$ characters, we can obtain $p$.
- When we delete $2$ characters, we can obtain $p$.
- When we delete $3$ characters, we can obtain $p$.
- When we delete $4$ characters, we cannot obtain $p$.
- When we delete $5$ characters, we cannot obtain $p$.
  And so on.

So we can observe a pattern here that after a certain number of deletion we cannot obtain $p$.

So we can solve this problem using **binary search**.

Pseudocode for the algorithm is given below

- Select a number $Y$.
- If after deleting first $Y$ characters as per the array we can obtain $p$ then we store it as the answer and look for a greater value.
- Else $Y$ is not answer, and we look for smaller value.

Now we need an effecient way to check if $p$ can be obtained from $remaining \ s$. We can do this using two pointers method.

- Keep pointer $i$ at $s_0$ and $j$ at $p_0$.
- If $s_i == p_j$ then we increment both the pointers
- Else we only increment $i$ pointer.

**Time complexity :** $O(N\log{N})$
**Space complexity :** $O(N)$

**Resource links**

- [Great Blog on Binary Search](https://www.topcoder.com/thrive/articles/Binary%20Search)

### Code

```cpp
#include <bits/stdc++.h>

using namespace std;

string s, p;
int n , m;
vector<int> indices;


bool is_P_in_S(const string&s1) {
	int i = 0 , j = 0;
	int n1 = s1.size();

	while (i < n1 and j < m) {
		if (s1[i] == p[j]) i++, j++;
		else i++;
	}

	return (j >= m); //This means all characters of p is in s1
}


int binary_search() {
	int lo = 0 , hi = n - 1;
	int ans = -1;


	while (lo <= hi) {
		int mid = (lo + hi) / 2;

		string s1;
		unordered_map<int, bool> to_exclude;

		for (int i = 0; i <= mid; i++)
			to_exclude[indices[i]] = true;

		for (int i = 0; i < n; i++ )
			if (!to_exclude[i])
				s1.push_back(s[i]);



		if (is_P_in_S(s1)) {
			ans = mid;
			lo = mid + 1;
		}
		else {
			hi = mid - 1;
		}

	}

	return ans + 1;//Conveting it to 1 based index
}


int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	cin >> s >> p;

	n = s.size();
	m = p.size();
	indices.resize(n);

	for (int i = 0; i < n; i++) {
		cin >> indices[i];
		indices[i]--; // We are converting one based index to 0 based index
	}

	cout << binary_search() << "\n";


	return 0;
}
```
