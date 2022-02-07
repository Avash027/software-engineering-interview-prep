#include <bits/stdc++.h>


using namespace std;



/***
* Implementation for disjoin set union
* It implements Path compression and union by rank
* Check the resource link to understand the implementation
*/
struct Dsu
{
	vector<int> par;
	vector<int> rank;

	Dsu(int size)
	{
		par.resize(size);
		rank.assign(size , 1);
		iota(begin(par), end(par) , 0);
	}

	int findParent(int node) {
		if (node == par[node]) return node;
		return par[node] = findParent(par[node]);
	}

	bool areConnected(int u, int v) {
		return findParent(u) == findParent(v);
	}

	void mergeVertices(int u , int v)
	{
		u = findParent(u);
		v = findParent(v);

		if (u == v) return;

		if (rank[u] > rank[v])
		{
			par[v] = u;
			rank[u] += rank[v];
		}
		else
		{
			par[u] = v;
			rank[v] += rank[u];
		}
	}
};


struct Edge
{
	int x;
	int y;
	int wt;
	bool isQuery;
	int queryIndex;

	/***
	* We use operator overloading. You can also use comparator to sort edges by
	* weight.
	*/
	bool operator <(Edge other) {
		return wt < other.wt;
	}
};


void findAnswer(vector<Edge>&v , vector<string>& ans , int n) {
	Dsu dsu(n + 1);

	for (auto edge : v) {

		if (edge.isQuery) {
			if (dsu.areConnected(edge.x , edge.y))
				ans[edge.queryIndex] = "NO";
			else
				ans[edge.queryIndex] = "YES";
		} else {
			if (!dsu.areConnected(edge.x, edge.y))
				dsu.mergeVertices(edge.x , edge.y);
		}
	}
}

int main() {


	int n, m, q;
	cin >> n >> m >> q;



	vector<Edge> v(m + q);
	vector<string> ans(q);


	for (int i = 0; i < m; i++) {
		cin >> v[i].x >> v[i].y >> v[i].wt;
		v[i].isQuery = false;
		v[i].queryIndex = -1;
	}

	for (int i = m , j = 0; i < m + q; i++ , j++) {
		cin >> v[i].x >> v[i].y >> v[i].wt;
		v[i].isQuery = true;
		v[i].queryIndex = j;
	}


	sort(begin(v), end(v));

	findAnswer(v, ans, n);


	for (int i = 0; i < q; i++)
		cout << ans[i] << "\n";

	return 0;
}