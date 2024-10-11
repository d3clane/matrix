#include "matrix.hpp"

#include <iostream>

int main()
{
    MyStd::Matrix<int> m1(3, 3, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    MyStd::Matrix<int> m2(3, 3, {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});

    auto m3 = m1 * m2;

    std::cout << m3[0][0] << "\n";
}