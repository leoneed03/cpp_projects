#ifndef _MATRIX_H_INCLUDED
#define _MATRIX_H_INCLUDED

#include <iostream>
#include <vector>
#include <stdexcept>
#include <mutex>
#include <algorithm>
#include <thread>
#include <list>

namespace hashtable {
    class node {
        private:
		std::mutex mtx;
		int key;
		std::string* str;
		node* next;
        public: 
		explicit node(int, std::string*);
		~node();
		void lock();
		void unlock();
		void set_key(int);
		void set_str(std::string*);
		void set_next(node*);
		int get_key();
		std::string* get_str();
		node* get_next();
		friend std::ostream& operator << (std::ostream& os, const node& nd);
    };
}
#endif
