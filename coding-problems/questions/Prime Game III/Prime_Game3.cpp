#include <bits/stdc++.h>

using namespace std;

vector<int> calculate_spf(int n) {
	vector<int> spf(n);

	for (int i = 1; i < n; i++)
		spf[i] = i;

	for (int i = 4; i < n; i += 2)
		spf[i] = 2;

	for (int i = 3; i * i < n; i++) {
		if (spf[i] != i) continue;

		for (int j = i * i; j < n; j += i)
			if (spf[j] == j)
				spf[j] = i;
	}

	return spf;
}


vector<int> calculate_factors(int n , vector<int>& spf) {
	vector<int> factors;

	while (n != 1) {
		factors.push_back(spf[n]);
		n /= spf[n];
	}

	return factors;
}

long long gcd(long long a , long long b) {
	if (a == 0)
		return b;
	return gcd(b % a, a);
}


int main() {
	int n;
	long long x;
	cin >> n >> x;


	vector<int> spf = calculate_spf(n + 1);
	vector<bool> dp(n + 1, false);


	for (int i  = 2; i <= n; i++) {

		int g = (int)gcd(i, x);
		vector<int> common_factors = calculate_factors(g , spf);

		for (int cp : common_factors)
			dp[i] = dp[i] || !dp[i - cp];

	}


	if (dp[n]) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}