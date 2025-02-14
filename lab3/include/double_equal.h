#pragma once

#include <cmath>

static constexpr double EPS{1e-3};

inline bool double_equal(double a, double b)
{
    return std::fabs(a - b) < EPS;
}