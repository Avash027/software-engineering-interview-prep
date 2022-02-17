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


int calculate_hpf(int n , vector<int>& spf) {
	int hpf = 0;

	while (n != 1) {
		hpf = max(hpf , spf[n]);
		n /= spf[n];
	}

	return hpf;
}


int main() {
	int n;
	cin >> n;


	vector<int> spf = calculate_spf(n + 1);
	vector<bool> dp(n + 1, false);

	for (int i  = 2; i <= n; i++) {
		int hpf = calculate_hpf(i, spf);


		dp[i] = (!dp[i - spf[i]])  || (!dp[i - hpf]);
	}


	if (dp[n]) cout << "YES\n";
	else cout << "NO\n";

	return 0;
}