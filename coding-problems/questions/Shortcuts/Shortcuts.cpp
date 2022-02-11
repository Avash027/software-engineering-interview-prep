#include <bits/stdc++.h>


using namespace std;


/**
We have passed distance array by reference
*/
void bfs(int src ,
         vector<vector<int>>& graph,
         vector<bool>& visited ,
         vector<int>& distance)
{
	queue<int> q;
	q.push(src);
	visited[src] = 1;
	distance[src] = 0;

	while (!q.empty())
	{
		int cur = q.front();
		q.pop();

		for (int&to : graph[cur])
		{
			if (!visited[to])
			{
				visited[to] = true;
				q.push(to);
				distance[to] = distance[cur] + 1;
			}
		}
	}
}

/**
* Constructing graph
**/
void makeGraph(vector<vector<int>>& graph, int n) {
	int a;
	for (int i = 1; i <= n; i++) {
		cin >> a;

		if (i != 1) {
			graph[i].push_back(i - 1);
			graph[i - 1].push_back(i);
		}

		if (i != n) {
			graph[i].push_back(i + 1);
			graph[i + 1].push_back(i);
		}

		graph[i].push_back(a);
	}

}

int main() {


	int n, a;
	cin >> n;

	vector<vector<int>> graph(n + 1);
	vector<int> distance(n + 1 , 0);
	vector<bool> visited(n + 1, false);

	makeGraph(graph, n);

	bfs(1, graph, visited, distance);

	cout << distance[n] << "\n";

	return 0;
}