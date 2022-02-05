#include <bits/stdc++.h>

using namespace std;

bool can_split_into_atmost_K_segments(vector<long long>&a,
                                      long long max_sum_of_each_segment,
                                      int k
                                     ) {

	int num_of_segments = 1;
	long long sum_of_each_segment = 0;


	for (long long e : a) {
		if (e > max_sum_of_each_segment) return false;

		if (sum_of_each_segment + e > max_sum_of_each_segment) {
			sum_of_each_segment = 0;
			num_of_segments++;
		}

		sum_of_each_segment += e;
	}

	return num_of_segments <= k;

}

int main() {
	int n, k;
	cin >> n >> k;

	if (n == 0 || k == 0) {
		cout << 0 << "\n";
		return 0;
	}

	vector<long long> a(n);

	for (auto&e : a)
		cin >> e;


	long long lo = 0 , hi = 1e17;
	long long ans = 0;

	while (lo <= hi) {
		long long mid = lo + (hi - lo) / 2;

		if (can_split_into_atmost_K_segments(a , mid , k)) ans = mid , hi = mid - 1;
		else lo = mid + 1;
	}

	cout << ans << "\n";

	return 0;
}