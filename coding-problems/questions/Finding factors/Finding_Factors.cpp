#include <bits/stdc++.h>

using namespace std;

vector<int> find_divisors(int n) {
	vector<int> divisors;

	for (int i  = 1; i * i <= n; i++) {
		if (n % i != 0) continue;
		divisors.push_back(i);
		if (i * i != n) divisors.push_back(n / i); // to remove duplication
	}

	return divisors;
}

int process_query_1(int l , int r , vector<int>& divisors) {

	int lb = 0 , rb = (int)divisors.size() - 1;
	int ans = -1;

	while (lb <= rb) {
		int mid = (lb + rb) / 2;

		int d = divisors[mid];

		if (d >= l and d <= r) ans = d , rb = mid - 1;
		else if (d < l) lb = mid + 1;
		else rb = mid - 1;
	}

	return ans;
}


int process_query_2(int l , int r , vector<int>& divisors) {

	int lb = 0 , rb = (int)divisors.size() - 1;
	int ans = -1;

	while (lb <= rb) {
		int mid = (lb + rb) / 2;

		int d = divisors[mid];

		if (d >= l and d <= r) ans = d , lb = mid + 1;
		else if (d < l) lb = mid + 1;
		else rb = mid - 1;
	}

	return ans;
}


int main() {
	
	int n, q;
	cin >> n >> q;

	vector<int> divisors = find_divisors(n);

	sort(begin(divisors), end(divisors));

	while (q--) {
		int q_type, l, r, q_ans;
		cin >> q_type >> l >> r;

		if (q_type == 1)
			q_ans = process_query_1(l, r, divisors);
		else
			q_ans = process_query_2(l, r, divisors);

		cout << q_ans << "\n";
	}



	return 0;
}