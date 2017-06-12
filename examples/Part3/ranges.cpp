
// #include <iostream>
#define NDEBUG

#include <vector>

#include <range/v3/action.hpp>
#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>

std::vector<int> DofAllocator(std::vector<int> const& nodal_connectivity, int const nodal_dofs)
{
    using namespace ranges;
    return view::for_each(nodal_connectivity, [&](int const local_node) {
        return view::ints(0, nodal_dofs) | view::transform([=](int const nodal_dof) {
                   return local_node * nodal_dofs + nodal_dof;
               });
    });
}

auto ranges_search(int const segment_to_scission, std::vector<int> const& chains)
{
    using namespace ranges;
    // clang-format off
    return distance(chains | view::partial_sum()
                           | view::take_while([=](auto const& i) {
                                return i < segment_to_scission;
                             }));
    // clang-format on
}

auto stl_search(int const segment_to_scission, std::vector<int> const& chains)
{
    auto accumulated_length = 0;
    auto chain = std::find_if(chains.begin(), chains.end(), [&](auto const& val) {
        accumulated_length += val;
        return segment_to_scission < accumulated_length;
    });
    return std::distance(chains.begin(), chain);
}

auto basic_search(int const segment_to_scission, std::vector<int> const& chains)
{
    auto accumulated_length = 0;
    int i = 0;
    for (; i < chains.size(); i++)
    {
        accumulated_length += chains[i];
        if (segment_to_scission < accumulated_length)
        {
            break;
        }
    }
    return i;
}

int main()
{
    std::vector<int> const chains = {10, 3, 7, 11};

    auto constexpr segment_to_scission = 17;

    std::cout << "stl distance    = " << stl_search(segment_to_scission, chains) << "\n";
    std::cout << "basic distance  = " << basic_search(segment_to_scission, chains) << "\n";
    std::cout << "ranges distance = " << ranges_search(segment_to_scission, chains) << "\n";
}
