#include <bits/stdc++.h>

using namespace std;

constexpr int INF = (int)1e8;

int n, m, s, k;
vector<vector<int>> graph;
vector<vector<int>> color_index;
vector<vector<int>> cost;

void bfs(int color)
{
	vector<int> dis(n + 1, INF);
	queue<int> q;


	for (int producer_town : color_index[color]) {
		q.push(producer_town);
		dis[producer_town] = 0;
	}

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int&to : graph[cur])
		{
			if (dis[to] > dis[cur])
			{
				q.push(to);
				dis[to] = dis[cur] + 1;
			}
		}
	}

	for (int i = 1; i <= n; i++)
		cost[i][color] = dis[i];
}


void input() {
	int x, y, c;

	cin >> n >> m >> s >> k;

	graph.resize(n + 1);
	color_index.resize(k + 1);
	cost.assign(n + 1 , vector<int>(k + 1 , INF));

	for (int i = 1; i <= n; i++) {
		cin >> c;
		color_index[c].push_back(i);
	}

	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
}

int main() {

	input();

	for (int color = 1 ; color <= k; color++) {
		bfs(color);
	}


	for (int i = 1; i <= n; i++) {
		sort(cost[i].begin(), cost[i].end());
		int ans_i = accumulate(cost[i].begin() , cost[i].begin() + s , 0);
		cout << ans_i << " ";
	}

	return 0;
}