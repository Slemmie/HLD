#include "HLD.h"

struct Node {
	
	int value = 0;
	
	template <typename T> inline Node& operator = (const T& _value) {
		this->value = _value;
		return *this;
	}
	
	static inline Node merge(const Node& left, const Node& right) {
		return Node { std::max(left.value, right.value) };
	}
	
};

#include <iostream>

int main() {
	std::ios::sync_with_stdio(0); std::cin.tie(0);
	
	int n, q;
	std::cin >> n >> q;
	std::vector <int> a(n);
	for (int& x : a) {
		std::cin >> x;
	}
	HLD <Node, int> hld(a);
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		std::cin >> u >> v;
		hld.push_edge(u - 1, v - 1);
	}
	hld.init();
	for (int i = 0; i < q; i++) {
		int operation;
		std::cin >> operation;
		if (operation == 1) {
			int index, value;
			std::cin >> index >> value;
			hld.update(index - 1, value);
		} else {
			int u, v;
			std::cin >> u >> v;
			std::cout << hld.query(u - 1, v - 1).value << " ";
		}
	}
	std::cout << "\n";
	
}
