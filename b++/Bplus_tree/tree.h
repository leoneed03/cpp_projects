#ifndef _TREE_H_INCLUDED
#define _TREE_H_INCLUDED

#include <iostream>
#include "node.h"
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

namespace bplus_tree_namespace
{
	template <class T1, class T2>
	class Bptree {
	private:
	    int t;
	    node<T1,T2>* root;
        void update(node<T1,T2>* Node) {
            T1 Key = min_key(Node);
            while (Node) {
                int i = 0;
                for (; i < Node -> get_key_num(); i++) {
                    if (Node -> get_child()[i + 1]) {
                        Node -> get_child()[i + 1] -> set_parent(Node);
                        Node -> set_key(i, min_key(Node -> get_child()[i + 1]));
                    }
                }
                Node = Node -> get_parent();
            }
        }
        
        void lazy_insert_left(node<T1,T2>* Node, node<T1,T2>* left, int pos, const T1& temp, const T2& val) {
            int key_num = Node -> get_key_num() - 1;
            if (Node -> get_key_num() < 2 * t - 1) {
                Node -> set_key(pos, temp);
                Node -> set_value(pos, val);
                Node -> set_key_num(Node -> get_key_num() + 1);
                return;
            }
            T1 s = Node -> get_key()[0];
            T2 v = Node -> get_value()[0];
            for (int i = 0; i < pos - 1; i++) {
                Node -> set_key(i, Node -> get_key()[i + 1]);
                Node -> set_value(i, Node -> get_value()[i + 1]);
            }
            Node -> set_key(pos - 1, temp);
            Node -> set_value(pos - 1, val);
            if (Node != left)
                lazy_insert_left(Node -> get_left(), left, Node -> get_left() -> get_key_num(), s, v);
            update(Node);
            return;
        }
        
        void lazy_insert_right(node<T1,T2>* Node, node<T1,T2>* right, int pos, const T1& temp, const T2& val) {
            int key_num = Node -> get_key_num() - 1;
            if (Node -> get_key_num() < 2 * t - 1) {
                for (int i = Node -> get_key_num(); i > 0; i--) {
                    Node -> set_key(i, Node -> get_key()[i - 1]);
                    Node -> set_value(i, Node -> get_value()[i - 1]);
                }
                Node -> set_key_num(Node -> get_key_num() + 1);
                Node -> set_key(0, temp);
                Node -> set_value(0, val);
                return;
            }
            T1 s = Node -> get_key()[key_num];
            T2 v = Node -> get_value()[key_num];
            for (int i = key_num; i > pos; i--) {
                Node -> set_key(i, Node -> get_key()[i - 1]);
                Node -> set_value(i, Node -> get_value()[i - 1]);
            }
            if (temp < Node -> get_key()[key_num]) {
                Node -> set_key(pos, temp);
                Node -> set_value(pos, val);
                if (Node != right)
                    lazy_insert_right(Node -> get_right(), right, 0, s, v);
            } else lazy_insert_right(Node -> get_right(), right, 0, temp, val);
            update(Node);
            return;
        }
        
        bool check_for_deleted(node<T1,T2>* for_check) {
            for (int i = 0; i < for_check -> get_key_num(); i++) {
                if (for_check -> get_deleted()[i])
                    return true;
            }
            return false;
        }
        
        void insert_in_deleted(node<T1,T2>* for_insert, const T1& key, const T2& value) {
            int pos = 0;
            for (; pos < for_insert -> get_key_num() && key >= for_insert -> get_key()[pos]; pos++) {}
            if (pos == -1)
                return;
            if (for_insert -> get_deleted()[pos]) {
                for_insert -> set_key(pos, key);
                for_insert -> set_value(pos, value);
                for_insert -> set_deleted(pos, false);
                return;
            }
            bool flag = false;
            int cur_pos = -1;
            for (int i = pos; i >= 0; i--) {
                if (for_insert -> get_deleted()[i]) {
                    flag = true;
                    cur_pos = i;
                    break;
                }
            }
            if (flag) {
                for (int i = cur_pos; i < pos; i++) {
                    for_insert -> set_key(i, for_insert -> get_key()[i + 1]);
                    for_insert -> set_value(i, for_insert -> get_value()[i + 1]);
                }
                for_insert -> set_deleted(cur_pos, false);
                for_insert -> set_key(pos, key);
                for_insert -> set_value(pos, value);
                update(for_insert);
                return;
            }
            bool fl = false;
            int cur = -1;
            for (int i = pos; i < for_insert -> get_key_num(); i++) {
                if (for_insert -> get_deleted()[i]) {
                    fl = true;
                    cur = i;
                    break;
                }
            }
            if (fl) {
                for (int i = cur; i > pos; i--) {
                    for_insert -> set_key(i, for_insert -> get_key()[i - 1]);
                    for_insert -> set_value(i, for_insert -> get_value()[i - 1]);
                }
                for_insert -> set_deleted(cur, false);
                for_insert -> set_key(pos, key);
                for_insert -> set_value(pos, value);
                update(for_insert);
                return;
            }
        }
	    
