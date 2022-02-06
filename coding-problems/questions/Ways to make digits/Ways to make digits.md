## Ways to make digits

You are given `N` single digit integers. On these N integers you can perform any of the two operations given below any number of times, until a single digit number is left.

The two operations are:

- delete the leftmost two values (let us call them a and b) and then insert $ \left(a+b\right)\%10 $ to the left end

- Delete the leftmost two values (let us call them a and b) and then insert $\left(a\ast b\right)\%10$ to the left end.

  For each single digit integer from 0 to 9 (inclusive) find the number of ways to make the digit. Since the answer can be really huge to find the number of ways modulo ${10}^9+7.$

### Constraints

$2\le N\le{10}^6$
$0\le A_i\le9$

### Input

$N$
$A_{1} \ A_{2} \ A_{3} \cdots A_{n}$

### Output

Print ten lines i.e., for each digit print the number of ways modulo ${10}^9+7$.

### Example

Input

```
3
2 7 6
```

Output

```
1
0
0
0
2
1
0
0
0
0
```

If we do Operation 1 first and Operation 1 second: the sequence becomes $(2,7,6)→(9,6)→(5)$.
If we do Operation 1 first and Operation 2 second: the sequence becomes $(2,7,6)→(9,6)→(4)$.
If we do Operation 2 first and Operation 1 second: the sequence becomes $(2,7,6)→(4,6)→(0)$.
If we do Operation 2 first and Operation 2 second: the sequence becomes $(2,7,6)→(4,6)→(4)$.

### Test cases

**Edge cases**

- ```
  2
  0 0
  ```

  > If the base case implementation is wrong then this will result in WA

- ```
  2
  2 2
  ```

- ```
  3
  2 2 7
  ```

**Large input test cases**

- ```
  1000000

  9 7 8 9 7 8 9 7 8 ..... 9 7 8
  ```

### Hints

- Notice that both the input and output are all **single digit integers**.
- Let’s say we consider only 2 elements in array. Can you find all possible ways now? If you can, try to use these values to find the answer for N=3 element array.
- If you know the number of ways to **make digits with N-1 numbers** can you use it to find answer for N integers

### Editorial

**Prerequisites**

- Dynamic Programming
- Basic Modulo arithmetic

**Naïve Solution [ 0(2^n^) ]**
At every integer we have to two possible options either we use the 1st operation or the second operation. After we reach the Nth number, we can calculate the frequency of each digit. However, this solution is too slow and will exceed the time limit. Notice that we are recalculating the same value again and again, so there is a room for optimization.

**Optimal Solution[ 0(n) ]**

First observations are that at any point of time the value does not exceed 9.

Let us look at few cases two understand the solution better.

- Case 1: When N=2 (Base case)
  In this case there are only two possible outcomes (as there are two possible operations).
- Case 2: When N>2
  We have already stored the value for N=2. Now we should ask ourselves **for each digit that can be made in the previous index. Can we perform operation with the current index’s value? Yes, we can**. As there are only ten digits we go through the digits of the previous index and perform operations to get new values in the current index. So, at every index we can store 10 values (0-9) and use it to calculate the next index answer.

Let’s look at an example to understand it better.

```
3
2 7 6
```

DP Table

| digit | N=1 |       N=2       |                N=3                |
| :---: | :-: | :-------------: | :-------------------------------: |
|   0   |  0  |        0        |          1 $[(4+6)\%10]$          |
|   1   |  0  |        0        |                 0                 |
|   2   |  0  |        0        |                 0                 |
|   3   |  0  |        0        |                 0                 |
|   4   |  0  | 1 $[(7*2)\%10]$ | 2 $[(9*6)\%10]$ and $[(4*6)\%10]$ |
|   5   |  0  |        0        |          1 $[(9+6)\%10]$          |
|   6   |  0  |        0        |                 0                 |
|   7   |  0  |        0        |                 0                 |
|   8   |  0  |        0        |                 0                 |
|   9   |  0  | 1 $[(7+2)\%10]$ |                 0                 |

- Remember after we perform operation on a and b they are replaced by a single value.

**Recurrence relation**

```cpp
dp[i][j] = number of ways of operations for the first i elements, after which the first element of the sequence becomes j.
```

(Have a look at the code for better understanding)

So, time complexity : O(N\*K) , Here K = number of single digit numbers = 10. So, it is a constant.

Time complexity: **O(N)**
Space complexity: **O(N)**

**Things to keep in mind**
Whenever you are dealing with large value it is safe to use `long long` to prevent overflow (Just like this case)

**Resource links**

- [Aditya verma DP series](https://www.youtube.com/watch?v=nqowUJzG-iM&list=PL_z_8CaSLPWekqhdCPmFohncHwz8TY2Go)

- [Striver DP series](https://www.youtube.com/playlist?list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY)

- [Basic Modular arithmetic](https://www.geeksforgeeks.org/modular-arithmetic/)

### Code

```cpp
include <bits/stdc++.h>

using namespace std;

constexpr int MOD = 1e9 + 7;

int main() {


	int n;
	cin >> n;
	vector<int> arr(n);

	for (int&e : arr)
		cin >> e;

	vector<vector<long long>> dp(n + 1 , vector<long long>(10 , 0));

	//Defining the base case

	dp[1][(arr[0] * arr[1]) % 10]++;
	dp[1][(arr[0] + arr[1]) % 10]++;


	for (int i = 2; i < n; i++)
		for (int j = 0; j < 10; j++) {
			if (dp[i - 1][j] == 0) continue; // If in the previous index there was no way to make j
			//then we cannot use it hence skip it.



			//We use the previous j value to calculate the current value
			dp[i][(arr[i] * j) % 10] += dp[i - 1][j];
			dp[i][(arr[i] + j) % 10] += dp[i - 1][j];


			dp[i][(arr[i] * j) % 10] %= MOD;
			dp[i][(arr[i] + j) % 10] %= MOD;

		}

	for (int j = 0; j < 10; j++)
		cout << dp[n - 1][j] << "\n";
}

```
