#include <gtest/gtest.h>
#include "../include/fixed_block_resource.h"
#include "../include/pmr_dlist.h"
#include <string>
#include <stdexcept>

struct MyData {
    int x;
    double y;
    std::string info;
    MyData(int xx = 0, double yy=0.0, const std::string& s="")
            : x(xx), y(yy), info(s) {}
    bool operator==(const MyData& other) const {
        return x==other.x && y==other.y && info==other.info;
    }
};

TEST(TestPmr_1, CreateEmptyListInt)
{
FixedBlockResource resource(512);
PmrDList<int> listInt(&resource);
auto it = listInt.begin();
EXPECT_TRUE(it == listInt.end());
}

TEST(TestPmr_2, PushOneElementInt)
{
FixedBlockResource resource(512);
PmrDList<int> listInt(&resource);
listInt.push_back(42);
auto it = listInt.begin();
ASSERT_FALSE(it == listInt.end());
EXPECT_EQ(*it, 42);
++it;
EXPECT_TRUE(it == listInt.end());
}

TEST(TestPmr_3, PushMultipleElementsInt)
{
FixedBlockResource resource(512);
PmrDList<int> listInt(&resource);
for(int i=1; i<=3; i++){
listInt.push_back(i*100);
}
int expected[3] = {100,200,300};
int idx=0;
for(auto it=listInt.begin(); it!=listInt.end(); ++it){
EXPECT_EQ(*it, expected[idx]) << "Mismatch at idx=" << idx;
idx++;
}
EXPECT_EQ(idx, 3);
}

TEST(TestPmr_4, ClearListInt)
{
FixedBlockResource resource(512);
PmrDList<int> listInt(&resource);
listInt.push_back(10);
listInt.push_back(20);
listInt.clear();
EXPECT_TRUE(listInt.begin() == listInt.end());
}

TEST(TestPmr_5, SmallResourceLeadsToBadAlloc)
{
FixedBlockResource resource(64);
PmrDList<int> listInt(&resource);
bool caught = false;
try {
for(int i=0; i<50; i++){
listInt.push_back(i);
}
} catch(const std::bad_alloc&) {
caught = true;
}
EXPECT_TRUE(caught) << "Должно было вылететь std::bad_alloc";
}

TEST(TestPmr_6, TwoContainersOneResource)
{
FixedBlockResource resource(1024);
PmrDList<int> listA(&resource), listB(&resource);
listA.push_back(1);
listA.push_back(2);
listB.push_back(100);
listB.push_back(200);

int expectedA[2] = {1,2};
int idx=0;
for(auto it=listA.begin(); it!=listA.end(); ++it){
EXPECT_EQ(*it, expectedA[idx++]);
}

int expectedB[2] = {100,200};
idx=0;
for(auto it=listB.begin(); it!=listB.end(); ++it){
EXPECT_EQ(*it, expectedB[idx++]);
}
}

TEST(TestPmr_7, PushMyData)
{
FixedBlockResource resource(2048);
PmrDList<MyData> list(&resource);
list.push_back(MyData(10, 3.14, "Pi"));
list.push_back(MyData(20, 2.718, "e"));

auto it = list.begin();
EXPECT_EQ(it->x, 10);
EXPECT_EQ(it->y, 3.14);
EXPECT_EQ(it->info, "Pi");
++it;
EXPECT_EQ(it->x, 20);
EXPECT_EQ(it->y, 2.718);
EXPECT_EQ(it->info, "e");
++it;
EXPECT_TRUE(it == list.end());
}

TEST(TestPmr_8, ReuseAfterClear)
{
FixedBlockResource resource(1024);
{
PmrDList<int> list(&resource);
for(int i=0; i<10; i++){
list.push_back(i);
}
list.clear();
}

PmrDList<int> list2(&resource);
for(int i=0; i<3; i++){
list2.push_back(100+i);
}
int expected[3] = {100,101,102};
int idx=0;
for(auto it=list2.begin(); it!=list2.end(); ++it){
EXPECT_EQ(*it, expected[idx++]);
}
}

TEST(TestPmr_9, IteratorForwardOnly)
{
FixedBlockResource resource(512);
PmrDList<int> list(&resource);
list.push_back(1);
list.push_back(2);

auto it = list.begin();
EXPECT_EQ(*it, 1);
++it;
EXPECT_EQ(*it, 2);
++it;
EXPECT_TRUE(it == list.end());

SUCCEED();
}

TEST(TestPmr_10, StringList)
{
FixedBlockResource resource(2048);
PmrDList<std::string> strList(&resource);
strList.push_back("Hello");
strList.push_back("World");

auto it = strList.begin();
EXPECT_EQ(*it, "Hello");
++it;
EXPECT_EQ(*it, "World");
++it;
EXPECT_TRUE(it == strList.end());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
