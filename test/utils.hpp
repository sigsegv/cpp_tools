#pragma once

#include <cmath>

bool equals_approx(float a, float b)
{
    return std::abs(a - b) < 0.001;
}
