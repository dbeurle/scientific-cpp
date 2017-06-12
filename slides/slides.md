name: inverse
layout: true
class: center, middle, inverse
<!-- ####################################################################### -->


---
# Scientific c++
Combining high performance and elegant datastructures ...

.footnote[ibnm - Darcy Beurle]

<!-- ####################################################################### -->
---
layout: false
# House keeping

**Series:**
This is a three hour workshop for the IRTG1627.

**Audience:**
Beginner to intermediate

**Questions:**
Interactive session, ask as we go along!

<br>
--

**Slides:**
GitHub: github.com/dbeurle/scientific-cpp

**Email:**
darcy.beurle@ibnm.uni-hannover.de

<!-- ####################################################################### -->
---
layout: false
# Overview

.leftside[
- Hour 1:
 - Introduction to the type system
 - Value, reference, pointer and const semantics
 - Functions
- Hour 2:
 - STL algorithms and lambdas
 - (Future) ranges library
- Hour 3:
 - Linear algebra library (Eigen)
 - Compiler optimization
]

--

.rightside[
Code
.good[
```c++
// good code marked with green bar.
```
]

.bad[
```c++
// bad code marked with red bar.
```
]

```c++
// example/neutral code, no bar
```

C++11 standard if not stated otherwise.  Enable using -std=c++11
]

--

.rightside[Just make your life easier and use -std=c++14]

---
layout: false
# Motivation

Why are we interested in c++ as a scientific tool?

--

We want fast, safe and expressive code!

--

**example:** some horrible c++ code with lots of 'errors':

.bad[
```c++
// x,y are lists, e.g.
double dot_product(std::vector<double> x, std::vector<double> y)
{
  double sum = 0.0;
  int xsize = x.size();
  for (int i = 0; i < xsize; ++i)
      sum += x[i] * y[i];
  return sum;
}
```
]

--
... and a piece of art:

.good[
```c++
// Your job by the end of this course (prize for the shortest and most efficient!)
```
]


<!-- ####################################################################### -->
---
template: inverse
# Variable declaration
How we get stuff done...

<!-- ####################################################################### -->
---
layout: false
# Types

.leftside[
- Variable declaration is essential!
- type (modifier) variable_name (= type_instantiation)
- float (32 bit floating point)
- double (64 bit floating point)
- int (usually 32 bit 2^31)
- long (usually 64 bit 2^63)
- unsigned types (2^size)
- boolean (true / false)
- Don't use unsigned types where possible
- Use long if more than 2 billion elements required
- Can check using std::numeric_limits
]

.rightside[.good[
```c++
auto val = 0.0f; // float
auto val = 0.0;  // double
auto val = 0;    // int
auto val = 0u;   // unsigned int
auto val = 0l;   // long
auto val = 0ul;  // unsigned long
auto val = true; // bool

// Double explicitly stated
double val{0.0};

```
]
.bad[
```c++
// Implicit conversion int to double
double val = 0;

```
]]

<!-- ####################################################################### -->
---
layout: false
# Scope

.leftside[
- Variables destructed when outside of scope
- Denoted by curly braces {}
- Handled by a class destructor or deleter
- Avoid top declaring variables
- Declare at site of initialization
]

.rightside[
```c++
auto val = 0.0;
{
    val = 1.0;
    auto inner_val = val;
}
// inner_val not visible here

for (auto r : range)
{
    int a = 0;
    // a is only visible until }
}

```
]

<!-- ####################################################################### -->
---
layout: false
# Namespace

.leftside[
- Scoping for symbol names (functions, classes, variables)
- Declared by namespace <name> {}
- Accessed by :: operator (colon - colon)
- Separate logical parts in code
- Avoid name clashes with same function

```c++
namespace irtg1627
{
    int coolness = 10;
}
// Print out value
std::cout << irtg1627::coolness << std::endl;

```

.bad[
```c++
cout << "Hello world" << endl;
// Which sort is this?
sort(v.begin(), v.end());
```
]
]
--
.rightside[.good[
```c++
// Define a local scope so using isn't
// going to pollute the entire file
{
    using namespace std;
}
```
]
.bad[
```c++
// In header file or globally
using namespace std;
```
]
]

<!-- ####################################################################### -->
---
layout: false
# References

.leftside[
- Store a reference to a memory address
- Cannot store a null type - must be initialized
- Could point to a deleted address (or invalid) - dangling reference
- Allow 'local' type access
- Accessed using like normal variables
- Simple and preferred to what's next (pointers)
]

