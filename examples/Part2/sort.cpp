
#include <algorithm>
#include <iostream>

// To compile: clang++ -std=c++14 sort.cpp
// or with g++: g++ -std=c++14 sort.cpp

int main()
{
    std::cout << "Basic sorting example\n\n";

    std::vector<double> v{0.3, 0.333, 0.48, 0.1, 0.0003};

    std::cout << "Vector before sorting :\n";

    for (auto v_i : v) std::cout << v_i << " ";

    std::sort(v.begin(), v.end());

    std::cout << "\n\nVector after sorting :\n";

    for (auto v_i : v) std::cout << v_i << " ";

    std::cout << "\n\n";
}
