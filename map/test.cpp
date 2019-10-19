#include <valgrind/drd.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <gtest/gtest.h>
#include <ctime>

#include "hashtable.hpp"

void random_sort_vector(std::vector<int> vect){
	for (int i = 0; i < vect.size(); i++)
		std::swap(vect[rand() % vect.size()], vect[rand() % vect.size()]);
}
void randomize(std::vector<std::vector<int>> vect){
	for (int i = 0; i < vect.size(); i++)
		random_sort_vector(vect[i]);
}
TEST(AllTests, thread_valgrind_test_0)
{
	int num = 10;
	hashtable::thread_safe_hashtable* ht = new 		hashtable::thread_safe_hashtable(100);
	std::vector<std::vector<int>> vect(num, std::vector<int>(1000,0));
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < num; j++)
			vect[j][i] = rand() % 1000;
	}
	randomize(vect);
	std::thread threads[num];
	threads[0] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[0]));
	threads[1] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[1]));
	threads[2] = std::thread(&hashtable::thread_safe_hashtable::check_vector, ht, std::ref(vect[2]));
	threads[3] = std::thread(&hashtable::thread_safe_hashtable::remove_vector, ht, std::ref(vect[3]));
	threads[4] = std::thread(&hashtable::thread_safe_hashtable::remove_vector, ht, std::ref(vect[4]));
	threads[5] = std::thread(&hashtable::thread_safe_hashtable::check_vector, ht, std::ref(vect[5]));
	threads[6] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[6]));
	threads[7] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[7]));
	threads[8] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[8]));
	threads[9] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[9]));
	for (int i = 0 ; i < num; i++) {
		threads[i].join();
	}
	ASSERT_TRUE(ht -> check_hashtable());
	delete ht;
}

TEST(AllTests, thread_put_test_1)
{
	int num = 4;
	hashtable::thread_safe_hashtable* ht = new 		hashtable::thread_safe_hashtable(100);
	std::vector<std::vector<int>> vect(num, std::vector<int>(400,0));
	for (int i = 0; i < 400; i++) {
		vect[0][i] = i;
		vect[1][i] = 400 + i;
		vect[2][i] = 800 + i;
		vect[3][i] = 1200 + i;
	}
	randomize(vect);
	bool flag = true;
	std::thread threads[num];
	threads[0] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[0]));
	threads[1] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[1]));
	threads[2] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[2]));
	threads[3] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[3]));
	for (int i = 0 ; i < num; i++) {
		threads[i].join();
	}
	for (int i = 0; i < 1600; i++) {
		if (!(ht->check(i)))
			flag = false;
	}
	if (ht -> get_number_of_elements() != 1600)
		flag = false;
	ASSERT_TRUE(flag);
	ASSERT_TRUE(ht -> check_hashtable());
	delete ht;
}
TEST(AllTests, thread_remove_everything_test_2)
{
	int num = 5;
	hashtable::thread_safe_hashtable* ht = new 		hashtable::thread_safe_hashtable(100);
	std::vector<std::vector<int>> vect(num, std::vector<int>(1000,0));
	for (int i = 0; i < 1000; i++) {
		vect[0][i] = rand() % 1000;
		vect[1][i] = rand() % 1000;
		vect[2][i] = rand() % 1000;
		vect[3][i] = i;
		vect[4][i] = 999 - i;
	}
	randomize(vect);
	std::thread threads[num];
	threads[0] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[0]));
	threads[1] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[1]));
	threads[2] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[2]));
	for (int i = 0 ; i < 3; i++) {
		threads[i].join();
	}
	threads[3] = std::thread(&hashtable::thread_safe_hashtable::remove_vector, ht, std::ref(vect[3]));
	threads[4] = std::thread(&hashtable::thread_safe_hashtable::remove_vector, ht, std::ref(vect[4]));
	for (int i = 3 ; i < num; i++) {
		threads[i].join();
	}
	bool flag = true;
	flag = (ht -> get_number_of_elements() == 0);
	ASSERT_TRUE(flag);
	ASSERT_TRUE(ht -> check_hashtable());
	delete ht;
}
TEST(AllTests, thread_remove_from_middle_test_3)
{
	int num = 4;
	hashtable::thread_safe_hashtable* ht = new 		hashtable::thread_safe_hashtable(100);
	std::vector<std::vector<int>> vect(num, std::vector<int>(1000,0));
	for (int i = 0; i < 1000; i++) {
		vect[0][i] = i;
		vect[1][i] = 1000 + i;
		vect[2][i] = 800 + i % 501;
		vect[3][i] = 200 + i % 201;
	}
	randomize(vect);
	std::thread threads[num];
	threads[0] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[0]));
	threads[1] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[1]));
	for (int i = 0 ; i < 2; i++) {
		threads[i].join();
	}
	threads[2] = std::thread(&hashtable::thread_safe_hashtable::remove_vector, ht, std::ref(vect[2]));
	threads[3] = std::thread(&hashtable::thread_safe_hashtable::remove_vector, ht, std::ref(vect[3]));
	for (int i = 2 ; i < num; i++) {
		threads[i].join();
	}
	bool flag = true;
	for (int i = 0; i < 1000; i++) {
		if ((((i > 1300) && (i < 2000)) || ((i >= 0) && (i < 200)) || ((i > 400) && (i < 800))) && (!(ht -> check(i))))
			flag = false;
		if ((((i >= 200) && (i <= 400)) || ((i >= 800) && (i <= 1300))) && (ht -> check(i)))
			flag = false;
	}
	ASSERT_TRUE(flag);
	ASSERT_TRUE(ht -> check_hashtable());
	delete ht;
}

