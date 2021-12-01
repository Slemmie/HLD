#pragma once

#include <vector>
#include <cassert>

class LCA {
	
public:
	
	LCA(int _size) :
	m_size(_size),
	m_graph(_size)
	{ }
	
	inline void push_edge(int u, int v) {
		assert(u >= 0 && u < m_size);
		assert(v >= 0 && v < m_size);
		m_graph[u].push_back(v);
		m_graph[v].push_back(u);
	}
	
	void init(int root = 0) {
		m_up = std::vector <std::vector <int>> (m_size, std::vector <int> (1, -1));
		m_depth = std::vector <int> (m_size, 0);
		m_dfs(root);
		int max_depth = 0;
		for (int i = 0; i < m_size; i++) {
			max_depth = std::max(max_depth, m_depth[i]);
		}
		m_log_height = 0;
		while ((1 << m_log_height) <= max_depth) {
			m_log_height++;
		}
		for (int i = 0; i < m_size; i++) {
			m_up[i].resize(m_log_height, -1);
		}
		for (int b = 1; b < m_log_height; b++) {
			for (int i = 0; i < m_size; i++) {
				if (m_up[i][b - 1] != -1) {
					m_up[i][b] = m_up[m_up[i][b - 1]][b - 1];
				}
			}
		}
	}
	
	int query(int u, int v) {
		if (u == v) {
			return u;
		}
		if (m_depth[u] < m_depth[v]) {
			std::swap(u, v);
		}
		int dist = m_depth[u] - m_depth[v];
		for (int b = 0; b < m_log_height; b++) {
			if ((dist >> b) & 1) {
				u = m_up[u][b];
			}
		}
		assert(m_depth[u] == m_depth[v]);
		if (u == v) {
			return u;
		}
		for (int b = m_log_height - 1; b >= 0; b--) {
			if (m_up[u][b] != m_up[v][b]) {
				u = m_up[u][b];
				v = m_up[v][b];
			}
		}
		assert(m_up[u][0] == m_up[v][0]);
		assert(m_up[u][0] != -1);
		return m_up[u][0];
	}
	
private:
	
	int m_size;
	std::vector <std::vector <int>> m_graph;
	std::vector <int> m_depth;
	std::vector <std::vector <int>> m_up;
	int m_log_height;
	
	void m_dfs(int node, int parent = -1) {
		m_up[node][0] = parent;
		for (int child : m_graph[node]) {
			if (child != parent) {
				m_depth[child] = m_depth[node] + 1;
				m_dfs(child, node);
			}
		}
	}
	
};