        void split(node<T1,T2>* Node) {
            node<T1,T2>* new_node = new node<T1,T2>(this -> t, Node -> get_leaf());
            if (Node -> get_right())
                new_node -> set_right(Node -> get_right());
            if (Node -> get_right())
                Node -> get_right() -> set_left(new_node);
            Node -> set_right(new_node);
            new_node -> set_left(Node);
            int temp_key = Node -> get_key()[t];
            new_node -> set_key_num(t - 1);
            Node -> set_key_num(t);
            for (int i = 0; i < new_node -> get_key_num(); i++) {
                new_node -> set_key(i, Node -> get_key()[i + t + 1]);
                new_node -> set_value(i, Node -> get_value()[i + t + 1]);
                new_node -> set_child(i, Node -> get_child()[i + t + 1]);
                if (new_node -> get_child()[i])
                    new_node -> get_child()[i] -> set_parent(new_node);
            }
            new_node -> set_child(new_node -> get_key_num(), Node -> get_child()[2 * t]);
            
            if (new_node -> get_child()[new_node -> get_key_num()])
                new_node -> get_child()[new_node -> get_key_num()] -> set_parent(new_node);

            if (Node -> get_leaf()) {
                new_node -> set_key_num(new_node -> get_key_num() + 1);
                new_node -> set_leaf(true);
                for (int i = new_node -> get_key_num() - 1; i > 0; i--) {
                    new_node -> set_key(i, new_node -> get_key()[i - 1]);
                    new_node -> set_value(i, new_node -> get_value()[i - 1]);
                }
                new_node -> set_key(0, Node -> get_key()[t]);
                new_node -> set_value(0, Node -> get_value()[t]);
            }
            
            if (Node == this -> root) {
                this -> root = new node<T1,T2>(t,false);
                this -> root -> set_key(0, temp_key);
                this -> root -> set_child(0, Node);
                this -> root -> set_child(1, new_node);
                this -> root -> set_key_num(1);
                Node -> set_parent(this -> root);
                new_node -> set_parent(this -> root);
            } else {
                node<T1,T2>* parent = Node -> get_parent();
                new_node -> set_parent(parent);
                int pos = 0;
                while (pos < parent -> get_key_num() && parent -> get_key()[pos] < temp_key)
                    ++pos;
                for (int i = parent -> get_key_num(); i > pos; i--) {
                    parent -> get_key()[i] = parent -> get_key()[i - 1];
                }
                for (int i = parent -> get_key_num() + 1; i > pos + 1; i--) {
                    parent -> get_child()[i] = parent -> get_child()[i - 1];
                }
                parent -> set_key(pos, temp_key);
                parent -> set_child(pos + 1, new_node);
                parent -> set_key_num(parent -> get_key_num() + 1);
                if (parent -> get_key_num() == 2 * t)
                    split(parent);
            }
        }
            
        int find_pos(node<T1,T2>* find_in, const T1& key) {
            int pos = 0;
            for (pos = 0; pos < find_in -> get_key_num(); pos++) {
                if (find_in -> get_key()[pos] == key)
                    return pos;
            }
            return -1;
        }
        
