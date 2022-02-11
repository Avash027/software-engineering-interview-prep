#include <bits/stdc++.h>

using namespace std;

string s, p;
int n , m;
vector<int> indices;


bool is_P_in_S(const string&s1) {
	int i = 0 , j = 0;
	int n1 = s1.size();

	while (i < n1 and j < m) {
		if (s1[i] == p[j]) i++, j++;
		else i++;
	}

	return (j >= m); //This means all characters of p is in s1
}


int binary_search() {
	int lo = 0 , hi = n - 1;
	int ans = -1;


	while (lo <= hi) {
		int mid = (lo + hi) / 2;

		string s1;
		unordered_map<int, bool> to_exclude;

		for (int i = 0; i <= mid; i++)
			to_exclude[indices[i]] = true;

		for (int i = 0; i < n; i++ )
			if (!to_exclude[i])
				s1.push_back(s[i]);



		if (is_P_in_S(s1)) {
			ans = mid;
			lo = mid + 1;
		}
		else {
			hi = mid - 1;
		}

	}

	return ans + 1;//Conveting it to 1 based index
}


int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);
	cin >> s >> p;

	n = s.size();
	m = p.size();
	indices.resize(n);

	for (int i = 0; i < n; i++) {
		cin >> indices[i];
		indices[i]--; // We are converting one based index to 0 based index
	}

	cout << binary_search() << "\n";


	return 0;
}