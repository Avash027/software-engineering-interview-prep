#include <bits/stdc++.h>

using namespace std;

int main() {
	int n, k;
	int max_distinct_colors = 0 , current_distinct_colors = 0;
	map<int, int> freq_colors;

	cin >> n >> k;

	if (n == 0 || k == 0) { //Edge case handling
		cout << 0 << "\n";
		return 0;
	}

	vector<int> arr(n);

	for (int&e : arr)
		cin >> e;


	for (int i = 0; i < k; i++) {
		//Here we are first checking if the color was already present or not
		//Then we update the frequency
		//NOTE: This is post-increment operator
		if (freq_colors[arr[i]]++ == 0) current_distinct_colors++;
	}

	max_distinct_colors = current_distinct_colors;


	for (int i = k; i < n; i++) {

		if (--freq_colors[arr[i - k]] == 0) current_distinct_colors--;
		if (freq_colors[arr[i]]++ == 0) current_distinct_colors++;

		max_distinct_colors = max(max_distinct_colors , current_distinct_colors);
	}

	cout << max_distinct_colors << "\n";

	return 0;
}