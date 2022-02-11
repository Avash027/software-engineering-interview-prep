#include <bits/stdc++.h>


using namespace std;

constexpr long long MOD = 1e9 + 7;

void dfs(int v ,
         int parent,
         vector<vector<int>>& adj,
         vector<vector<long long>>& dp) {

	long long ways_to_assign_0 = 1;
	long long ways_to_assign_1 = 1;


	for (int e : adj[v]) {
		if (e == parent) continue;

		//We will first evaluate the children
		dfs(e , v , adj , dp);

		//At this point we have evaluated all children of v

		ways_to_assign_1 = (ways_to_assign_1 * dp[e][0] % MOD) % MOD;
		ways_to_assign_0 = (ways_to_assign_0 * (dp[e][1] + dp[e][0]) % MOD) % MOD;
	}

	/**
	*Notice that we are also covering the base case here. In case v is a leaf node then dp[v][0] = dp[v][1]=1
	*/
	dp[v][0] = ways_to_assign_0;
	dp[v][1] = ways_to_assign_1;

}


int main() {

	int n, a, b;
	cin >> n ;

	vector<vector<int>> adj(n + 1);
	vector<vector<long long>> dp(n + 1 , vector<long long>(2, 0));


	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	dfs(1, -1, adj, dp);

	long long ans = (dp[1][0] % MOD + dp[1][1] % MOD) % MOD;

	cout << ans << "\n";


	return 0;
}