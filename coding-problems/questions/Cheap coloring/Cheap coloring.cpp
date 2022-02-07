#include <bits/stdc++.h>


using namespace std;



/***
* To make calculations easier
* X = 0
* Y = 1
* Z = 2
*/

int main() {
	int n, cost_x, cost_y, cost_z;
	string s;

	cin >> n >> s;
	cin >> cost_x >> cost_y >> cost_z;

	vector<vector<int>> dp(n , vector<int>(3 , 0));

	//Base case
	dp[0][0] = (s[0] == 'X' ? 0 : cost_x);
	dp[0][1] = (s[0] == 'Y' ? 0 : cost_y);
	dp[0][2] = (s[0] == 'Z' ? 0 : cost_z);


	for (int i = 1; i < n; i++) {


		//For color X
		if (s[i] == 'X') dp[i][0] = 0;
		else dp[i][0] = cost_x;

		dp[i][0] += min(dp[i - 1][1] , dp[i - 1][2]);

		//For color Y
		if (s[i] == 'Y') dp[i][1] = 0;
		else dp[i][1] = cost_y;

		dp[i][1] += min(dp[i - 1][0] , dp[i - 1][2]);

		//For color Z
		if (s[i] == 'Z') dp[i][2] = 0;
		else dp[i][2] = cost_z;

		dp[i][2] += min(dp[i - 1][0] , dp[i - 1][1]);
	}

	cout << min({dp[n - 1][0] , dp[n - 1][1] , dp[n - 1][2]}) << "\n";

	return 0;
}