	    T1 min_key(node<T1,T2>* Node) {
		    T1 Key = Node -> get_key()[0];
		    while(Node -> get_child()[0]) {
		        Node = Node -> get_child()[0];
		    }
		    Key = Node -> get_key()[0];
		    return Key;
	        }
	        node<T1,T2>* fix_node(node<T1,T2>* for_fix) {
		    int t = this -> t;
		    if (for_fix -> get_key_num() >= t - 1)
		        return for_fix -> get_left();
		    auto left = for_fix -> get_left();
		    auto right = for_fix -> get_right();
		    int c = t - 1 - for_fix -> get_key_num();
		    if (left && left -> get_key_num() - t + 1 >= c) {
		        for (int i = t - 1; i >= c ; i--) {
		            for_fix -> set_key(i, for_fix -> get_key()[i - c]);
		            for_fix -> set_value(i, for_fix -> get_value()[i - c]);
		        }
		        for (int i = 0; i < c; i++) {
		            for_fix -> set_key(i, left -> get_key()[left -> get_key_num() - c + i]);
		            for_fix -> set_value(i, left -> get_value()[left -> get_key_num() - c + i]);
		        }
		        for_fix -> set_key_num(for_fix -> get_key_num() + c);
		        left -> set_key_num(left -> get_key_num() - c);
		        update(for_fix);
		        return left;
		    }
		    if (right && right -> get_key_num() - t + 1 >= c) {
		        for (int i = 0; i < c; i++) {
		            for_fix -> set_key(i + for_fix -> get_key_num(), right -> get_key()[i]);
		            for_fix -> set_value(i + for_fix -> get_key_num(), right -> get_value()[i]);
		        }
		        for (int i = 0; i < right -> get_key_num() - c; i++) {
		            right -> set_key(i, right -> get_key()[i + c]);
		            right -> set_value(i, right -> get_value()[i + c]);
		        }
		        for_fix -> set_key_num(for_fix -> get_key_num() + c);
		        right -> set_key_num(right -> get_key_num() - c);
		        update(right);
		        return for_fix -> get_left();
		    }
		    if (left && left -> get_key_num()- t + 1 < c) {
		        for (int i = 0; i < for_fix -> get_key_num(); i++) {
		            left -> set_key(i + left -> get_key_num(), for_fix -> get_key()[i]);
		        }
		        left -> set_key_num(left -> get_key_num() + for_fix -> get_key_num());
		        if (for_fix -> get_right()) {
		            left -> set_right(for_fix -> get_right());
		            for_fix -> get_right() -> set_left(left);
		        }
		        else left -> set_right(nullptr);
		        if (for_fix -> get_parent() && for_fix -> get_parent() -> get_child()[0] == for_fix) {
		             for (int i = 0; i < for_fix -> get_parent() -> get_key_num(); i++) {
		                 for_fix -> get_parent() -> get_child()[i] = for_fix -> get_parent() -> get_child()[i + 1];
		             }
		             update(for_fix -> get_parent());
		             delete_key(*for_fix -> get_parent(), for_fix -> get_parent() -> get_key()[0], 0);
		         } else
		             delete_key(*for_fix -> get_parent(), for_fix -> get_key()[0], 1);
		         update(left);
		         delete(for_fix);
		        return left;
		}
		if (right && right -> get_key_num() - t + 1 < c) {
		    for (int i = 0; i < right -> get_key_num(); i++) {
		        for_fix -> set_key(i + for_fix -> get_key_num(), right -> get_key()[i]);
		        for_fix -> set_value(i + for_fix -> get_key_num(), right -> get_value()[i]);
		    }
		    for_fix -> set_key_num(right -> get_key_num() + for_fix -> get_key_num());
		    if (right -> get_right()) {
		        for_fix -> set_right(right -> get_right());
		        right -> get_right() -> set_left(for_fix);
		    }
		    else for_fix -> set_right(nullptr);
		    delete_key(*right -> get_parent(), right -> get_key()[0], 1);
		    delete(right);
		    return for_fix -> get_left();
		}
		return nullptr;
	    }
	    void delete_key(node<T1,T2>& Node, const T1& key, int p) {
		    bool f = false;
		    for (int i = 0; i < 2 * t; i++) {
		        if (Node.get_key()[i] == key) {
		            f = true;
		            break;
		        }
		    }
		    if (!f)
		        return;
		    int pos = 0;
		    while (pos < Node.get_key_num() && Node.get_key()[pos] < key) {
		        ++pos;
		    }
		    for (int i = pos; i < Node.get_key_num() - 1; i++) {
		        Node.set_key(i, Node.get_key()[i + 1]);
		        Node.set_value(i, Node.get_value()[i + 1]);
		    }
		    if (p)
		        for (int i = pos + 1; i < Node.get_key_num(); i++) {
		            Node.set_child(i, Node.get_child()[i + 1]);
		        }
		    Node.set_key_num(Node.get_key_num() - 1);
		    update(&Node);
		    if (Node.get_key_num() < t - 1) {
		        node<T1,T2>* left_sibl = Node.get_left();
		        node<T1,T2>* right_sibl = Node.get_right();
		        if (left_sibl && left_sibl -> get_key_num() > t - 1) {
		            left_sibl -> set_key_num(left_sibl -> get_key_num() - 1);
		            Node.set_key_num(Node.get_key_num() + 1);
		            Node.set_child(Node.get_key_num(), Node.get_child()[Node.get_key_num() - 1]);
		            for (int i = Node.get_key_num() - 1; i > 0; i--) {
		                Node.set_key(i, Node.get_key()[i - 1]);
		                Node.set_value(i, Node.get_value()[i - 1]);
		                Node.set_child(i, Node.get_child()[i - 1]);
		            }
		            Node.set_key(0, left_sibl -> get_key()[left_sibl -> get_key_num()]);
		            Node.set_value(0, left_sibl -> get_value()[left_sibl -> get_key_num()]);
		            Node.set_child(0, left_sibl -> get_child()[left_sibl -> get_key_num() + 1]);
		            update(&Node);
		        } else if (right_sibl && right_sibl -> get_key_num() > t - 1) {
		            Node.set_key_num(Node.get_key_num() + 1);
		            Node.set_key(Node.get_key_num() - 1, right_sibl -> get_key()[0]);
		            Node.set_value(Node.get_key_num() - 1, right_sibl -> get_value()[0]);
		            Node.set_child(Node.get_key_num(), right_sibl -> get_child()[0]);
		            right_sibl -> set_key_num(right_sibl -> get_key_num() - 1);
		            for (int i = 0; i < right_sibl -> get_key_num(); i++) {
		                right_sibl -> set_key(i, right_sibl -> get_key()[i + 1]);
		                right_sibl -> set_value(i, right_sibl -> get_value()[i + 1]);
		                right_sibl -> set_child(i, right_sibl -> get_child()[i + 1]);
		            }
		             right_sibl -> set_child(right_sibl -> get_key_num(), right_sibl -> get_child()[right_sibl -> get_key_num() + 1]);
		            update(&Node);
		        } else if (left_sibl) {
		            for (int i = 0; i < Node.get_key_num(); i++) {
		                left_sibl -> set_key(left_sibl -> get_key_num(), Node.get_key()[i]);
		                left_sibl -> set_value(left_sibl -> get_key_num(), Node.get_value()[i]);
		                left_sibl -> set_child(left_sibl -> get_key_num() + 1, Node.get_child()[i]);
		                left_sibl -> set_key_num(left_sibl -> get_key_num() + 1);
		            }
		            if (!Node.get_leaf()) {
		                 left_sibl -> set_child(left_sibl -> get_key_num() + 1, Node.get_child()[Node.get_key_num()]);
		                left_sibl -> set_key_num(left_sibl -> get_key_num() + 1);
		            }
		            if (Node.get_right()) {
		                left_sibl -> set_right(Node.get_right());
		                Node.get_right() -> set_left(left_sibl);
		            }
		            else {
		                left_sibl -> set_right(nullptr);
		            }

		            update(left_sibl);
		           if (Node.get_parent()) {
		               node<T1,T2>* par = Node.get_parent();
		                if (par -> get_child()[0] == &Node) {
		                   for (int i = 0; i < Node.get_parent() -> get_key_num(); i++) {
		                       par -> get_child()[i] = par -> get_child()[i] -> get_right();
		                   }
		                   update(par);
		                   delete_key(*par, par -> get_key()[0], 0);
		                }
		                
		                 delete_key(*par, min_key(&Node), 1);
		           }
		           delete(&Node);
		        } else if (right_sibl) {
		            for (int i = 0; i < right_sibl -> get_key_num(); i++) {
		                Node.set_key(Node.get_key_num(), right_sibl -> get_key()[i]);
		                Node.set_value(Node.get_key_num(), right_sibl -> get_value()[i]);
		                Node.set_child(Node.get_key_num() + 1, right_sibl -> get_child()[i]);
		                Node.set_key_num(Node.get_key_num() + 1);
		            }
		            if (right_sibl -> get_child()[right_sibl -> get_key_num()]) {
		                Node.set_child(Node.get_key_num() + 1, right_sibl -> get_child()[right_sibl -> get_key_num()]);
		                Node.set_key_num(Node.get_key_num() + 1);
		            }
		            if (right_sibl -> get_right()) {
		                Node.set_right(right_sibl -> get_right());
		                right_sibl -> get_right() -> set_left(&Node);
		            } else {
		                Node.set_right(nullptr);
		            }
		            update(&Node);
		            delete_key(*(right_sibl -> get_parent()), min_key(right_sibl), 1);
		            delete(right_sibl);
		        }
		        if (this -> root -> get_key_num() <= 1 && child_num(*(this -> root)) == 1) {
		            node<T1,T2>* temp = this -> root;
		            this -> root = this -> root -> get_child()[0];
		            this -> root -> set_parent(nullptr);
		            delete(temp);
		        }
		    }
	    }
    
