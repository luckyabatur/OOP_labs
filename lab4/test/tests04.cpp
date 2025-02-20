#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "../include/array_func.h"
#include "../include/double_equal.h"
#include "../include/Pentagon.h"
#include "../include/Hexagon.h"
#include "../include/Octagon.h"

TEST(ArrTest01, EmptyArrayCheck)
{
Array<std::shared_ptr<Figure<double>>> arr;

{
testing::internal::CaptureStdout();
output(arr);
std::string out = testing::internal::GetCapturedStdout();
EXPECT_NE(std::string::npos, out.find("Фигур нет"));
}
{
testing::internal::CaptureStdout();
print_square(arr);
std::string out = testing::internal::GetCapturedStdout();
EXPECT_NE(std::string::npos, out.find("Фигур нет"));
}
{
testing::internal::CaptureStdout();
print_geomc(arr);
std::string out = testing::internal::GetCapturedStdout();
EXPECT_NE(std::string::npos, out.find("Фигур нет"));
}
}

TEST(ArrTest02, SinglePentagonSquare)
{
Array<std::shared_ptr<Figure<double>>> arr;
std::ostringstream oss;
// Координаты правильного pentagon (радиус ~10)
oss << "10 0  3.090170 9.510565  -8.090170 5.877853  -8.090170 -5.877853  3.090170 -9.510565\n";
std::istringstream in(oss.str());

auto pent = std::make_shared<Pentagon<double>>();
EXPECT_NO_THROW({
in >> *pent;
});
arr.push_back(pent);

double s = square_sum(arr);
EXPECT_GT(s, 0.0);
}

TEST(ArrTest03, MultipleFiguresSquare)
{
Array<std::shared_ptr<Figure<double>>> arr;

{
std::ostringstream oss;
oss << "10 0  3.090170 9.510565  -8.090170 5.877853  -8.090170 -5.877853  3.090170 -9.510565\n";
std::istringstream in(oss.str());
auto p = std::make_shared<Pentagon<double>>();
in >> *p;
arr.push_back(p);
}
{
std::ostringstream oss;
oss << "8 0  4 6.928203  -4 6.928203  -8 0  -4 -6.928203  4 -6.928203\n";
std::istringstream in(oss.str());
auto h = std::make_shared<Hexagon<double>>();
in >> *h;
arr.push_back(h);
}
{
std::ostringstream oss;
oss << "8 0  5.656854 5.656854  0 8  -5.656854 5.656854  -8 0  -5.656854 -5.656854  0 -8  5.656854 -5.656854\n";
std::istringstream in(oss.str());
auto o = std::make_shared<Octagon<double>>();
in >> *o;
arr.push_back(o);
}

double s = square_sum(arr);
EXPECT_GT(s, 0.0);
}

TEST(ArrTest04, DeleteElement)
{
Array<std::shared_ptr<Figure<double>>> arr;
{
std::ostringstream oss;
oss << "10 0  3.090170 9.510565  -8.090170 5.877853  -8.090170 -5.877853  3.090170 -9.510565\n";
std::istringstream in(oss.str());
auto p1 = std::make_shared<Pentagon<double>>();
in >> *p1;
arr.push_back(p1);
}
{
std::ostringstream oss;
oss << "10 0  3.090170 9.510565  -8.090170 5.877853  -8.090170 -5.877853  3.090170 -9.510565\n";
std::istringstream in(oss.str());
auto p2 = std::make_shared<Pentagon<double>>();
in >> *p2;
arr.push_back(p2);
}

EXPECT_EQ(arr.get_size(), 2);
bool ok1 = arr.del(1);
EXPECT_TRUE(ok1);
EXPECT_EQ(arr.get_size(), 1);
bool ok2 = arr.del(99);
EXPECT_FALSE(ok2);
EXPECT_EQ(arr.get_size(), 1);
}

TEST(ArrTest05, InputNonEmptyNoAction)
{
Array<std::shared_ptr<Figure<double>>> arr;
{
std::ostringstream oss;
oss << "8 0  5.656854 5.656854  0 8  -5.656854 5.656854  -8 0  -5.656854 -5.656854  0 -8  5.656854 -5.656854\n";
std::istringstream in(oss.str());
auto oct = std::make_shared<Octagon<double>>();
in >> *oct;
arr.push_back(oct);
}
testing::internal::CaptureStdout();
input(arr);
std::string out = testing::internal::GetCapturedStdout();
EXPECT_EQ(std::string::npos, out.find("Выберите фигуру"));
}

TEST(ArrFigTest06, InputCorrectPentagon)
{
Array<std::shared_ptr<Figure<double>>> arr;
std::string data =
        "\n1\n"
        "10 0  3.090170 9.510565  -8.090170 5.877853  -8.090170 -5.877853  3.090170 -9.510565\n"
        "z\n";
std::istringstream iss(data);
auto oldCin = std::cin.rdbuf(iss.rdbuf());
EXPECT_NO_THROW({
input(arr);
});
std::cin.rdbuf(oldCin);
EXPECT_EQ(1, arr.get_size());
}

TEST(ArrTest07, GenericArrayInt)
{
Array<int> arr;
EXPECT_TRUE(arr.empty());
arr.push_back(42);
EXPECT_FALSE(arr.empty());
EXPECT_EQ(arr[0], 42);
EXPECT_EQ(arr.get_size(), 1);
arr.push_back(100);
EXPECT_EQ(arr.get_size(), 2);
bool ok = arr.del(0);
EXPECT_TRUE(ok);
EXPECT_EQ(arr.get_size(), 1);
EXPECT_EQ(arr[0],100);
}


TEST(ArrTest08, CopyAssign)
{
Array<std::shared_ptr<Figure<double>>> arrA;
{
std::ostringstream oss;
oss << "10 0  3.090170 9.510565  -8.090170 5.877853  -8.090170 -5.877853  3.090170 -9.510565\n";
std::istringstream in(oss.str());
auto p = std::make_shared<Pentagon<double>>();
in >> *p;
arrA.push_back(p);
}
{
std::ostringstream oss;
oss << "8 0  4 6.928203  -4 6.928203  -8 0  -4 -6.928203  4 -6.928203\n";
std::istringstream in(oss.str());
auto h = std::make_shared<Hexagon<double>>();
in >> *h;
arrA.push_back(h);
}
Array<std::shared_ptr<Figure<double>>> arrB;
arrB = arrA;
EXPECT_EQ(arrB.get_size(), 2);
bool ok = arrB.del(0);
EXPECT_TRUE(ok);
EXPECT_EQ(arrB.get_size(),1);
EXPECT_EQ(arrA.get_size(),2);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
