#include <bits/stdc++.h>

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