.rightside[
```c++
std::vector<double> v(100, 0.0);

std::vector<double>& w = v;
// w can be used like v
w.resize(110, 0.0);

```
]

<!-- ####################################################################### -->
---
layout: false
# Functions

- Return type and modifiers
- Function name
- Arguments
- Modifiers for methods (in a class)
- Arguments: (value (copy), reference, pointer)
- AXPY algorithm looks like y = a*x + y
.good[
```c++
void axpy(std::vector<double> const& x,  // Const ref
          std::vector<double>& y,        // Ref
          double const a);               // Copy
```
]
.bad[
```c++
std::vector<double> axpy(std::vector<double> x,  // Copy
                         std::vector<double> y,  // Copy
                         double a);              // Copy
```
]

<!-- ####################################################################### -->
---
layout: false
# Pointers

.leftside[
- Store a memory address (a location in memory)
- Can store a nullptr type (does not point to anything)
- Used in dynamically allocated memory
- Accessed using offset operator [] or ->
- Deferenced using *
- Deallocated using delete or delete[] otherwise memory leak
- Are confusing for engineers
]

.rightside[
```c++
double* data = new double[N];
for (int i = 0; i < N; ++i)
    data[i] = some_val;

double* data2 = data;
delete[] data2;

// Segmentation fault!
data[0] = 10.0;

```

```c++
// Lose hook into the memory
double* data = new double[N];

data = nullptr;
// Segfault and memory leak
delete data;
```
]

<!-- ####################################################################### -->
---
layout: false
# Smart pointers

- Ownership semantics!
- Automatically dellocate when out of scope
- std::unique_ptr<>
- std::shared_ptr<>
- Use std::make_ helper functions to allocate memory
- No more new and delete keywords in code

.good[
```c++
#include <memory>

// c++14
std::unique_ptr<double> data = std::make_unique<double>(N);

// c++11
std::unique_ptr<double> data = new double[N];
```
]
.bad[
```c++
double* data = new double[N];
for (int i = 0; i < N; ++i)
{
    data[i] = some_val;
}
```
]

<!-- ####################################################################### -->
---
layout: false
# Range based for loop

.leftside[
- Iteration over a container
- Terse representation of a regular for loop
- Not usable for multiple containers
- Type return can be copy, reference or pointer
- Conceptual changes in programming model
]

.rightside[
.good[
```c++
std::vector<double> v(1000, 0.0);
for (auto& v_i : v)
    v_i += 1.0;
```
]
.bad[
```c++
std::vector<double> v(1000, 0.0);
for (int i = 0; i < v.size(); i++)
    v[i] += 1.0;
```
]]

--

.leftside[]

.rightside[
.good[
```c++
std::vector<MeshType> meshes;
...
for (auto& mesh : meshes)
{
    mesh.update_internal_variables();
}
```]]

<!-- ####################################################################### -->
---
template: inverse
# Containers
Where we store our numbers...

<!-- ####################################################################### -->
---
layout: false
# std::tuple

.leftside[
Tuples are collection of different (or same) types
- Useful for logical grouping
 - Key-value pair
 - Matrix and dof list
 - Multiple function return values
- Retrieve using std::get<0>(tuple_name)
- Make using std::make_tuple()
- Fixed size at compile time
- Constant time access
- http://en.cppreference.com/w/cpp/utility/tuple

A pair (std::pair<,>) is a specialisation of tuple with
- Access via .first and .second members
- Created using std::make_pair(,)
- Used extensively in associative containers
 - Pointer and status flag
]

.rightside[
```c++
// Deduce type std::tuple<?, ?>
auto mytuple = std::make_tuple(0.2f, 1l);

// c++14
double value = std::get<0>(mytuple);
int index = std::get<1>(mytuple);

// c++17
auto [value, index] = mytuple;

```
]


<!-- ####################################################################### -->
---
layout: false
# std::set

.leftside[
- Collection of unique objects
- Logarithmic search, removal and insertion time
- No guarantee on the order of values
- Linked list implementation so bad cache coherency (see flat_set)
- Returns a pair: iterator to the element and bool success flag
- http://en.cppreference.com/w/cpp/container/set
]

.rightside[
.good[
```c++
std::set<int> unique_values;

// Insert tries to insert a value,
// then returns a iterator (pointer-like)
// to the inserted value and whether it
// was just inserted or already there
auto state = unique_values.insert(0);

// Check if the value was inserted correctly
assert(*state.first == 0);

// true -> it was inserted
// false -> it was not inserted
//          (already there)
bool inserted = state.second;
```
]]

<!-- ####################################################################### -->
---
layout: false
# Maps

