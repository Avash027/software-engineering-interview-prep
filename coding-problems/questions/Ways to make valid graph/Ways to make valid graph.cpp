#include <bits/stdc++.h>

using namespace std;


constexpr int MOD = 1e9 + 7;

vector<int>	graph[100001];
vector<int> vis(100001 , 0);
int n , m, a, b;


/**
* This is code for binary exponentiation
* However the constraints can allow linear exponentiation as well
*/
int mod_pow(long long a, long long b, long long mod) {
	long long result = 1;

	while (b > 0) {
		if (b & 1) result = 1LL * result * a % mod;
		a = 1LL * a * a % mod;
		b >>= 1;
	}

	if (result < 0) result += MOD;

	return result;
}


void inputGraph() {
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
}

/**
* vis[] stores two values 1 and 2
* vis[v] = 1 means we have visited the node and we want to check wether this node is present in any cycle
* vis[v] = 2 means we have visited the node and we dont want to wether is is present in cycle or not
*/

void countCycles(int v, int par , int& num_of_cycles) {
	vis[v] = 1;

	for (int to : graph[v]) {
		if (!vis[to])
			countCycles(to, v , num_of_cycles);
		else if (vis[to] == 1 && to != par)
			num_of_cycles++;
	}

	vis[v] = 2;

}


int count_valid_components() {

	bool isValidGraph = true;
	int num_of_components = 0;

	for (int i = 1; i <= n; i++) {
		if (vis[i] != 0) continue; // We have visited this component so we skip it

		int num_of_cycles = 0;

		countCycles(i, -1 , num_of_cycles);

		if (num_of_cycles == 0  || num_of_cycles > 1) {
			isValidGraph = false;
			break;
		} else num_of_components++;

	}


	if (!isValidGraph || num_of_components == 0) return 0;
	return num_of_components;
}


int main() {


	inputGraph();
	int num_of_valid_components = count_valid_components();

	if (num_of_valid_components == 0) {
		cout << -1 << "\n";
		return 0;
	}


	cout << mod_pow(2 , num_of_valid_components, MOD) << "\n";

	return 0;
}