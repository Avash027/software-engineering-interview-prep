#include <bits/stdc++.h>

using namespace std;


long long sum_of_good_segments(vector<long long> a , long long k , int n) {

	int left_boundary = 0 , right_boundary = 0;

	long long sum_of_segment = 0LL , sum_of_length_of_segments = 0;


	while (right_boundary < n) {

		sum_of_segment += a[right_boundary++];

		while (sum_of_segment > k) {// It is not a good segment so we try to reduce its size
			sum_of_segment -= a[left_boundary];
			left_boundary++;
		}

		long long lenght_of_segment = right_boundary - left_boundary;

		sum_of_length_of_segments += (lenght_of_segment * (lenght_of_segment + 1)) / 2;

	}

	return sum_of_length_of_segments;


}


int main() {
	int n;
	long long k;

	cin >> n >> k;

	if (n == 0 || k == 0) {
		cout << 0 << "\n";
		return 0;
	}

	vector<long long> a(n);

	for (auto&e : a)
		cin >> e;

	cout << sum_of_good_segments(a, k, n) << "\n";

	return 0;
}