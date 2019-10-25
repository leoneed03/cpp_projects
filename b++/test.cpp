#include <iostream>
#include <cstdlib>
#include "tree.h"
#include <cstdio>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>


using namespace std;
using namespace bplus_tree_namespace;

template  <class T1>
int check_vect(vector<T1> &v, vector<T1> &t) {
    if (v.size() != t.size())
        return 0;
    for (int i=0; i<v.size(); i++ ) {
        if (v[i] != t[i])
            return 0;
    }
    return 1;
}
template <class T1>
void print_vect(vector<T1> &v) {

    for (int i = 0; i < v.size(); i++) {
        cout<<v[i]<<", ";
    }
}
TEST(AllTests, in){


    Bptree<int,int>* tree = new Bptree<int,int>(3);
    tree->insert(12,0);
        tree->insert(14,0);
        tree->insert(15,0);
        tree->insert(16,0);
        tree->insert(17,0);
            tree->insert(27,0);
    tree->insert(31,0);
        tree->insert(37,0);
            tree->insert(32,0);
    tree->insert(33,0);
        tree->insert(34,0);
        tree->insert(35,0);
        tree->insert(36,0);
        tree->insert(100,0);
        tree->delete_check(32);
        tree->delete_check(33);
        tree->delete_check(15);
        
        tree->delete_check(16);
        
        tree->delete_check(17);
        
        tree->delete_check(33);
        tree->delete_check(25);
        tree->delete_check(36);
        
        tree->delete_check(34);
        tree->delete_check(35);
        tree->lazy_delete(12);
        tree->lazy_delete(14);
        tree->lazy_delete(27);
        tree->fix();           
    tree->pr();
    delete(tree);
    }

