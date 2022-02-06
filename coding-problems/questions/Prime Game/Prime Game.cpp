#include <bits/stdc++.h>

using namespace std;


vector<int> getPrimeFactors(int n) {
	vector<int> prime_factors;

	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			prime_factors.push_back(i);
			while (n % i == 0) n /= i;
		}
	}

	if (n > 1) prime_factors.push_back(n);

	return prime_factors;
}

int main() {

	int n;
	cin >> n;

	vector<bool> dp(n + 1, false);


	for (int i = 2; i <= n; i++) {
		vector<int> prime_factors = getPrimeFactors(i);

		for (int factor_of_i : prime_factors)
			dp[i] = dp[i] or !dp[i - factor_of_i];//Notice the negation operater here
	}


	if (dp[n]) cout << "YES\n";
	else cout << "NO\n";

}