
#include <iostream>
#include <vector>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Sparse>

// Compile
// g++ -std=c++14 linear_solvers.cpp -o solvers

// See https://eigen.tuxfamily.org/dox/group__TopicSparseSystems.html#title4
// for more examples

int main()
{
    using Matrix = Eigen::MatrixXd;
    using Vector = Eigen::VectorXd;
    using Matrix3 = Eigen::Matrix3d;
    using Vector3 = Eigen::Vector3d;

    using SparseMatrix = Eigen::SparseMatrix<double>;

    {
        // Dense solver for a small matrix
        Matrix3 A = Matrix3::Random();
        Vector3 b = Vector3::Random();

        Vector3 x = A.fullPivLu().solve(b);

        std::cout << "Solution norm = " << (A * x - b).norm() << std::endl;
    }

    {
        // Sparse linear system solvers

        // Size of the system
        auto constexpr n = 10;

        // Make a symmetric sparse matrix
        SparseMatrix S = Eigen::MatrixXd::Random(n, n).sparseView(0.5, 1);
        S = S.transpose() * S;

        Eigen::VectorXd b(n), x;
        b.setRandom();

        // Direct solver example

        Eigen::SimplicialLDLT<SparseMatrix> cholesky_ldlt;
        x = cholesky_ldlt.compute(S).solve(b);
        std::cout << "LDLT solver info: " << cholesky_ldlt.info() << std::endl;
        std::cout << "solution\n" << x << "\n";

        // Iterative solvers

        Eigen::ConjugateGradient<SparseMatrix, Eigen::Lower | Eigen::Upper, Eigen::IdentityPreconditioner> cg;
        cg.compute(S);
        x = cg.solve(b);
        std::cout << "CG:       #iterations: " << cg.iterations()
                  << ", estimated error: " << cg.error() << std::endl;
        std::cout << "solution\n" << x << "\n";

        Eigen::ConjugateGradient<SparseMatrix, Eigen::Lower | Eigen::Upper, Eigen::IncompleteCholesky<double>>
            incomplete_cg;
        incomplete_cg.compute(S);
        x = incomplete_cg.solve(b);
        std::cout << "CG (IC):  #iterations:  " << incomplete_cg.iterations()
                  << ", estimated error: " << incomplete_cg.error() << std::endl;
        std::cout << "solution\n" << x << "\n";

        Eigen::BiCGSTAB<SparseMatrix, Eigen::IdentityPreconditioner> bicg;
        bicg.compute(S);
        x = bicg.solve(b);
        std::cout << "BiCGSTAB: #iterations: " << bicg.iterations()
                  << ", estimated error: " << bicg.error() << std::endl;
        std::cout << "solution\n" << x << "\n";
    }
}
