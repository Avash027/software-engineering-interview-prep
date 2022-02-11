#include <bits/stdc++.h>

using namespace std;


int main() {


	int n;
	long long k , ans = 0;
	cin >> n >> k;

	vector<long long> a(n);
	set<pair<long long, int>> st;

	for (auto&e : a)
		cin >> e;

	int l = 0 , r = 0;

	while (r < n) {
		st.insert({a[r] , r}); // Set does not allow duplicate values so we also store the index
		//to allow store same values
		r++;

		while (!st.empty()) {
			int mn = st.begin()->first;
			int mx = st.rbegin()->first;

			if (mx - mn <= k) break;
			st.erase({a[l], l});
			l++;
		}

		ans += (long long)(r - l);

	}

	cout << ans << "\n";
	return 0;
}