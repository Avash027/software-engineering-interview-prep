## Cheap Coloring

There are $N$ houses, some of which may be colored. You can color each house in `X`, `Y`, `Z` color.1 bucket of any color is needed to completely paint 1 house. Also, you are given the prices of one bucket of color. You have to find the minimum cost to color the houses such that no two adjacent houses are of the same color. You may or may not paint the already painted house.

Houses that are not painted initially are labelled as `?`.

### Constraints

$1 \leq N \leq 10^5 $
$N$ characters where $a_i = X \ or \ Y \ or \ Z \ or \ ?$
$1 \leq C_x, C_y, C_z \leq 10^5$

### Input

$N$
$a_1 ,\quad a_2 ,\quad a_3 \dots \quad a_n$
$C_x \quad C_y \quad C_z$

### Output

Print one integer the minimum cost of repainting.

### Example

Input

```
4
X??X
4 2 2
```

Output

```
4
```

There are two optimal ways of coloring `XZYX` or `XYZX`. Both these combinations requires $1$ bucket each of X and Y color. So the minimum cost is $4$.

### Test cases

**Edge cases**

```
1
X
1 2 3

Output: 0
```

```
1
?
1 2 1

Output: 1
```

```
4
????
1 2 3

Output: 6
```

```
4
Y???
1 3 6

Output: 7
```

**Large input test cases**

```
100000
???????????????? ... (100000 times)
100000 100000 100000
```

```
100000
???????????????? ... (100000 times)
100000 1 100000

```

### Hints

- Notice that there are **only 3** colors.
- Suppose there is only 1 house. Can you find the minimum cost to paint that 1 house? If yes, can you use that result to determine cost to paint 2 houses?
- We do not want adjacent house to have same colors. So when we want to color a house we just need to check the previous house.

### Editorial

**Prerequisites**

- Basic Dynamic Programming

**Optimal Solution $O(N)$**

Let us assume that we found the cheapest way to color the $N-1$ houses. So, the color of the last house will either be `X`, `Y`, or `Z`. Now, we have 3 cases depending on the color of last house.

Case `X`:

If the color of last house is `X`, the color of the house before it must either be `Y` or `Z`. Let the minimum cost of painting such that the $(N-1)th$ house is `Y` be $P_Y$ and the minimum cost of painting such that the $(N-1)th$ house is `Z` be $P_Z$. Since it is the cheapest solution and $C_X$ is a constant, the cost to paint the first $N-1$ houses must be $min(P_Y, P_Z)$.

**Hence, total cost if the last house is painted `X` = $C_X + min(P_Y, P_Z)$.**

Similarly,

Case `Y`:

**Total cost if the last house is painted `Y` = $C_Y + min(P_X, P_Z)$.**

Case `Z`:

**Total cost if the last house is painted `Z` = $C_Z + min(P_X, P_Y)$.**

So now we have two obersvations:

- To find the minimum cost to paint first $i$ houses we need the minimum cost to paint first $i-1$ houses.

- For each $i$ we need to store three values
  - Minimum cost if we paint the $i$th house `X`.
  - Minimum cost if we paint the $i$th house `Y`.
  - Minimum cost if we paint the $i$th house `Z`.

**Recurrence relation**

**$dp[i][j]$ = Minimum cost to paint the first $i$ houses such that the $i$th house is painted in color $j$.**

- If $a_i \neq X$ then
  - $dp[i][X] = C_X + \ min(dp[i-1][Y] , dp[i-1][Z])$
- Else
  - $dp[i][X] =  min(dp[i-1][Y] , dp[i-1][Z])$

Repeat the same relation for all other colors.

Base case

$dp[0][X] = a_0 == X?0:C_X$
$dp[0][Y] = a_0 == Y?0:C_Y$
$dp[0][Z] = a_0 == Z?0:C_Z$

**Time complexity :** $O(N)$
**Space complexity :** $O(N)$

### Code

```cpp
#include <bits/stdc++.h>


using namespace std;



/***
* To make calculations easier
* X = 0
* Y = 1
* Z = 2
*/

int main() {
	int n, cost_x, cost_y, cost_z;
	string s;

	cin >> n >> s;
	cin >> cost_x >> cost_y >> cost_z;

	vector<vector<int>> dp(n , vector<int>(3 , 0));

	//Base case
	dp[0][0] = (s[0] == 'X' ? 0 : cost_x);
	dp[0][1] = (s[0] == 'Y' ? 0 : cost_y);
	dp[0][2] = (s[0] == 'Z' ? 0 : cost_z);


	for (int i = 1; i < n; i++) {


		//For color X
		if (s[i] == 'X') dp[i][0] = 0;
		else dp[i][0] = cost_x;

		dp[i][0] += min(dp[i - 1][1] , dp[i - 1][2]);

		//For color Y
		if (s[i] == 'Y') dp[i][1] = 0;
		else dp[i][1] = cost_y;

		dp[i][1] += min(dp[i - 1][0] , dp[i - 1][2]);

		//For color Z
		if (s[i] == 'Z') dp[i][2] = 0;
		else dp[i][2] = cost_z;

		dp[i][2] += min(dp[i - 1][0] , dp[i - 1][1]);
	}

	cout << min({dp[n - 1][0] , dp[n - 1][1] , dp[n - 1][2]}) << "\n";

	return 0;
}
```
