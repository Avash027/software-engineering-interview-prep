#include <bits/stdc++.h>

using namespace std;


int longest_non_decreasing_subsequence(vector<int>&a) {
	vector<int> lnds;

	for (int e : a) {
		if (lnds.size() == 0 || e >= lnds.back())
			lnds.push_back(e);
		else {
			auto index_to_replace = upper_bound(lnds.begin(), lnds.end() , e) - lnds.begin();
			a[index_to_replace] = e;
		}
	}

	return (int)lnds.size();
}

int main() {

	int n;
	cin >> n;

	if (n == 0) {
		cout << 0 << "\n";
		return 0;
	}

	vector<int> a(n);

	for (int&e : a)
		cin >> e;


	int minimum_moves = n - longest_non_decreasing_subsequence(a);

	cout << minimum_moves << "\n";

}