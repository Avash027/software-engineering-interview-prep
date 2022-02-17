#include <bits/stdc++.h>

using namespace std;

int n , m;
vector<vector<int>> graph;
vector<vector<int>> dp;
vector<int> in;
string s;


int findAnswer() {
	queue<int> q;
	int cnt = 0, ans = -1;

	//We are selecting all the parent nodes
	for (int i = 1; i <= n; i++)
		if (in[i] == 0) {
			q.push(i);
			dp[i][s[i] - 'a']++;
		}

	while (!q.empty()) {
		int e = q.front();
		q.pop();
		cnt++;

		for (int k : graph[e]) {
			for (int i = 0; i < 26; i++)
				dp[k][i] = max(dp[k][i] , dp[e][i] + (int)(s[k] - 'a' == i));

			in[k]--;
			if (in[k] == 0) //All the parents of k have been processed so we can add it to the queue
				q.push(k);
		}
	}

	if (cnt != n) return ans;

	for (int i = 1; i <= n; i++)
		for (int j = 0; j < 26; j++)
			ans = max(ans , dp[i][j]);

	return ans;

}


int main() {
	int x, y;
	cin >> n >> m >> s;

	graph.resize(n + 1);
	dp.assign(n + 1 , vector<int>(26, 0));
	in.assign(n + 1 , 0);

	s = "#" + s; // This is done to make it 1 based index

	while (m--) {
		cin >> x >> y;
		graph[x].push_back(y);
		in[y]++;
	}

	cout << findAnswer() << "\n";

	return 0;
}