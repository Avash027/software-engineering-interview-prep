#include <bits/stdc++.h>


using namespace std;

/**
Notice that we are passing st by reference
*/
void process_query_1(vector<int>&a, vector<set<int>>& st) {
	int pos, x;

	cin >> pos >> x;

	st[a[pos]].erase(pos);
	a[pos] = x;
	st[x].insert(pos);

}

int process_query_2(vector<set<int>>& st) {
	int l, r, ans = 0;
	cin >> l >> r;

	for (int i = 1; i <= 50; i++) {
		auto index_in_bound = st[i].lower_bound(l);

		//We first check if the iterator is out of bounds or not
		if (index_in_bound != st[i].end() and (*index_in_bound) <= r)
			ans++;
	}

	return ans;
}

int main() {

	int n, q;
	int q_type;

	cin >> n >> q;

	vector<set<int>> st(51);
	vector<int> a(n);


	for (int i = 0; i < n; i++) {
		cin >> a[i];
		st[a[i]].insert(i);
	}


	for (int i = 0; i < q; i++) {
		cin >> q_type;

		if (q_type == 1)
			process_query_1(a, st);
		else {
			int q_ans = process_query_2(st);
			cout << q_ans << "\n";
		}

	}



	return 0;
}