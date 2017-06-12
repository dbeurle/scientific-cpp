
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

#include <range/v3/numeric.hpp>

int main()
{
    std::vector<double> v = {0.1, 1.0, 10.0, 100.0};

    auto result = std::accumulate(v.begin(), v.end(), 0.0);

    std::cout << result << std::endl;

    result = ranges::accumulate(v, 0.0);

    std::cout << result << std::endl;

    result = ranges::accumulate(v, 1.0, [](auto const& accumulator, auto const& i) {
        return accumulator * i;
    });

    std::cout << result << std::endl;

    return 0;
}
