#include <bits/stdc++.h>

using namespace std;


struct Element
{
	string word;
	long long cost;
};

const long long INF = 1e11;

int main() {
	ios_base::sync_with_stdio(false), cin.tie(NULL);

	int n;
	cin >> n;

	vector<Element> a(n);
	vector<vector<long long>> dp(n , vector<long long>(2 , INF)); //Any large value will be good

	for (auto&e : a)
		cin >> e.word >> e.cost;

	//Defining the base case

	dp[0][1] = 0;
	dp[0][0] = a[0].cost;


	for (int i = 1; i < n; i++) {

		string cur = a[i].word;
		string prev = a[i - 1].word;

		string cur_reverse = a[i].word;
		string prev_reverse = a[i - 1].word;

		reverse(cur_reverse.begin(), cur_reverse.end());
		reverse(prev_reverse.begin(), prev_reverse.end());


		//1st Case
		if (cur.compare(prev) >= 0)
			dp[i][1] = min(dp[i - 1][1] , dp[i][1]);

		//2nd Case
		if (cur.compare(prev_reverse) >= 0)
			dp[i][1] = min(dp[i - 1][0], dp[i][1]);

		//3rd Case
		if (cur_reverse.compare(prev) >= 0)
			dp[i][0] = min(dp[i - 1][1] + a[i].cost , dp[i][0]);

		//4th Case
		if (cur_reverse.compare(prev_reverse) >= 0)
			dp[i][0] = min(dp[i - 1][0] + a[i].cost , dp[i][0]);
	}



	long long ans = min(dp[n - 1][0] , dp[n - 1][1]);

	if (ans >= INF) ans = -1; //There is no way to sort the strings

	cout << ans << "\n";

	return 0;
}