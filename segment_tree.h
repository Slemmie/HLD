#pragma once

#include <vector>
#include <cassert>

template <typename node> class Segment_tree {
	
public:
	
	template <typename T> Segment_tree(const std::vector <T>& a) {
		m_size = 1;
		while (m_size < (int)a.size()) {
			m_size <<= 1;
		}
		m_data.resize(m_size << 1);
		m_build(a, 0, 0, m_size);
	}
	
	template <typename T> inline void update(int index, const T& value) {
		assert(index >= 0 && index < m_size);
		m_update(index, value, 0, 0, m_size);
	}
	
	inline node query(int left, int right) const {
		assert(left >= 0 && left < right && right <= m_size);
		return m_query(left, right, 0, 0, m_size);
	}
	
private:
	
	int m_size;
	std::vector <node> m_data;
	
	template <typename T> void m_build(const std::vector <T>& a, int index, int left, int right) {
		if (right - left == 1) {
			if (left < (int)a.size()) {
				m_data[index] = a[left];
			}
			return;
		}
		int mid = (left + right) / 2;
		m_build(a, index * 2 + 1, left, mid);
		m_build(a, index * 2 + 2, mid, right);
		m_data[index] = node::merge(m_data[index * 2 + 1], m_data[index * 2 + 2]);
	}
	
	template <typename T> void m_update(int target_index, const T& value, int index, int left, int right) {
		if (right - left == 1) {
			m_data[index] = value;
			return;
		}
		int mid = (left + right) / 2;
		if (target_index < mid) {
			m_update(target_index, value, index * 2 + 1, left, mid);
		} else {
			m_update(target_index, value, index * 2 + 2, mid, right);
		}
		m_data[index] = node::merge(m_data[index * 2 + 1], m_data[index * 2 + 2]);
	}
	
	node m_query(int target_left, int target_right, int index, int left, int right) const {
		if (left >= target_right || right <= target_left) {
			return { };
		}
		if (left >= target_left && right <= target_right) {
			return m_data[index];
		}
		int mid = (left + right) / 2;
		return node::merge(
		m_query(target_left, target_right, index * 2 + 1, left, mid),
		m_query(target_left, target_right, index * 2 + 2, mid, right));
	}
	
};
