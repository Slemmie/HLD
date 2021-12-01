#include <bits/stdc++.h>

int main() {
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution <int> dis(0, 1 << 30);
	int n = dis(gen) % 100 + 2;
	int q = dis(gen) % 100 + 1;
	std::cout << n << " " << q << "\n";
	for (int i = 0; i < n; i++) {
		std::cout << dis(gen) % 99 + 1 << " \n"[i + 1 == n];
	}
	std::vector <int> ord(n);
	std::iota(ord.begin(), ord.end(), 0);
	srand(dis(gen) % 123456);
	std::random_shuffle(ord.begin(), ord.end());
	std::vector <std::pair <int, int>> edges;
	for (int i = 1; i < n; i++) {
		int par = ord[dis(gen) % i];
		edges.emplace_back(ord[i] + 1, par + 1);
		if (dis(gen) % 2) {
			std::swap(edges.back().first, edges.back().second);
		}
	}
	std::random_shuffle(edges.begin(), edges.end());
	for (auto p : edges) {
		std::cout << p.first << " " << p.second << "\n";
	}
	for (int i = 0; i < q; i++) {
		int o = dis(gen) % 2;
		std::cout << o + 1 << " ";
		if (o == 0) {
			std::cout << dis(gen) % n + 1 << " " << dis(gen) % 99 + 1 << "\n";
		} else {
			int a = dis(gen) % n;
			int b = dis(gen) % n;
			while (a == b) {
				b = dis(gen) % n;
			}
			std::cout << a + 1 << " " << b + 1 << "\n";
		}
	}
	
}
