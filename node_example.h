#pragma once

// range sum
struct Node {
	
	int value = 0;
	
	template <typename T> inline Node& operator = (const T& _value) {
		this->value = _value;
		return *this;
	}
	
	static inline Node merge(const Node& left, const Node& right) {
		return Node { left.value + right.value };
	}
	
};

// range max
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
