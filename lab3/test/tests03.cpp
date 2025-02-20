#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include "../include/array_func.h"
#include "../include/Pentagon.h"
#include "../include/Hexagon.h"
#include "../include/Octagon.h"
#include "../include/double_equal.h"

TEST(FigTest01, EmptyVector)
{
std::vector<Figure*> figs;

{
testing::internal::CaptureStdout();
output(figs);
std::string out = testing::internal::GetCapturedStdout();
EXPECT_NE(std::string::npos, out.find("Фигур нет"));
}
{
testing::internal::CaptureStdout();
print_square(figs);
std::string out = testing::internal::GetCapturedStdout();
EXPECT_NE(std::string::npos, out.find("Фигур нет"));
}
{
testing::internal::CaptureStdout();
print_geomc(figs);
std::string out = testing::internal::GetCapturedStdout();
EXPECT_NE(std::string::npos, out.find("Фигур нет"));
}
}

TEST(FigTest02, SinglePentagonSquare)
{
std::vector<Figure*> figs;
Point arr[5] = {
        Point(10.000000,0.000000),
        Point(3.090170,9.510565),
        Point(-8.090170,5.877853),
        Point(-8.090170,-5.877853),
        Point(3.090170,-9.510565)
};
try {
figs.push_back(new Pentagon(arr));
} catch(...) {
FAIL();
}
double s = square_sum(figs);
EXPECT_GT(s, 0.0);
for(auto f : figs) delete f;
}


TEST(FigTest03, MultipleFigsCheck)
{
std::vector<Figure*> figs;
{
Point arr[5] = {
        Point( 10.000000, 0.000000),
        Point(  3.090170, 9.510565),
        Point( -8.090170, 5.877853),
        Point( -8.090170,-5.877853),
        Point(  3.090170,-9.510565)
};
figs.push_back(new Pentagon(arr));
}
{
Point arr[6] = {
        Point(8.000000,0.000000),
        Point(4.000000,6.928203),
        Point(-4.000000,6.928203),
        Point(-8.000000,0.000000),
        Point(-4.000000,-6.928203),
        Point(4.000000,-6.928203)
};
figs.push_back(new Hexagon(arr));
}
{
Point arr[8] = {
        Point(  8.000000, 0.000000),
        Point(  5.656854, 5.656854),
        Point(  0.000000, 8.000000),
        Point( -5.656854, 5.656854),
        Point( -8.000000, 0.000000),
        Point( -5.656854,-5.656854),
        Point(  0.000000,-8.000000),
        Point(  5.656854,-5.656854)
};
figs.push_back(new Octagon(arr));
}
double s = square_sum(figs);
EXPECT_GT(s, 0.0);
for(auto f: figs) delete f;
}

TEST(FigTest04, DeleteCheck)
{
std::vector<Figure*> figs;
{
Point arr[5] = {
        Point(10,0), Point(3.09,9.51),
        Point(-8.09,5.88), Point(-8.09,-5.88),
        Point(3.09,-9.51)
};
figs.push_back(new Pentagon(arr));
figs.push_back(new Pentagon(arr));
}
bool ok1 = del(figs, 1);
EXPECT_TRUE(ok1);
EXPECT_EQ(1u, figs.size());
bool ok2 = del(figs, 99);
EXPECT_FALSE(ok2);
EXPECT_EQ(1u, figs.size());
for(auto f: figs) delete f;
}

TEST(FigTest05, SamePentagonEquality)
{
Point arr[5] = {
        Point(10.000000,0.000000),
        Point(3.090170,9.510565),
        Point(-8.090170,5.877853),
        Point(-8.090170,-5.877853),
        Point(3.090170,-9.510565)
};
Figure* p1=nullptr;
Figure* p2=nullptr;
try {
p1 = new Pentagon(arr);
p2 = new Pentagon(arr);
} catch(...) {
FAIL();
}
bool eq = (*p1 == *p2);
EXPECT_TRUE(eq);
delete p1; delete p2;
}

TEST(FigTest06, DifferentTypeEq)
{
Point arrP[5] = {
        Point(10.0,0.0), Point(3.09,9.51),
        Point(-8.09,5.88), Point(-8.09,-5.88),
        Point(3.09,-9.51)
};
Point arrH[6] = {
        Point(8.0,0.0), Point(4.0,6.928203),
        Point(-4.0,6.928203), Point(-8.0,0.0),
        Point(-4.0,-6.928203), Point(4.0,-6.928203)
};
Figure* pent=nullptr;
Figure* hexa=nullptr;
try{
pent=new Pentagon(arrP);
hexa=new Hexagon(arrH);
}catch(...){
FAIL();
}
EXPECT_FALSE((*pent==*hexa));
delete pent; delete hexa;
}

TEST(FigTest07, HexCenterCheck)
{
Point arr[6] = {
        Point(8.000000,0.000000),
        Point(4.000000,6.928203),
        Point(-4.000000,6.928203),
        Point(-8.000000,0.000000),
        Point(-4.000000,-6.928203),
        Point(4.000000,-6.928203)
};
Figure* h=nullptr;
try {
h = new Hexagon(arr);
} catch(...) {
FAIL();
}
Point c = h->geomc();
EXPECT_TRUE(double_equal(c.get_x(), 0.0));
EXPECT_TRUE(double_equal(c.get_y(), 0.0));
delete h;
}

TEST(FigTest08, InputNonEmpty)
{
std::vector<Figure*> figs;
{
Point arr[5] = {
        Point(10.0,0.0), Point(3.09,9.51),
        Point(-8.09,5.88), Point(-8.09,-5.88),
        Point(3.09,-9.51)
};
figs.push_back(new Pentagon(arr));
}
testing::internal::CaptureStdout();
input(figs);
std::string out = testing::internal::GetCapturedStdout();
EXPECT_EQ(std::string::npos, out.find("Выберите фигуру"));
for(auto f: figs) delete f;
}

TEST(FigTest9, AllPointsCoincide)
{
Point arr[5] = {
        Point(12.345,12.345),
        Point(12.345,12.345),
        Point(12.345,12.345),
        Point(12.345,12.345),
        Point(12.345,12.345)
};
EXPECT_THROW({
Pentagon p(arr);
}, std::invalid_argument);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
