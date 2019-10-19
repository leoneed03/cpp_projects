#ifndef _HASH_H_INCLUDED
#define _HASH_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdexcept>
#include <mutex>
#include <algorithm>
#include <thread>
#include <list>
#include "list.hpp"
namespace hashtable {
    class thread_safe_hashtable {
        private:
		int number_of_elements;
		std::mutex number_of_elements_mutex;
		std::vector<thread_safe_list*>* keys;
		void put(node*);
		void remove(int);
		int hash(int);
        public:
		explicit thread_safe_hashtable(int);
		~thread_safe_hashtable();
		node* check(int);
		int get_number_of_elements();
		void put_vector(const std::vector<int>);
		void remove_vector(const std::vector<int>);
		void check_vector(const std::vector<int>);
		bool check_hashtable();
		friend std::ostream& operator << (std::ostream& os, const thread_safe_hashtable& ht);
    };
}
#endif
