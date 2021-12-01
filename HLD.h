#pragma once

#include "segment_tree.h"

#include <vector>
#include <cassert>

template <typename seg_node, typename node_data> class HLD {
	
public:
	
	HLD(const std::vector <node_data>& _node_data) :
	m_size(_node_data.size()),
	m_node_data(_node_data),
	m_segtree(std::vector <node_data> (0)),
	m_graph(_node_data.size()),
	m_parent(_node_data.size(), -1),
	m_depth(_node_data.size(), 0),
	m_head(_node_data.size(), -1),
	m_heavy(_node_data.size(), -1),
	m_seg_ind(_node_data.size(), -1)
	{ }
	
	inline void push_edge(int u, int v) {
		assert(u >= 0 && u < m_size);
		assert(v >= 0 && v < m_size);
		m_graph[u].push_back(v);
		m_graph[v].push_back(u);
	}
	
	inline void init() {
		m_dfs(0);
		std::vector <node_data> ordered_node_data;
		int seg_ind_cnt = 0;
		m_decompose(0, 0, ordered_node_data, seg_ind_cnt);
		m_segtree = Segment_tree <seg_node> (ordered_node_data);
	}
	
	template <typename T> inline void update(int index, const T& value) {
		assert(index >= 0 && index < m_size);
		m_segtree.update(m_seg_ind[index], value);
	}
	
	seg_node query(int u, int v) {
		seg_node result;
		while (m_head[u] != m_head[v]) {
			if (m_depth[m_head[u]] < m_depth[m_head[v]]) {
				std::swap(u, v);
			}
			result = seg_node::merge(result, m_segtree.query(m_seg_ind[m_head[u]], m_seg_ind[u] + 1));
			u = m_parent[m_head[u]];
		}
		if (m_depth[u] > m_depth[v]) {
			std::swap(u, v);
		}
		return seg_node::merge(result, m_segtree.query(m_seg_ind[u], m_seg_ind[v] + 1));
	}
	
private:
	
	int m_size;
	std::vector <node_data> m_node_data;
	Segment_tree <seg_node> m_segtree;
	std::vector <std::vector <int>> m_graph;
	std::vector <int> m_parent;
	std::vector <int> m_depth;
	std::vector <int> m_head;
	std::vector <int> m_heavy;
	std::vector <int> m_seg_ind;
	
	int m_dfs(int node) {
		int subtree_size = 1, max_child = 0;
		for (int child : m_graph[node]) {
			if (child == m_parent[node]) {
				continue;
			}
			m_parent[child] = node;
			m_depth[child] = m_depth[node] + 1;
			int child_size = m_dfs(child);
			if (child_size > max_child) {
				max_child = child_size;
				m_heavy[node] = child;
			}
			subtree_size += child_size;
		}
		return subtree_size;
	}
	
	void m_decompose(int node, int head, std::vector <node_data>& ordered_node_data, int& seg_ind_cnt) {
		m_head[node] = head;
		ordered_node_data.push_back(m_node_data[node]);
		m_seg_ind[node] = seg_ind_cnt++;
		if (m_heavy[node] != -1) {
			m_decompose(m_heavy[node], head, ordered_node_data, seg_ind_cnt);
		}
		for (int child : m_graph[node]) {
			if (child == m_parent[node] || child == m_heavy[node]) {
				continue;
			}
			m_decompose(child, child, ordered_node_data, seg_ind_cnt);
		}
	}
	
};
