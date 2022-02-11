#include <bits/stdc++.h>

using namespace std;


int main() {
	

	int n;
	long long sum = 0 , cur_sum = 0, pref_sum = 0;
	long long ans = 0;

	cin >> n;
	vector<long long> a(n);
	vector<long long> suffix(n , 0);

	for (auto&e : a) {
		cin >> e;
		sum += e;
	}

	if (sum % 3 != 0) {
		cout << 0 << "\n";
		return 0;
	}


	for (int i = n - 1; i >= 0; i--) {
		cur_sum += a[i];

		if (i == n - 1)
			suffix[i] = cur_sum == sum / 3;
		else
			suffix[i] = suffix[i + 1] + (long long)(cur_sum == sum / 3);
	}



	for (int i = 0; i < n - 2; i++) {
		pref_sum += a[i];

		if (pref_sum == sum / 3)
			ans += suffix[i + 2];
	}

	cout << ans << "\n";

	return 0;
}