.leftside[
## std::map
- Maps unique keys to values
- Key must be comparable and const
- Values can be mutable
- Logarithmic search, insertion and removal
- Sorted keys by comparison function
]
.rightside[
.good[
```c++
std::map<std::string, int> map;
map["Hello"] = 0;
map["World"] = 1;

auto found = map.find("Hello");

auto key = found->first; // == Hello
auto value = found->second; // == 0
```
]]

<br>
--
.leftside[
## std::unordered_map
- Similar to map (key, pair)
- No longer ordered (dur)
- Constant time lookups (hash table)
- Preferable to std::map for quickly hashable keys
]

.rightside[.good[
```c++
std::unordered_map<std::string, double> map;
map["Hello"] = 0.0;
map["World"] = 1.0;

auto found = map.find("World");

auto key = found->first; // == World
auto value = found->second; // == 1.0

```
]]

<!-- ####################################################################### -->
---
# Right tool for the job

.leftside[
- std::vector
  - Many similar types to store e.g, displacements, names, nodal connectivities
  - Constant access times to a given location
  - Fast range access

<br>

- std::tuple
  - A few different types to store e.g. stiffness matrix and dofs
  - Fast access and contiguous in memory
]

.rightside[
- std::set
  - Multiple unique items to store e.g. unique dofs in a mesh
  - Need to do set operations (unions etc)

<br>

- std::map, std::unordered_map
  - Map from a key to a value (fancy look-up table) e.g. name to boundary mesh mapping
  - Need to get quickly the value for a key (unordered_map)
  - Iterate over the map quickly to get the value for a key (unordered_map)
]



<!-- ####################################################################### -->
---
layout: false
# Iterators (begin, end and friends)

.leftside[
- Most data structures are driven by iterators
- Abstraction which optimizes away but allows for generic algorithms
- E.g: sorting works on lists, vectors, tuples, valarrays etc
- Alternative to index based access

### Benefits

- std::distance(it1, it2) - Distance between two iterators independent of data structure
- std::next(it1, N) - Iterate it1 through N steps
- Use range based for loops
- Range based algorithms require beginning and ending iterators
]

--

.rightside[.bad[
```c++
std::vector<double> vec(100);
auto endIt = vec.end();
auto it = vec.begin();
for (; it != endIt; it++)
    *it = 1.0;

```
]
.good[
```c++
std::vector<double> vec(100);
for (auto& v : vec)
    v = 1.0;

// Probably more succient
std::fill(vec.begin(), vec.end(), 1.0);
// or more simply in this case
// std::vector<double> vec(100, 1.0);
```
]
]

<!-- ####################################################################### -->
---
template: inverse
# Algorithms
Where we modify our numbers...

<!-- ####################################################################### -->

---

layout: false
# Algorithms

.leftside[
- Many common algorithms available (from c++17 some also parallelized)
- std::transform, std::accumulate, std::sort, std::for_each, std::find, std::count, std::fill
- Can specify predicates on std::find_if and friends through lambdas (closures)
- Somewhat tedious to specify ranges (see range-v3 library later)
]
--

.rightside[.good[
```c++
std::vector<int> v = {1, 3, 2, 0};
std::sort(v.begin(), v.end());
// v = {0, 1, 2, 3};
```
]]

.rightside[.bad[
```c++
std::vector<double> vec(100);
std::iota(vec.begin(), vec.end(), 0);

auto sum = std::accumulate(vec.begin(), vec.end(), 0);

```
]
.good[
```c++
std::vector<double> vec(100);
std::iota(vec.begin(), vec.end(), 0.0);

auto sum = std::accumulate(vec.begin(), vec.end(), 0.0);


```
]
]

<!-- ####################################################################### -->

---

layout:false
# Lambdas
- Unnamed (anomymous) functions with an overloaded () operator
- Allows a generic algorithm to handle user defined functions

[] specifies capture properties:
- [] - No capture
- [&] - By reference
- [=] - By value

Followed by:
- (input argument) - Type that enters the function (depends on the std algorithm)
- {} - Function scope ended with });

.good[
```c++
std::string str {"ThiS sTriNG is IMPOSsible To paRSE"};
std::transform(str.begin(), str.end(), str.begin(), [](auto const character) {
    return std::to_lower(character);
});
// Check if contains an a
auto loc = std::find_if(str.begin(), str.end(), [](auto const character) {
    return character == 'a';
});
```
]


<!-- ####################################################################### -->
---
template: inverse
# Algorithms 2.0
Where we modify our numbers again...


