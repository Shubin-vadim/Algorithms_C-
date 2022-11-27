#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<bool>used;
vector<vector<int>>matrix;
int cnt_friends = 0;

void dfs(int v) {
	used[v] = true;
	cnt_friends++;
	for (int i = 0; i < matrix[v].size(); i++) {
		if (matrix[v][i] != 0 && !used[i]) {
			dfs(i);
		}
	}

}


int main() {
	int n, s;
	cin >> n >> s;

	int cnt_reber = 0, k;
	matrix.resize(n);
	used.resize(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> k;
			matrix[i].push_back(k);
		}
	}

	dfs(s - 1);

	cout << cnt_friends - 1;
	return 0;
}