	    public:
            Bptree(int n) {
                this -> t = n;
                this -> root = nullptr;
            }
            Bptree(int n, node<T1,T2>& Node) {
                this -> t = n;
                this -> root = Node;
            }
            ~Bptree() {
                if (this -> root) {
                    if (this -> root -> get_key_num() != 0) {
                        node<T1,T2>* first = this -> root;
                        node<T1,T2>* next = this -> root;
                        node<T1,T2>* curr = this -> root;
                        node<T1,T2>* right = this -> root;
                        while(first) {
                            next = first -> get_child()[0];
                            curr = first;
                            while(curr) {
                                right = curr -> get_right();
                                if (curr)
                                    delete(curr);
                                curr = right;
                            }
                            first = next;
                        }
                    } else {
                        delete(this -> root);
                    }
                }
            }

            node<T1,T2>* find_leaf(T1 key) {
                node<T1,T2>* cur = this -> root;
                while (!cur -> get_leaf())
                    for (int i = 0; i <= cur -> get_key_num(); i++)
                        if (i == cur -> get_key_num() || key < cur -> get_key()[i]) {
                            cur = cur -> get_child()[i];
                            break;
                        }
                return cur;
            }

            bool insert(const T1& key, const T2& value) {
                if (!this -> root)
                    this -> root = new node<T1,T2> (this -> t, true);
                node<T1,T2>* leaf = find_leaf(key);
                for (int i = 0; i < leaf -> get_key_num(); i++) {
                    if (leaf -> get_key()[i] == key) {
                        return false;
                    }
                }
                int pos=0;
                while (pos < leaf -> get_key_num() && leaf -> get_key()[pos] < key)
                    ++pos;
                for (int i = leaf -> get_key_num(); i > pos; i--) {
                    leaf -> set_key(i, leaf -> get_key()[i - 1]);
                    leaf -> set_value(i, leaf -> get_value()[i - 1]);
                }
                leaf -> set_key(pos, key);
                leaf -> set_value(pos, value);
                leaf -> set_key_num(leaf -> get_key_num() + 1);
                if (leaf -> get_key_num() == 2 * t)
                    split(leaf);
                return true;
            }