<!-- ####################################################################### -->

---

layout: false
# Range v3 library

- Range-v3 library for inclusion in C++20 but available on GitHub
- The same set of common algorithms available
- Reduces requirement on begin and end iterators and allows for lazy evaluation
- https://ericniebler.github.io/range-v3/index.html

--

.good[
```c++
ranges::sort(v);
ranges::accumulate(v, 10.0);
ranges::fill(v, 0.0);
```
]

<!-- ####################################################################### -->

---

layout: false
# Range views

- Provides a 'view' into the vector
- Pipe operator (|) allows different filters / functions to be applied to the data
- Most algorithms available to modify data structures

--

.good[
```c++
#include <vector>
#include <range/v3/view.hpp>
...
std::vector<int> vi{1,2,3,4,5,6,7,8,9,10};

using namespace ranges;

auto rng = vi | view::remove_if([](int i){return i % 2 == 1;})
              | view::transform([](int i){return std::to_string(i);});

// rng == {"2","4","6","8","10"};
```
]

<!-- ####################################################################### -->

---

layout: false
# Range actions

- Actions mutate the data structure (not read-only)
- Includes algorithms such as sort, unique etc
- Same pipe operator applies from the previous slide

--

.good[
```c++
#include <vector>

#include <range/v3/action.hpp>
...
std::vector<std::vector<int>> const nodal_connectivity{{0, 3, 1, 2},
                                                       {3, 4, 1, 2},
                                                       {1, 0, 7}};
// Remove duplicates in an array of arrays
std::vector<int> essential_nodes = std::ref(nodal_connectivity)
                                 | action::join
                                 | action::sort
                                 | action::unique;  // {0, 1, 2, 3, 4, 7}
```
]

<!-- ####################################################################### -->

---

layout:false
# time.to_code()
- Exercise1.cpp
  - Use std::transform to compute daxpy
  - http://en.cppreference.com/w/cpp/algorithm/transform

- Exercise2.cpp
  - Use multiple algorithms in succession
  - http://en.cppreference.com/w/cpp/algorithm/transform
  - http://en.cppreference.com/w/cpp/algorithm/unique
  - http://en.cppreference.com/w/cpp/algorithm/sort
  - http://en.cppreference.com/w/cpp/container/vector

- Can work in pairs, ask questions along the way

<!-- ####################################################################### -->

---
template: inverse
# Linear algebra!
BLAS 1, 2, 3 and sparse operations

<!-- ####################################################################### -->

---

layout: false
# Linear algebra libraries

Engineers will encounter many linear algebra problems including
- Vector and matrix operations
- Sparse matrices and specialised data structures
- Solution of dense and sparse systems
- Least squares, norms, dot and cross products, rotation matrices...

These are painful to code and optimise.  Offload these operations to a library such as
- Blaze https://bitbucket.org/blaze-lib/blaze
- Eigen http://eigen.tuxfamily.org/index.php?title=Main_Page

We will use Eigen in this workshop however Blaze is also very good but lacks sparse solvers.
- Both libraries are header only with the option to add optimised BLAS backends
- Eigen will work with older compilers
- Blaze only works with c++14 compatible compilers (code is nicer)

<!-- ####################################################################### -->

---

layout: false
# BLAS 1

Consists of vector and scalar operations

.leftside[
- Memory access is critical and efficient use of vector registers
- Involves complex low level programming
- Standard algorithms are typically vectorised - but not optimally
- Trade-off?

One of the great of discoveries in c++ is expression templates.
- Specialized libraries (Blaze, Eigen)
- Allow for MATLAB like syntax with excellent performance
- Avoid temporary vectors and memory allocation
- Consider: d = a + b / 2.0 + c;
]

--

.rightside[
.bad[
```c++
std::vector<double> a(100, 1.0), b(100, 3.0),
                    c(100, 1.5), d(100, 0.0);
for (int i = 0; i < a.size(); i++)
{
    d[i] = a[i] + b[i] / 2.0 + c[i];
}
```
]
.good[
```c++
#include <eigen3/Eigen/Dense>
...
using Vector = Eigen::VectorXd;

Vector a = Vector::Ones(100);
Vector b = 3.0 * a,  c = 1.5 * a;

Vector d = a + b / 2.0 + c;
```
]
]

<!-- ####################################################################### -->

---

layout: false
# BLAS 2

Matrix - vector operations

.leftside[
- Memory access and efficient use of vector registers is even more important
- Involves complex low level programming and advanced blocking algorithms
- No equivalent standard library BLAS level 2 operations

Expression templates can also help here!
- Allow for MATLAB like syntax with excellent performance
- (Sometimes) avoid temporary vectors and memory allocation
- Consider: b = A * x;
]

