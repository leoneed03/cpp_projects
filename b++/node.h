#ifndef _NODE_H_INCLUDED
#define _NODE_H_INCLUDED

#include <iostream>
#include <stdio.h>

namespace bplus_tree_namespace
{
	template <class T1, class T2>
	class node {
	private:
	    bool leaf;
	    int key_num;
	    bool* deleted;
	    T1* key;
	    node* parent;
	    node** child;
	    T2* value;
	    node* left;
	    node* right;
	public:
	    node(){}
	    node(int t, bool f) {
			this->leaf = f;
			this->key = new T1[2 * t];
			this->key_num = 0;
			this->deleted = new bool[2 * t];
			for (int i = 0; i < 2 * t; i++)
				this->deleted[i] = false;
			for (int i = 0; i < 2 * t; i++)
				this->key[i] = 0;
			this->parent = nullptr;
			this->child = new node<T1, T2>* [2 * t + 1];
			for (int i = 0; i <= 2 * t; i++) {
				this->child[i] = nullptr;
			}
			this->value = new T2[2 * t];
			this->left = nullptr;
			this->right = nullptr;
		}
		~node(){
			if (deleted)
			   delete []deleted;
			if (key)
				delete []key;
			if (child)
				delete []child;
			if (value)
				delete []value;
		}
		bool get_leaf() {
			return this->leaf;
		}
		int get_key_num() {
			return this->key_num;
		}
		bool* get_deleted(){
			return this->deleted;
		}
		T1* get_key() {
			return this->key;
		}

		node<T1,T2>* get_parent() {
			return this->parent;
		}

		node<T1,T2>** get_child() {
	  		return this->child;
		}

		T2* get_value() {
			return this->value;
		}

		node<T1,T2>* get_left() {
			return this->left;
		}
		node<T1,T2>* get_right() {
			return this->right;
		}
		void set_leaf(bool t) {
			this->leaf = t;
		}
		void set_key_num(int t) {
			this->key_num = t;
		}
		void set_deleted(int pos, bool f){
			this->deleted[pos] = f;
		}
		void set_parent(node<T1,T2>* par) {
			this->parent = par;
		}
		void set_child(int pos, node<T1,T2>* ch) {
			this->child[pos] = ch;
		}
		void set_value(int pos, const T2& val) {
			this->value[pos] = val;
		}

		void set_key(int pos, const T1& key) {
			this->key[pos] = key;
		}

		void set_left(node<T1,T2>* left_sibl) {
			this->left = left_sibl;
		}

		void set_right(node<T1,T2>* right_sibl) {
			this->right = right_sibl;
		}

	};
}
#endif
