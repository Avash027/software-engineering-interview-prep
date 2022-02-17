#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> tree;
vector<int> dangerous;

int ans = 0;

void dfs(int v , int parent, int count) {


	if (dangerous[v] == 1) count++;
	else count = 0;
	if (count > m) return;

	bool isLeaf = true;

	for (int to : tree[v]) {
		if (to == parent) continue;

		isLeaf = false;
		dfs(to, v, count);
	}

	if (isLeaf)
		ans++;

}

void input() {
	int x, y;

	cin >> n >> m;
	tree.resize(n + 1);
	dangerous.resize(n + 1);

	for (int i = 1; i <= n; i++)
		cin >> dangerous[i];


	for (int i = 0; i < n - 1; i++) {
		cin >> x >> y;
		tree[x].push_back(y);
		tree[y].push_back(x);
	}

}

int main() {

	input();
	dfs(1, -1, 0);

	cout << ans << "\n";
	return 0;
}