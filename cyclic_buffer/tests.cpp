// danfoss_test.cpp: определяет точку входа для приложения.
//

#include "tests.h"
#include "cyclic_buffer.h"
#include <cassert>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>

using namespace std;

TEST(IntBufferTest, push_test) {
	cyclic_buffer<int> b = { 1,2,3,4,5 };

	b.push_back(6);
	EXPECT_EQ(b, cyclic_buffer<int>({ 2, 3, 4, 5, 6 }));

	b.push_front(0);
	EXPECT_EQ(b, cyclic_buffer<int>({ 0, 2, 3, 4, 5 }));

	b.push_front(-1);
	EXPECT_NE(b, cyclic_buffer<int>({ 0, 2, 3, 4, 5 }));
	EXPECT_EQ(b, cyclic_buffer<int>({ -1, 0, 2, 3, 4 }));
}

TEST(IntBufferTest, for_test) {
	cyclic_buffer<int> b = { 1,2,3,4,5 };
	string tmp;
	for (auto const& a : b)
	{
		tmp += to_string(a) + " ";
	}

	EXPECT_EQ(tmp, "1 2 3 4 5 ");
}

TEST(IntBufferTest, cycle_test) {
	cyclic_buffer<int> b = { 1,2,3,4,5 };

	int i = 0;
	string tmp = "";
	auto cyter = b.cybegin();
	while (i < 15)
	{
		tmp += to_string(++*(cyter)) + " ";
		i++;
		cyter++;
	}
	EXPECT_EQ(tmp, "2 3 4 5 6 3 4 5 6 7 4 5 6 7 8 ");
}

TEST(IntBufferTest, size_test) {
	cyclic_buffer<int> b = { 1,2,3,4,5 };

	EXPECT_EQ(b.max_size(), 5);
	EXPECT_TRUE(b.max_size() == b.size());
	b.pop_front();
	EXPECT_EQ(b.max_size(), 5);
	EXPECT_NE(b.max_size(), b.size());
	EXPECT_EQ(b.size(), 4);
	EXPECT_TRUE(b == cyclic_buffer<int>({ 2,3,4,5 }));
}
 

TEST(StringBufferTest, push_test) {
	cyclic_buffer<string> b = { "a","b","c","d","e","f","g" };
	b.push_back("h");
	EXPECT_EQ(b, cyclic_buffer<string>({ "b","c","d","e","f","g","h" }));
}

TEST(StringBufferTest, for_test) {
	cyclic_buffer<string> b = { "a","b","c","d","e","f","g" };
	b.push_front("i");
	EXPECT_EQ(b, cyclic_buffer<string>({ "i","a","b","c","d","e","f"}));
}

TEST(StringBufferTest, cycle_test) {
	cyclic_buffer<string> b = { "a","b","c","d","e","f","g" };

	int i = 0;
	string tmp = "";
	auto cyter = b.cybegin();
	while (i < 15)
	{
		*(cyter) += "->";
		tmp += *cyter + " ";
		i++;
		cyter++;
	}

	EXPECT_EQ(tmp, "a-> b-> c-> d-> e-> f-> g-> a->-> b->-> c->-> d->-> e->-> f->-> g->-> a->->-> ");
}

TEST(StringBufferTest, size_test) {

}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
