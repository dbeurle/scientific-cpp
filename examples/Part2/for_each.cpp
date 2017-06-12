
#include <algorithm>
#include <iostream>
#include <vector>

#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

int main()
{
    std::vector<int> elements(10, 0);
    std::iota(elements.begin(), elements.end(), 0);

    std::for_each(elements.begin(), elements.end(), [](auto const& e) {
        std::cout << "STL " << e << std::endl;
    });

    ranges::for_each(ranges::view::ints(0, 10),
                     [&](auto const& e) { std::cout << "Ranges " << e << std::endl; });
}
