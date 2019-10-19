#include "node.hpp"

namespace hashtable {
	node::node(int new_key, std::string* new_str): key(new_key), str(new_str), next(nullptr) {};
	node::~node() { 
		delete str;
	}
	void node::lock() {
		mtx.lock();
	}
	void node::unlock() {
		mtx.unlock();
	}
	void node::set_key(int new_key) {
		key = new_key;
	}
	void node::set_str(std::string* new_str) {
		delete str;
		str = new_str;
	}
	void node::set_next(node* nd) {
		next = nd;
	}
	int node::get_key() {
		return key;
	}
	std::string* node::get_str() {
		return str;
	}
	node* node::get_next() {
		return next;
	}
	std::ostream& operator << (std::ostream& os, const node& nd) {
		os << nd.key << " ";
		if (nd.str) 
			os << *(nd.str) << " ";
		else 
			os << " ";
	}
}

