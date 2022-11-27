#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool bfs(int v, int fn, vector<vector<int>>& graph, vector<bool>& used) {
	used[v] = true;
	queue<int>q;
	q.push(v);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < graph[u].size(); i++) {
			int new_v = graph[u][i];
			if (new_v == fn) {
				return true;
			}
			if (!used[new_v]) {
				used[new_v] = true;
				q.push(new_v);
			}
		}
	}
	return false;
}

int main() {
	int n, k, t;
	cin >> n >> t;
	vector<vector<int>>graph(n);
	vector<bool>used(n);
	for (int i = 0; i < n - 1; i++) {
		cin >> k;
		graph[i].push_back(i + k);
	}

	if (bfs(0, t - 1, graph, used)) {
		cout << "YES";
	}
	else {
		cout << "NO";
	}

	return 0;
}