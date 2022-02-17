#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> teams;
vector<bool> visited;

bool dfs(int v, int team_num) {

	visited[v] = true;
	teams[v] = team_num;

	for (int to : graph[v]) {
		if (!visited[to]) {
			if (dfs(to , team_num ^ 1) == false) return false;
		} else {
			if (teams[v] == teams[to]) return false;
		}

	}

	return true;
}

int main() {

	int x, y;
	cin >> n >> m;

	if (m == 0) {
		cout << "YES\n";
		return 0;
	}

	graph.resize(n + 1);
	teams.assign(n + 1, 0);
	visited.assign(n + 1, false);


	for (int i = 0; i < m; i++) {
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	bool isPossible =  dfs(1, 0);

	if (isPossible) cout << "YES\n";
	else cout << "NO\n";


	return 0;
}