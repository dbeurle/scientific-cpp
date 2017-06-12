
// This is an example how to use lambdas and compute generic integration methods
// and can be used as an example to see compile time optimisations (check assembly)

// Compile using: g++ -c -std=c++14 NumericalIntegration.cpp

// The generic integration function
template <typename Method, typename F>
double integrate(F f, double a, double b, int steps, Method m)
{
    double s = 0.0;

    auto const h = (b - a) / static_cast<double>(steps);

    for (int i = 0; i < steps; ++i) s += m(f, a + h * i, h);

    return h * s;
}

// Integration methods
class Rectangular
{
public:
    enum position_type { left, middle, right };

    Rectangular(position_type pos) : position(pos) {}

    template <typename F>
    double operator()(F f, double x, double h) const
    {
        switch (position)
        {
            case left:
                return f(x);
            case middle:
                return f(x + h / 2.0);
            case right:
                return f(x + h);
        }
    }

private:
    position_type const position;
};

class Trapeziodal
{
public:
    template <typename F>
    double operator()(F f, double x, double h) const
    {
        return (f(x) + f(x + h)) / 2.0;
    }
};

class Simpson
{
public:
    template <typename F>
    constexpr double operator()(F f, double x, double h) const
    {
        return (f(x) + 4.0 * f(x + h / 2.0) + f(x + h)) / 6.0;
    }
};

/** Lambda function to integrate */
auto f = [](double const& x) { return x * x; };

// Integration routines
auto rectangle_left() { return integrate(f, 0.0, 1.0, 20, Rectangular(Rectangular::left)); }

auto rectangle_right() { return integrate(f, 0.0, 1.0, 20, Rectangular(Rectangular::right)); }

auto rectangle_mid() { return integrate(f, 0.0, 1.0, 20, Rectangular(Rectangular::middle)); }

auto trap() { return integrate(f, 0.0, 1.0, 14, Trapeziodal()); }