            bool delete_check(const T1& key) {
                node<T1,T2>* leaf = find_leaf(key);
                int pos = 0;
                bool f = false;
                for (int i = 0; i < leaf -> get_key_num(); i++) {
                    if (leaf -> get_key()[i] == key) {
                        f = true;
                        break;
                    }
                }
                if (f)
                    delete_key(*leaf, key, 1);
                else
                    return false;
                return true;
            }

            int child_num(node<T1,T2>& Node) {
                int res = 0;
                for (int i = 0; i <= Node.get_key_num(); i++) {
                    if (Node.get_child()[i])
                        ++res;
                }
                return res;
            }

            void fix() {
                if (!this -> root)
                    return;
                node<T1,T2>* cur = this -> root;
                while (cur -> get_child()[0]) {
                    cur = cur -> get_child()[0];
                }
                int count = 0;
                T1* bulk = new T1[2 * t];
                T2* ar = new T2[2 * t];
                while (true) {
                    count = 0;
                    for (int i = 0; i < cur -> get_key_num(); i++) {
                        if (!cur -> get_deleted()[i]) {
                            bulk[count] = cur -> get_key()[i];
                            ar[count] = cur -> get_value()[i];
                            count++;
                        }
                    }
                    for (int i = 0; i < count; i++) {
                        cur -> set_key(i, bulk[i]);
                        cur -> set_value(i, ar[i]);
                    }
                    for (int i = 0; i < 2 * t; i++) {
                        cur -> set_deleted(i, false);
                    }
                    cur -> set_key_num(count);
                    update(cur);
                    if (cur -> get_right())
                        cur = cur -> get_right();
                    else {
                        break;
                    }
                }
                while (cur) {
                    cur = fix_node(cur);
                }
                delete []bulk;
                delete []ar;
            }