TEST(AllTests, thread_put_test_4)
{
	int num = 4;
	hashtable::thread_safe_hashtable* ht = new 		hashtable::thread_safe_hashtable(100);
	std::vector<std::vector<int>> vect(num, std::vector<int>(1000,0));
	for (int i = 0; i < 1000; i++) {
		vect[0][i] = i % 100;
		vect[1][i] = i % 100;
		vect[2][i] = i % 100;
		vect[3][i] = i % 100;
	}
	randomize(vect);
	bool flag = true;
	std::thread threads[num];
	threads[0] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[0]));
	threads[1] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[1]));
	for (int i = 0 ; i < 2; i++) {
		threads[i].join();
	}
	for (int i = 0; i < 100; i++) {
		if (!(ht -> check(i)))
			flag = false;
	}
	threads[2] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[2]));
	threads[3] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[3]));
	for (int i = 2 ; i < num; i++) {
		threads[i].join();
	}
	for (int i = 0; i < 100; i++) {
		if (!(ht->check(i)))
			flag = false;
	}
	if (ht -> get_number_of_elements() != 100)
		flag = false;
	ASSERT_TRUE(flag);
	ASSERT_TRUE(ht -> check_hashtable());
	delete ht;
}
TEST(AllTests, thread_remove_test_5)
{
	int num = 4;
	hashtable::thread_safe_hashtable* ht = new 		hashtable::thread_safe_hashtable(100);
	std::vector<std::vector<int>> vect(num, std::vector<int>(1000,0));
	for (int i = 0; i < 1000; i++) {
		vect[0][i] = i % 100;
		vect[1][i] = i % 100;
		vect[2][i] = 50 + i % 60;
		vect[3][i] =  70 + i % 20;
	}
	randomize(vect);
	int j = 0;
	bool flag = true;
	std::thread threads[num];
	threads[0] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[0]));
	threads[1] = std::thread(&hashtable::thread_safe_hashtable::put_vector, ht, std::ref(vect[1]));
	for (int i = 0 ; i < 2; i++) {
		threads[i].join();
	}
	for (int i = 0; i < 100; i++) {
		if (!(ht -> check(i)))
			flag = false;
	}
	if (ht -> get_number_of_elements() != 100)
		flag = false;
	threads[2] = std::thread(&hashtable::thread_safe_hashtable::remove_vector, ht, std::ref(vect[2]));
	threads[3] = std::thread(&hashtable::thread_safe_hashtable::remove_vector, ht, std::ref(vect[3]));
	for (int i = 2 ; i < num; i++) {
		threads[i].join();
	}
	for (int i = 0; i < 50; i++) {
		if (!(ht->check(i)))
			flag = false;
	}
	if (ht -> get_number_of_elements() != 50)
		flag = false;
	ASSERT_TRUE(flag);
	ASSERT_TRUE(ht -> check_hashtable());
	delete ht;
}
int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}









