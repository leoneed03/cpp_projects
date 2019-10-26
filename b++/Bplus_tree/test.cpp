#include "tree.h"

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
using namespace bplus_tree_namespace;

template  <class T1>
int check_vect(vector<T1> &v, vector<T1> &t) {
    if (v.size() != t.size())
        return 0;
    for (int i = 0; i < v.size(); i++ ) {
        if (v[i] != t[i])
            return 0;
    }
    return 1;
}
template <class T1>
void print_vect(vector<T1> &v) {

    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ", ";
    }
}

int main(){
    Bptree<int,int>* tree = new Bptree<int,int>(3);
    tree -> insert(27,0);
    tree -> insert(52,0);
    tree -> insert(20,0);
    tree -> insert(42,0);
    tree -> insert(21,0);
    tree -> insert(34,0);
    tree -> insert(47,0);
    tree -> insert(64,0);
    tree -> insert(72,0);
    tree -> insert(91,0);
    tree -> insert(97,0);
    tree -> insert(14,0);
    tree -> insert(7,0);
    tree -> insert(34,0);
    tree -> insert(27,0);
    tree -> insert(20,0);
    tree -> insert(21,0);
    tree -> insert(42,0);
    tree -> insert(47,0);
    tree -> insert(64,0);
    tree -> insert(93,0);
    tree -> insert(22,0);
    tree -> insert(23,0);
    tree -> insert(15,0);
    tree -> insert(26,0);
    tree -> insert(44,0);
    tree -> insert(63,0);
    tree -> insert(23,0);
    tree -> insert(5,0);
    tree -> insert(6,0);
    tree -> insert(4,0);
    tree -> insert(93,0);
    tree -> insert(13,0);
    tree -> insert(115,0);
    tree -> insert(66,0);
    tree -> insert(48,0);
    tree -> insert(98,0);
    tree -> insert(123,0);
    tree -> insert(115,0);
    tree -> insert(76,0);
    tree -> insert(74,0);
    tree -> insert(3,0);
    tree -> pr();
    tree -> delete_check(44);
    tree -> delete_check(34);
    tree -> delete_check(52);
    tree -> delete_check(64);
    tree -> delete_check(48);
    tree -> pr();
    vector<int> act = tree -> print();
    print_vect(act);
    vector<int> exp = {63, 6, 14, 21, 42, 72, 91, 98, 3, 4, 5, 6, 7, 13, 14, 15, 20, 21, 22, 23, 26, 27, 42, 47, 63, 66, 72, 74, 76, 91, 93, 97, 98, 115, 123};
    cout << check_vect(act,exp);
    delete tree;
    return 0;
}









