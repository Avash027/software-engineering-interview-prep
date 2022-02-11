#include <bits/stdc++.h>

using namespace std;


int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);

	int n, k;
	long long ans = 0;
	cin >> n >> k;

	vector<long long> a(n);
	map<long long, int> suffix;
	map<long long, int> prefix;

	for (auto&e : a) {
		cin >> e;
		suffix[e]++;
	}

	for (int i = 0; i < n; i++) {
		suffix[a[i]]--;

		if (a[i] % k == 0)
			ans += 1LL * prefix[a[i] / k] * suffix[a[i] * k];

		prefix[a[i]]++;
	}


	cout << ans << "\n";

	return 0;
}