
#include <vector>
#include <iostream>

#include <range/v3/action.hpp>
#include <range/v3/view.hpp>

int main()
{
    using namespace ranges;

    std::vector<std::vector<int>> const nodal_connectivity{{0, 3, 1, 2},
                                                           {3, 4, 1, 2},
                                                           {1, 0, 7}};

    // Remove duplicates in an array of arrays
    std::vector<int> essential_nodes = std::ref(nodal_connectivity)
                                     | action::join
                                     | action::sort
                                     | action::unique;

    for (auto i : essential_nodes) std::cout << i << std::endl;
}