            void lazy_insert(const T1& key, const T2& val) {
                auto leaf = find_leaf(key);
                for (int i = 0; i < leaf -> get_key_num(); i++) {
                    if (leaf -> get_key()[i] == key) {
                        if (leaf -> get_deleted()[i]) {
                            leaf -> set_deleted(i, false);
                            leaf -> set_value(i, val);
                        }
                       return;
                    }
                }
                if (check_for_deleted(leaf)) {
                    insert_in_deleted(leaf, key, val);
                    return;
                }
                int left_count = 0, right_count = 0, f = 0, g = 0;
                if (leaf -> get_key_num() < 2 * t - 1) {
                    insert(key, val);
                    return;
                }
                int pos = 0;
                while (pos < leaf -> get_key_num() && leaf -> get_key()[pos] < key) {
                    ++pos;
                }
                auto left = leaf, right = leaf;
                while (left) {
                    if (left -> get_key_num() < 2 * t - 1) {
                        f = 1;
                        break;
                    }
                    left_count++;
                    if (left -> get_left())
                        left = left -> get_left();
                    else
                        break;
                }
                while (right) {
                    if (right -> get_key_num() < 2 * t - 1) {
                        g = 1;
                        break;
                    }
                    right_count++;
                    if (right -> get_right())
                        right = right -> get_right();
                    else
                        break;
                }
                if (!f && !g) {
                    insert(key, val);
                    return;
                }
                if (f && !g) {
                    lazy_insert_left(leaf, left, pos, key, val);
                    return;
                }
                if (!f && g) {
                    lazy_insert_right(leaf, right, pos, key, val);
                    return;
                }
                if (left_count > right_count) {
                    lazy_insert_right(leaf, right, pos, key, val);
                } else{
                    lazy_insert_left(leaf, left, pos, key, val);
                }
            }

            int lazy_delete(const T1& key) {
                node<T1,T2>* leaf = find_leaf(key);
                int pos = find_pos(leaf, key);
                if (pos == -1)
                    return 0;
                leaf -> set_deleted(pos, true);
                return 1;
            }

            void pr() {
                p(this -> root, 0);
            }
            void p(node<T1,T2>* cur, int level) {
                int i = 0;
                for (int k = 0; k < level; k++) {
                    std::cout<<"*";
                }
                std::cout<<" ";
                for (int j = 0; j < cur -> get_key_num(); j++) {
                    if (cur -> get_deleted()[j])
                        std::cout<<"_";
                    std::cout<<cur -> get_key()[j]<<" ";
                }
                if (cur -> get_parent())
                    std::cout<<"parent is: "<<cur -> get_parent() -> get_key()[0]<<"  ";
                std::cout<<"children are: " <<this -> child_num(*cur) <<" end of line"<<std::endl;
                while (i <= cur -> get_key_num()) {
                    if (cur -> get_child()[i] && !cur -> get_leaf())
                        p(cur -> get_child()[i],level +1);
                    i++;
                }
                return;
            }

            set<T1> print_set() {
                set <T1> res;
                node<T1,T2>* cur = this -> root;
                for (int i = 0; i < cur -> get_key_num(); i++) {
                    res.insert(cur -> get_key()[i]);
                }
                if (cur -> get_leaf())
                    return res;
                do {
                    cur=cur -> get_child()[0];
                    while (cur -> get_left())
                        cur = cur -> get_left();
                    for (int i = 0; i < cur -> get_key_num(); i++) {
                        res.insert(cur -> get_key()[i]);
                    }
                    while (cur -> get_right()) {
                        cur = cur -> get_right();
                        for (int i = 0; i < cur -> get_key_num(); i++) {
                            res.insert(cur -> get_key()[i]);
                        }
                    }
                } while(!cur -> get_leaf());
                return res;
            }
            std::vector<T1> print() {
                std::vector<T1> res;
                node<T1,T2>* cur = this -> root;
                for (int i = 0; i < cur -> get_key_num(); i++) {
                    res.push_back(cur -> get_key()[i]);
                }
                if (cur -> get_leaf())
                    return res;
                do {
                    cur=cur -> get_child()[0];
                    while (cur -> get_left())
                        cur = cur -> get_left();
                    for (int i = 0; i < cur -> get_key_num(); i++) {
                        res.push_back(cur -> get_key()[i]);
                    }
                    while (cur -> get_right()) {
                        cur = cur -> get_right();
                        for (int i = 0; i < cur -> get_key_num(); i++) {
                            res.push_back(cur -> get_key()[i]);
                        }
                    }
                } while(!cur -> get_leaf());
                return res;
           }
	};
}

#endif
