#include <bits/stdc++.h>

using namespace std;


bool is_num_of_sprays_enough(vector<long long>&a ,
                             long long l ,
                             long long w,
                             long long max_extra_sprays) {

	//We initialize it with 0 because we are at 0 initially
	//This variable just keeps the track of the maximum distance we have watered.
	long long current_range = 0;

	for (int e : a) {

		if (e <= current_range) {//That means that the current index is covered so we dont need extra sprays here
			current_range = max(current_range , e + w);
		} else {

			//This is the formula to calculate ceil.
			//Here we are calculating minimum number of sprays required to reach till the current index
			// ceil(a/b) = (a+b-1)/b

			int count = (e - current_range + w - 1) / w;
			max_extra_sprays -= count;
			current_range = max(current_range + count * w , e + w);
		}


		//Once we have watered the entire stretched we can just exit the loop
		if (current_range >= l) break;
	}

	//If we still haven't reached the end yet then we have to add count
	if (current_range < l) {
		int count = (l - current_range + w - 1) / w;
		max_extra_sprays -= count;
	}


	return max_extra_sprays >= 0LL;
}

int main() {
	long long n , l , w;
	cin >> n >> l >> w;
	vector<long long> a(n);


	for (auto&e : a)
		cin >> e;


	sort(begin(a) , end(a));

	long long lo = 0 , hi = 1e17;
	long long ans = 0;

	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		if (is_num_of_sprays_enough(a , l , w, mid)) ans = mid , hi = mid - 1;
		else lo = mid + 1;

	}

	cout << ans << "\n";
}