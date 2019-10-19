#ifndef _LIST_H_INCLUDED
#define _LIST_H_INCLUDED

#define MAX 2147483647
#include <iostream>
#include <vector>
#include <stdexcept>
#include <mutex>
#include <algorithm>
#include <thread>
#include <list>
#include "node.hpp"

namespace hashtable {
	class thread_safe_list {
	private:
		node* head;
	public: 
		explicit thread_safe_list(node*);
		explicit thread_safe_list();
		~thread_safe_list();
		int put(node*);
		int remove(int);
		node* check(int);
		node* get_head();
		friend std::ostream& operator << (std::ostream& os, const thread_safe_list& list);
	};
}
#endif
