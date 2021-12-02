#include <iostream>
#include <vector>

int query(const std::vector <std::vector <int>>& graph, const std::vector <int>& a, int node, int parent, int sink) {
	if (node == sink) {
		return a[node];
	}
	int result = -(1 << 30);
	for (int x : graph[node]) {
		if (x != parent) {
			result = std::max(result, query(graph, a, x, node, sink));
		}
	}
	if (result > -(1 << 30)) {
		result = std::max(result, a[node]);
	}
	return result;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	
	int n, q;
	std::cin >> n >> q;
	std::vector <int> a(n);
	for (int& x : a) {
		std::cin >> x;
	}
	std::vector <std::vector <int>> graph(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		std::cin >> u >> v;
		u--, v--;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	for (int i = 0; i < q; i++) {
		int operation;
		std::cin >> operation;
		if (operation == 1) {
			int index, value;
			std::cin >> index >> value;
			a[index - 1] = value;
		} else {
			int u, v;
			std::cin >> u >> v;
			std::cout << query(graph, a, u - 1, -1, v - 1) << " ";
		}
	}
	std::cout << "\n";
	
}
