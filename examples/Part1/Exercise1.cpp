
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

// Compile with g++ -Wall -std=c++14 Exercise1.cpp -o exercise1

int main()
{
    std::vector<int> v{1, 3, 4, 1, 5, 7, 2, 1, 3, 6, 8, 8, 7, 7};

    // TODO: Multiply each entry by two, remove the duplicates and find the sum
    // The following algorithms could help:
    //    1) std::sort
    //    2) std::reduce or std::accumulate
    //    3) std::unique
    //    4) std::vector<>.erase()
    //    5) std::transform

    // Sort the vector
    std::sort(v.begin(), v.end());

    // Move the duplicate entries to the back of the vector
    auto it_last_unique = std::unique(, );

    // Delete the non-unique entries from the vector between two iterators
    v.erase(, );

    // Multiple each value by two
    std::transform(, , , []() {

    });

    // Find the sum
    auto sum = std::accumulate();

    std::cout << "Answer = " << sum << "\n";
}
