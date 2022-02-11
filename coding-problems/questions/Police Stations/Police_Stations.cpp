#include <bits/stdc++.h>


using namespace std;

constexpr long long MOD = 1e9 + 7;

int n, m;

vector<vector<int>> graph;
vector<vector<int>> transpose_graph;
vector<bool> visited;
vector<int> order;

vector<long long> cost;

//Kosarajau's algorithm
void dfs1(int v) {
	visited[v] = true;

	for (int e : graph[v]) {
		if (!visited[e])
			dfs1(e);
	}

	order.push_back(v);
}


void dfs2(int v ,
          long long& min_cost_in_component,
          unordered_map<long long, long long>& nodes_with_min_cost
         ) {

	visited[v] = true;

	min_cost_in_component = min(min_cost_in_component , cost[v]);

	nodes_with_min_cost[cost[v]]++;

	for (int e : transpose_graph[v]) {
		if (!visited[e])
			dfs2(e,
			     min_cost_in_component,
			     nodes_with_min_cost);
	}
}


void initGraph() {
	int a, b;

	cin >> n >> m;

	graph.resize(n + 1);
	transpose_graph.resize(n + 1);
	visited.assign(n + 1, false);
	cost.resize(n + 1);

	for (int i  = 1; i <= n; i++)
		cin >> cost[i];

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		transpose_graph[b].push_back(a);
	}
}

int main() {

	initGraph();


	/***
	* Code below is implementations of Kosarajau's algorithm
	* Check the resources to read about it in detail
	*/
	for (int i = 1; i <= n; i++)
		if (!visited[i]) dfs1(i);


	long long total_cost = 0;
	long long total_ways = 1;

	fill(visited.begin(), visited.end() , false); // Resetting the visited array for second dfs
	reverse(order.begin(), order.end());


	for (int i = 0; i < order.size(); i++) {
		if (visited[order[i]]) continue;

		long long min_cost_in_component = 1e10;//We take 10^10 because max cost can be 10^9

		unordered_map<long long, long long> nodes_with_min_cost;

		dfs2(order[i],
		     min_cost_in_component,
		     nodes_with_min_cost);


		total_cost += min_cost_in_component;
		total_ways = (total_ways * nodes_with_min_cost[min_cost_in_component] % MOD) % MOD;

	}


	cout << total_cost << " " << total_ways << "\n";

	return 0;
}