--

.rightside[
```c++
using Matrix = Eigen::MatrixXd;
using Vector = Eigen::VectorXd;

Matrix A = Matrix::Random(8, 8);
Vector x = Vector::Random(8);

Vector b = A * x;
```
]

<!-- ####################################################################### -->

---

layout: false
# BLAS 3

Matrix - matrix operations

.leftside[
- Memory access and efficient use of vector registers is even more important
- Involves complex low level programming and advanced blocking algorithms
- No equivalent standard library BLAS level 3 operations

Expression templates can also help here!
- Allow for MATLAB like syntax with excellent performance
- (Sometimes) avoid temporary vectors and memory allocation
- Consider: k_e += B^T \* D \* B \* w \* j;
]

--

.rightside[
```c++
using Matrix = Eigen::MatrixXd;

Matrix B = Matrix::Random(3, 4 * 2);
Matrix D = Matrix::Random(3, 3);

Matrix k_e = Matrix::Zero(8, 8);
...
k_e += B.transpose() * D * B * w * j;
```
]

<!-- ####################################################################### -->

---

layout: false
# Quick case study: Continuum mechanics

.leftside[
We often need to compute quadrature point values involving inverses, determinants and multiplications
- Mostly a fixed size (second order tensor of 2 or 3 dimensions)
- Computationally expensive portion, looking for easy optimisations
- Exploit known fixed size matrices to perform faster floating point operations
- Exploiting symmetry is not always a good solution
 - Reduces ability to vectorise code efficiently
 - Makes code harder to read
 - Does save bandwidth and storage
]

--

.rightside[
```c++
using Matrix3 = Eigen::Matrix3d;

Matrix3 sym(Matrix3 const& A)
{
    return 0.5 * (A + A.transpose());
}
// Deformation gradient
Matrix3 F = ...

// Compute the time derivative
Matrix3 dF_dt = F - Matrix3::Identity();

auto const j = F.determinant();

// Rate of deformation = sym (dF_dt * F_inv)
Matrix3 D = sym(dF_dt * F.inverse());


```
]

<!-- ####################################################################### -->

---

layout: false
# Solving linear systems

Includes dense and sparse solvers

.leftside[
Eigen includes direct and iterative solvers as well as decompositions
- Direct: LU, Cholesky, LDLt, LLt, QR
- Iterative: Conjugate gradient, BiCGStab, GMRES.
- SVD etc
Includes specialised algorithms for size dependent matrices
- A 2x2 or 3x3 matrix can be more efficiency inverted by cofactor expansion
  - Eigen::Matrix2d and Eigen::Matrix3d
  - Not resizable and not dynamically allocated
  - Internal data layout highly optimised for vectorisation
]

--

.rightside[
```c++
using Matrix3 = Eigen::Matrix3d;
using Vector3 = Eigen::Vector3d;

Matrix3 A = Matrix3::Random();
Vector3 b = Vector3::Random();
Vector3 x = A.fullPivLu().solve(b);

// Or for larger matrices
Eigen::LLT<Eigen::MatrixXd> llt;
llt.compute(A);  // Factorise
x = llt.solve(b); // Solve

```
]

<!-- ####################################################################### -->

---
template: inverse
# Optimisations

<!-- ####################################################################### -->

---

layout: false
# Compiler optimisations

.leftside[
Most code in C++ relies on optimisations being turned on, otherwise can be very slow indeed!
- Inlining functions
- Memory alignment
- Vectorisations
- Dead code elimination
- Return value optimisation (moving rather than copying)
- Can be unsafe for poorly written code (using -Wall) for warnings

Optimisation flags
- -O1, -O2, -O3 (apply different levels of optimisation)
- -march=native (tune for this machine, not likely to work on other machines)
- -lto (link time optimisations)
]

.rightside[
```
g++ -O3 -march=native -Wall *.cpp
clang++ -O3 -march=native -Wall *.cpp
```
]

<!-- ####################################################################### -->

---

layout: false
# Compiler optimisations

.leftside[
Cool - but useless - compile time computation
- Make the compiler do numerical computations
- Limited practical use but can make things easier to understand
- Perform divisions and multiplications of compile time constants only
- Marking as ```const``` can help
- Marking as ```constexpr``` is the best when possible

We can even make a compiler to numerical integration

www.godbolt.org and NumericalIntegration.cpp

]

<!-- ####################################################################### -->

---
template: inverse
# end
