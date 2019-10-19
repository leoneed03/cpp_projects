#include "hashtable.hpp"
#include <vector>
namespace hashtable {
	thread_safe_hashtable::thread_safe_hashtable(int my_size) {
		number_of_elements = 0;
		keys = new std::vector<thread_safe_list*>(my_size);
		for (int i = 0; i < my_size; i++) {
			(*keys)[i] = new thread_safe_list();
		}
	}
	thread_safe_hashtable::~thread_safe_hashtable() {
		for (int i = 0; i < (*keys).size(); i++) {
			delete (*keys)[i];
		} 
		delete keys;
	}
	int thread_safe_hashtable::get_number_of_elements() {
		int res = 0;
		{	
			std::lock_guard<std::mutex> g_lock(number_of_elements_mutex);
			res = number_of_elements;
		}
		return res;
	}
	void thread_safe_hashtable::put_vector(const std::vector<int> my_vect) {
		for (int i = 0; i < my_vect.size(); i++) {
			this -> put(new node(my_vect[i], new std::string("HT")));
		}
	}
	void thread_safe_hashtable::remove_vector(const std::vector<int> vect) {
		for (int i = 0; i < vect.size(); i++) {
			this -> remove(vect[i]);
		}
	}
	void thread_safe_hashtable::check_vector(const std::vector<int> vect) {
		for (int i = 0; i < vect.size(); i++) {
			this -> check(vect[i]);
		}
	}
	int thread_safe_hashtable::hash(int key) {
		return (key % (*keys).size());
	}
	void thread_safe_hashtable::put(node* nd) {
		int res = (*keys)[ hash(nd->get_key()) ] -> put(nd);
		std::lock_guard<std::mutex> g_lock(number_of_elements_mutex);
		number_of_elements += res;
	}
	void thread_safe_hashtable::remove(int my_key) {
		int res = (*keys)[ hash(my_key) ] -> remove(my_key);
		std::lock_guard<std::mutex> g_lock(number_of_elements_mutex);
		number_of_elements -= res;
	}
	node* thread_safe_hashtable::check(int my_key) {
		return (*keys)[ hash(my_key) ] -> check(my_key);
	}
	bool thread_safe_hashtable::check_hashtable() {
		for (int i = 0; i < (*keys).size(); i++) {
			auto curr = (*keys)[i] -> get_head();
			while (curr = curr -> get_next()) {
				if (curr -> get_key() % (*keys).size() != i)
					return false;
			}
		}
		return true;
	}
	std::ostream& operator << (std::ostream& os, const thread_safe_hashtable& ht) {
		os << (*ht.keys).size() << std::endl;
		for (int i = 0; i < (*ht.keys).size(); i++ ) {
			os << "THIS IS " << i << ":   ";
			thread_safe_list* x = (*(ht.keys))[i];
			os << *x;
			os << std::endl << "ENDED" << std::endl;
		}
	}
}