/*
TEST(AllTests, insert_test1000) {
    Bptree<int,int>* tree = new Bptree<int,int>(3);
    vector<int> exp(50010);
    for (int i = 0; i < 50000; i++){
        tree->insert(i,0);
        exp[i]=i;
    }
    
    set<int> my_set= tree->print_set();
	for (int i = 0; i < 50000; i++){
	    ASSERT_TRUE(my_set.find(exp[i])!=my_set.end());
	}
    delete tree;
}

TEST(AllTests, delete_test1000) {
    Bptree<int,int>* tree = new Bptree<int,int>(3);
    vector<int> exp(50010);
    for (int i = 0; i < 50000; i++){
        tree->insert(i,0);
        exp[i]=i;
    }
    for (int i = 0; i < 50000; i++){
        tree->delete_check(i);
    }
    vector<int> act = tree->print();
    ASSERT_TRUE(act.size()==0);
    cout<<"ACTUAL SIZE "<<act.size()<<endl<<endl<<endl;
    delete tree;
}
TEST(AllTests, insert_test500) {
    Bptree<int,int>* tree = new Bptree<int,int>(3);
    vector<int> exp(50010,0);
    for (int i = 0; i < 50000; i++){
	    tree->insert(i,0);
	    exp[i] = i;
	}
    for (int i = 20000; i < 25000; i++){
        exp[i] = -1;
        tree->delete_check(i);
    }
    set<int> my_set= tree->print_set();
	for (int i = 25000; i < 50000; i++){
	  //  ASSERT_TRUE(my_set.find(exp[i])!=my_set.end());
	}
    delete tree;
}*/
/*
TEST(AllTests, insert_test1) {
    Bptree<int,int>* tree = new Bptree<int,int>(3);
    tree->insert(27,0);
    tree->insert(20,0);
    tree->insert(31,0);
    tree->insert(42,0);
    tree->insert(21,0);
    tree->insert(34,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(72,0);
    tree->pr();
    vector<int> act = tree->print();
    vector<int> exp = { 31, 47, 20, 21, 27, 31, 34, 42, 47, 64, 72};
    ASSERT_TRUE(check_vect(act,exp));
    print_vect(act);
    delete tree;
}
TEST(AllTests, insert_test2) {
    Bptree<int,int>* tree = new Bptree<int,int>(3);
    tree->insert(27,0);
    tree->insert(20,0);
    tree->insert(31,0);
    tree->insert(42,0);
    tree->insert(1,0);
    tree->insert(100,0);
    tree->pr();
    vector<int> act = tree->print();
    vector<int> exp = { 31, 1 ,20, 27, 31, 42, 100};
    ASSERT_TRUE(check_vect(act,exp));
    print_vect(act);
    delete tree;
}

TEST(AllTests, insert_test3) {
    Bptree<int,int>* tree = new Bptree<int,int>(3);
    tree->insert(7,0);
    tree->insert(2,0);
    tree->insert(1,0);
    tree->insert(11,0);
    tree->insert(42,0);
    tree->insert(1,0);
    tree->pr();
    vector<int> act = tree->print();
    print_vect(act);
    vector<int> exp = { 1, 2, 7, 11, 42};
    ASSERT_TRUE(check_vect(act,exp));
    delete tree;
}

TEST(AllTests, delete_test1) {
//borrowing from the left
    Bptree<int,int>* tree = new Bptree<int,int>(3);
   tree->insert(27,0);
    tree->insert(52,0);
    tree->insert(20,0);
    tree->insert(42,0);
    tree->insert(21,0);
    tree->insert(34,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(72,0);
    tree->insert(91,0);
    tree->insert(97,0);
    tree->insert(14,0);
    tree->insert(7,0);
    tree->insert(34,0);
    tree->insert(27,0);
    tree->insert(20,0);
    tree->insert(21,0);
    tree->insert(42,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(93,0);
    tree->insert(22,0);
    tree->insert(23,0);
    tree->insert(15,0);
    tree->insert(26,0);
    tree->insert(44,0);
    tree->insert(63,0);
    tree->insert(23,0);
    tree->insert(5,0);
    tree->insert(6,0);
    tree->insert(4,0);
    tree->insert(93,0);
    tree->insert(13,0);
    tree->insert(115,0);
    tree->insert(66,0);
    tree->insert(48,0);
    tree->insert(98,0);
    tree->insert(123,0);
    tree->insert(115,0);
    tree->insert(76,0);
    tree->insert(74,0);
    tree->insert(3,0);
    tree->pr();
    tree->delete_check(44);
    tree->delete_check(34);
    tree->delete_check(52);
    tree->delete_check(64);
    tree->pr();
    vector<int> act = tree->print();
    print_vect(act);
    vector<int> exp = {48, 6, 14, 21, 42, 66, 91, 98, 3, 4, 5, 6, 7, 13, 14, 15, 20, 21, 22, 23, 26, 27, 42, 47, 48, 63, 66, 72, 74, 76, 91, 93, 97, 98, 115, 123};
    ASSERT_TRUE(check_vect(act,exp));
    delete tree;
}
TEST(AllTests, delete_test2){
//testing borrowing from right
    Bptree<int,int>* tree = new Bptree<int,int>(3);
   tree->insert(27,0);
    tree->insert(52,0);
    tree->insert(20,0);
    tree->insert(42,0);
    tree->insert(21,0);
    tree->insert(34,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(72,0);
    tree->insert(91,0);
    tree->insert(97,0);
    tree->insert(14,0);
    tree->insert(7,0);
    tree->insert(34,0);
    tree->insert(27,0);
    tree->insert(20,0);
    tree->insert(21,0);
    tree->insert(42,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(93,0);
    tree->insert(22,0);
    tree->insert(23,0);
    tree->insert(15,0);
    tree->insert(26,0);
    tree->insert(44,0);
    tree->insert(63,0);
    tree->insert(23,0);
    tree->insert(5,0);
    tree->insert(6,0);
    tree->insert(4,0);
    tree->insert(93,0);
    tree->insert(13,0);
    tree->insert(115,0);
    tree->insert(66,0);
    tree->insert(48,0);
    tree->insert(98,0);
    tree->insert(123,0);
    tree->insert(115,0);
    tree->insert(76,0);
    tree->insert(74,0);
    tree->insert(3,0);
    tree->pr();
    tree->delete_check(44);
    tree->delete_check(34);
    tree->delete_check(52);
    tree->delete_check(64);
    tree->delete_check(48);
    tree->pr();
    vector<int> act = tree->print();
    print_vect(act);
    vector<int> exp = {63, 6, 14, 21, 42, 72, 91, 98, 3, 4, 5, 6, 7, 13, 14, 15, 20, 21, 22, 23, 26, 27, 42, 47, 63, 66, 72, 74, 76, 91, 93, 97, 98, 115, 123};
    ASSERT_TRUE(check_vect(act,exp));
    delete tree;
}
TEST(AllTests, delete_test3){
//merging with left
    Bptree<int,int>* tree = new Bptree<int,int>(3);
   tree->insert(27,0);
    tree->insert(52,0);
    tree->insert(20,0);
    tree->insert(42,0);
    tree->insert(21,0);
    tree->insert(34,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(72,0);
    tree->insert(91,0);
    tree->insert(97,0);
    tree->insert(14,0);
    tree->insert(7,0);
    tree->insert(34,0);
    tree->insert(27,0);
    tree->insert(20,0);
    tree->insert(21,0);
    tree->insert(42,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(93,0);
    tree->insert(22,0);
    tree->insert(23,0);
    tree->insert(15,0);
    tree->insert(26,0);
    tree->insert(44,0);
    tree->insert(63,0);
    tree->insert(23,0);
    tree->insert(5,0);
    tree->insert(6,0);
    tree->insert(4,0);
    tree->insert(93,0);
    tree->insert(13,0);
    tree->insert(115,0);
    tree->insert(66,0);
    tree->insert(48,0);
    tree->insert(98,0);
    tree->insert(123,0);
    tree->insert(115,0);
    tree->insert(76,0);
    tree->insert(74,0);
    tree->insert(3,0);
    tree->pr();
    tree->delete_check(66);
    tree->delete_check(72);
    tree->delete_check(44);
    tree->delete_check(34);
    tree->delete_check(52);
    tree->delete_check(64);
    tree->delete_check(48);
    tree->pr();
    vector<int> act = tree->print();
    print_vect(act);
    vector<int> exp = {63, 6, 14, 21, 42, 72, 91, 98, 3, 4, 5, 6, 7, 13, 14, 15, 20, 21, 22, 23, 26, 27, 42, 47, 63, 66, 72, 74, 76, 91, 93, 97, 98, 115, 123};
   // ASSERT_TRUE(check_vect(act,exp));
    delete tree;
}
TEST(AllTests, delete_test4){
//merging with right
    Bptree<int,int>* tree = new Bptree<int,int>(3);
   tree->insert(27,0);
    tree->insert(52,0);
    tree->insert(20,0);
    tree->insert(42,0);
    tree->insert(21,0);
    tree->insert(34,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(72,0);
    tree->insert(91,0);
    tree->insert(97,0);
    tree->insert(14,0);
    tree->insert(7,0);
    tree->insert(34,0);
    tree->insert(27,0);
    tree->insert(20,0);
    tree->insert(21,0);
    tree->insert(42,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(93,0);
    tree->insert(22,0);
    tree->insert(23,0);
    tree->insert(15,0);
    tree->insert(26,0);
    tree->insert(44,0);
    tree->insert(63,0);
    tree->insert(23,0);
    tree->insert(5,0);
    tree->insert(6,0);
    tree->insert(4,0);
    tree->insert(93,0);
    tree->insert(13,0);
    tree->insert(115,0);
    tree->insert(66,0);
    tree->insert(48,0);
    tree->insert(98,0);
    tree->insert(123,0);
    tree->insert(115,0);
    tree->insert(76,0);
    tree->insert(74,0);
    tree->insert(3,0);
    tree->pr();
    tree->delete_check(44);
    tree->delete_check(34);
    tree->delete_check(52);
    tree->delete_check(64);
    tree->delete_check(48);
    tree->delete_check(3);
    tree->delete_check(4);
    tree->delete_check(6);
    tree->delete_check(-109);
    tree->pr();
    vector<int> act = tree->print();
    print_vect(act);
    vector<int> exp = {63, 14, 21, 42, 72, 91, 98, 5, 7, 13, 14, 15, 20, 21, 22, 23, 26, 27, 42, 47, 63, 66, 72, 74, 76, 91, 93, 97, 98, 115, 123};
    ASSERT_TRUE(check_vect(act,exp));
    delete tree;
}

TEST(AllTests, delete_test5){
// another merging with left
    Bptree<int,int>* tree = new Bptree<int,int>(3);
   tree->insert(27,0);
    tree->insert(52,0);
    tree->insert(20,0);
    tree->insert(42,0);
    tree->insert(21,0);
    tree->insert(34,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(72,0);
    tree->insert(91,0);
    tree->insert(97,0);
    tree->insert(14,0);
    tree->insert(7,0);
    tree->insert(34,0);
    tree->insert(27,0);
    tree->insert(20,0);
    tree->insert(21,0);
    tree->insert(42,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(93,0);
    tree->insert(22,0);
    tree->insert(23,0);
    tree->insert(15,0);
    tree->insert(26,0);
    tree->insert(44,0);
    tree->insert(63,0);
    tree->insert(23,0);
    tree->insert(5,0);
    tree->insert(6,0);
    tree->insert(4,0);
    tree->insert(93,0);
    tree->insert(13,0);
    tree->insert(115,0);
    tree->insert(66,0);
    tree->insert(48,0);
    tree->insert(98,0);
    tree->insert(123,0);
    tree->insert(115,0);
    tree->insert(76,0);
    tree->insert(74,0);
    tree->insert(3,0);
    tree->pr();
    tree->delete_check(123);
    tree->delete_check(98);
    tree->delete_check(97);
    tree->pr();
    vector<int> act = tree->print();
    print_vect(act);
    vector<int> exp = {52, 6, 14, 21, 34, 66, 91, 3, 4, 5, 6, 7, 13, 14, 15, 20, 21, 22, 23, 26, 27, 34, 42, 44, 47, 48, 52, 63, 64, 66, 72, 74, 76, 91, 93, 115};
    ASSERT_TRUE(check_vect(act,exp));
    delete tree;
}

TEST (AllTest, lazy_insert1){
    Bptree<int,int>* tree = new Bptree<int,int>(3);
    tree->insert(27,0);
    tree->insert(52,0);
    tree->insert(20,0);
    tree->insert(42,0);
    tree->insert(21,0);
    tree->insert(34,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(72,0);
    tree->insert(91,0);
    tree->insert(97,0);
    tree->insert(14,0);
    tree->insert(7,0);
    tree->insert(34,0);
    tree->insert(27,0);
    tree->insert(20,0);
    tree->insert(21,0);
    tree->insert(42,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(93,0);
    tree->insert(22,0);
    tree->insert(23,0);
    tree->insert(15,0);
    tree->insert(26,0);
    tree->insert(44,0);
    tree->insert(63,0);
    tree->insert(23,0);
    tree->insert(5,0);
    tree->insert(6,0);
    tree->insert(4,0);
    tree->insert(93,0);

    tree->insert(13,0);
    tree->insert(115,0);
    tree->insert(66,0);
    tree->insert(48,0);
    tree->insert(98,0);

    tree->insert(123,0);
    tree->insert(115,0);
    tree->insert(76,0);
    tree->insert(74,0);
    tree->insert(3,0);
    tree->pr();
    tree->delete_check(14);
    tree->delete_check(15);
    tree->delete_check(3);
    tree->delete_check(4);
    tree->delete_check(5);
    tree->delete_check(52);
    tree->delete_check(63);
    tree->delete_check(48);
    tree->delete_check(47);
    tree->delete_check(44);
    tree->delete_check(66);
    tree->delete_check(64);

    tree->delete_check(27);
    tree->delete_check(26);
    tree->delete_check(34);
    tree->delete_check(72);
    tree->delete_check(23);
    tree->pr();
    tree->lazy_insert(23,0);
    tree->lazy_insert(23,0);
    tree->lazy_insert(26,0);
    tree->lazy_insert(35,0);
    tree->lazy_insert(40,0);
    tree->lazy_insert(36,0);
    tree->lazy_insert(41,0);
    tree->lazy_insert(24,0);
    tree->lazy_insert(37,0);
    tree->lazy_insert(38,0);
    tree->lazy_insert(39,0);
 
    tree->pr();
    
    vector<int> act = tree->print();
    print_vect(act);
    vector<int> exp = {40, 21, 35, 91, 98, 6, 7, 13, 20, 21, 22, 23, 24, 26, 35, 36, 37, 38, 39, 40, 41, 42, 74, 76, 91, 93, 97, 98, 115, 123};
    ASSERT_TRUE(check_vect(act,exp));
    delete tree;   
    
}

TEST(AllTests, lazy_insert_test2) {
    Bptree<int,int>* tree = new Bptree<int,int>(2);
   tree->insert(27,0);
    tree->insert(52,0);
    tree->insert(20,0);
    tree->insert(42,0);
    tree->insert(21,0);
    tree->insert(34,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(72,0);
    tree->insert(91,0);
    tree->insert(97,0);
    tree->insert(14,0);
    tree->insert(7,0);
   
    tree->pr();
    tree->delete_check(44);
    tree->delete_check(34);
    tree->delete_check(52);
    tree->delete_check(64);
    
    cout<<"HELLO"<<endl;
    tree->pr();
    tree->lazy_insert(-23,0);
    tree->lazy_insert(23,0);
    tree->lazy_insert(26,0);
    tree->lazy_insert(35,0);
    tree->lazy_insert(40,0);
    tree->lazy_insert(36,0);
    tree->lazy_insert(41,0);
    tree->lazy_insert(24,0);
    tree->lazy_insert(37,0);
    tree->lazy_insert(38,0);
    tree->lazy_insert(39,0);
    tree->pr();
    vector<int> act = tree->print();
    print_vect(act);
    vector<int> exp = {35, 41, 20, 24, 38, 72, -23, 7, 14, 20, 21, 23, 24, 26, 27, 35, 36, 37, 38, 39, 40, 41, 42, 47, 72, 91, 97};
    ASSERT_TRUE(check_vect(act,exp));
    delete tree;
}

TEST(AllTests, lazy_delete_test1){
    Bptree<int,int>* tree = new Bptree<int,int>(3);
   tree->insert(27,0);
    tree->insert(52,0);
    tree->insert(20,0);
    tree->insert(42,0);
    tree->insert(21,0);
    tree->insert(34,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(72,0);
    tree->insert(91,0);
    tree->insert(97,0);
    tree->insert(14,0);
    tree->insert(7,0);
    tree->insert(34,0);
    tree->insert(27,0);
    tree->insert(20,0);
    tree->insert(21,0);
    tree->insert(42,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(93,0);
    tree->insert(22,0);
    tree->insert(23,0);
    tree->insert(15,0);
    tree->insert(26,0);
    tree->insert(44,0);
    tree->insert(63,0);
    tree->insert(23,0);
    tree->insert(5,0);
    tree->insert(6,0);
    tree->insert(4,0);
    tree->insert(93,0);
    tree->insert(13,0);
    tree->insert(115,0);
    tree->insert(66,0);
    tree->insert(48,0);
    tree->insert(98,0);
    tree->insert(123,0);
    tree->insert(115,0);
    tree->insert(76,0);
    tree->insert(74,0);
    tree->insert(3,0);
      tree->lazy_delete(3);
    tree->lazy_delete(4);
    tree->lazy_delete(5);
     tree->lazy_delete(6);
     tree->lazy_delete(7);
     tree->lazy_delete(14);
     tree->lazy_delete(15);
     tree->lazy_delete(23);
     tree->lazy_delete(26);
     tree->lazy_delete(27);
     tree->lazy_delete(34);
     tree->lazy_delete(44);
     tree->lazy_delete(47);
     tree->lazy_delete(48);
     tree->lazy_delete(52);
     tree->lazy_delete(63);
     tree->lazy_delete(64);
     tree->lazy_delete(66);
     tree->insert(23,0);
     tree->lazy_delete(72);
    tree->fix();

    tree->lazy_delete(74);
    
    tree->pr();
    tree->fix();
    tree->pr();
    tree->pr();
    vector<int> act = tree->print();
    print_vect(act);
    vector<int> exp = {22, 76, 93, 98, 13, 20, 21, 22, 42, 76, 91, 93, 97, 98, 115, 123};
    ASSERT_TRUE(check_vect(act,exp));
    delete tree;
}


TEST(AllTests, lazy_test_1){
    Bptree<int,int>* tree = new Bptree<int,int>(3);
   tree->insert(27,0);
    tree->insert(52,0);
    tree->insert(20,0);
    tree->insert(42,0);
    tree->insert(21,0);
    tree->insert(34,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(72,0);
    tree->insert(91,0);
    tree->insert(97,0);
    tree->insert(14,0);
    tree->insert(7,0);
    tree->insert(34,0);
    tree->insert(27,0);
    tree->insert(20,0);
    tree->insert(21,0);
    tree->insert(42,0);
    tree->insert(47,0);
    tree->insert(64,0);
    tree->insert(93,0);
    tree->insert(22,0);
    tree->insert(23,0);
    tree->insert(15,0);
    tree->insert(26,0);
    tree->insert(44,0);
    tree->insert(63,0);
    tree->insert(23,0);
    tree->insert(5,0);
    tree->insert(6,0);
    tree->insert(4,0);
    tree->insert(93,0);
    tree->insert(13,0);
    tree->insert(115,0);
    tree->insert(66,0);
    tree->insert(48,0);
    tree->insert(98,0);
    tree->insert(123,0);
    tree->insert(115,0);
    tree->insert(76,0);
    tree->insert(74,0);
    tree->insert(3,0);
    tree->insert(80,0);
    tree->pr();
    tree->lazy_delete(48);
    tree->lazy_delete(47);
    tree->lazy_insert(28,0);
    tree->lazy_insert(24,0);
    tree->lazy_insert(35,0);
    tree->lazy_insert(8, 0);
    tree->lazy_delete(66);
    tree->lazy_insert(73,0);
    tree->pr();
    vector<int> act = tree->print();
    print_vect(act);
    vector<int> exp = {52, 6, 14, 23, 34, 72, 91, 98, 3, 4, 5, 6, 7, 8, 13, 14, 15, 20, 21, 22, 23, 24, 26, 27, 28, 34, 35, 42, 44, 48, 52, 63, 64, 72, 74, 73, 76, 80, 91, 93, 97, 98, 115, 123};
    ASSERT_TRUE(check_vect(act,exp));
    delete tree;
}
*/
int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}









