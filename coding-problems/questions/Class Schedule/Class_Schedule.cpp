#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> graph;
vector<int> in;
vector<int> class_score;

vector<int> KahnAlgo() {
	vector<int> ans;

	// The pair will store {class_score[i] , i}
	//This is a max priority queue so the class with higher priority queue will always be on top
	priority_queue<pair<int, int>> pq;

	for (int i = 1; i <= n; i++)
		if (in[i] == 0)
			pq.push({class_score[i], i});

	while (!pq.empty()) {
		int node = pq.top().second;
		pq.pop();
		ans.push_back(node);

		for (int child : graph[node]) {
			--in[child];

			if (in[child] == 0) // All the parents have been processed
				pq.push({class_score[child] , child});
		}
	}

	return ans;
}

void input() {
	int x, y;

	cin >> n >> m;
	graph.resize(n + 1);
	in.assign(n + 1 , 0);
	class_score.assign(n + 1 , 0);


	for (int i = 1; i <= n; i++)
		cin >> class_score[i];

	for (int i = 1; i <= m; i++) {
		cin >> x >> y;
		graph[x].push_back(y);
		in[y]++;
	}
}

int main() {

	input();
	vector<int> ans =  KahnAlgo();

	if ((int)ans.size() != n) cout << -1 << "\n";
	else {
		for (int node : ans)
			cout << node << " ";
		cout << "\n";
	}

	return 0;
}