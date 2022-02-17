#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<char>> A;

vector<vector<int>> make_binary_array(char c) {
	vector<vector<int>> B(n , vector<int>(m));

	for (int i = 0; i < n; i++)
		for (int j  = 0; j < m; j++) {
			if (A[i][j] == c)
				B[i][j] = 1;
			else
				B[i][j] = 0;
		}

	return B;

}

int calculate_largest_square(vector<vector<int>>& B) {
	int ans_c = 1;
	vector<vector<int>> C(n , vector<int> (m, 0));

	for (int i = 0; i < n; i++)
		C[i][0] = B[i][0];

	for (int j = 0; j < m; j++)
		C[0][j] = B[0][j];

	for (int i = 1; i < n; i++)
		for (int j = 1; j < m; j++) {
			if (B[i][j] == 1)
				C[i][j] = min({C[i - 1][j] , C[i][j - 1], C[i - 1][j - 1]}) + 1;
			else
				C[i][j] = 0;

			ans_c = max(ans_c , C[i][j]);
		}

	return ans_c * ans_c;
}


int main() {
	int ans = 1;

	cin >> n >> m;

	A.assign(n, vector<char>(m));


	for (int i = 0; i < n; i++)
		for (int j  = 0; j < m; j++)
			cin >> A[i][j];


	for (char c = 'a'; c <= 'e'; c++) {
		vector<vector<int>> B =  make_binary_array(c);
		ans = max(ans , calculate_largest_square(B));
	}

	cout << ans << "\n";

	return 0;
}