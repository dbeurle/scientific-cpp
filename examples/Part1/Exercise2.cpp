
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

// Compile using clang++ -std=c++14 Exercise1.cpp -o exercise1

int main()
{
    // Use lambdas to compute y = a*x + y
    std::vector<double> x = {0.2, 30.0, 3.03, 5.40, 20.3};
    std::vector<double> y = {3.3, 30.2, 85.0, 4.51, 6.29};

    auto const a = 2.0;

    // Compute y += a*x using std::transform
    std::transform(x.begin(), x.end(), y.begin(), y.begin(), [&](auto const xs, auto const ys) {
        return ys + a * xs;
    });

    std::cout << "Answer : \n";
    for (auto y_i : y) std::cout << y_i << std::endl;
}
