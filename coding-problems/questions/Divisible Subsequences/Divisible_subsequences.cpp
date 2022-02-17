#include <bits/stdc++.h>

using namespace std;

constexpr long long MOD = 1e9 + 7;

int main() {

	int n, k;
	cin >> n >> k;

	vector<vector<long long>> dp(k + 1 , vector<long long>(n + 1 , 0));

	for (int i = 1; i <= n; i++)
		dp[1][i] = 1;


	for (int i = 1; i < k; i++) {
		for (int j = 1; j <= n; j++) {
			for (int m = j; m <= n; m += j) //This loop is to calculate all the mutliples of j
				dp[i + 1][m] = (dp[i][j] % MOD + dp[i + 1][m] % MOD) % MOD;
		}
	}

	long long sum = 0;

	for (int i = 1; i <= n; i++) {
		sum += dp[k][i];
		sum %= MOD;
	}

	cout << sum << "\n";

	return 0;
}