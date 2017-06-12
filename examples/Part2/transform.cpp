
#include <algorithm>
#include <iostream>
#include <vector>

#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

int main()
{
    // Create a vector a and b with 10 elements in each and a is initialised to 1
    std::vector<int> a(10, 1), b(10);

    std::transform(a.begin(), a.end(), b.begin(), [](auto const& i) { return i * 2; });

    b.erase(std::unique(b.begin(), b.end()), b.end());

    std::cout << "Using the stl : \n";
    for (auto const& i : b) std::cout << i << std::endl;

    // Now we are going to use the range library

    using namespace ranges;

    b.resize(10);

    b = a | view::transform([](auto const& i) { return i * 2; }) | view::unique;

    std::cout << "Using the range v3 library : \n";
    for (auto const& i : b) std::cout << i << std::endl;
}
