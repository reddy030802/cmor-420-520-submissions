#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

// matrix A
std::vector<std::vector<double>> createMatrix(int n, double h) {
    std::vector<std::vector<double>> A(n+1, std::vector<double>(n+1, 0.0));
    for (int i = 0; i <= n; ++i) {
        A[i][i] = 2.0 / (h * h);
        if (i > 0) {
            A[i][i-1] = -1.0 / (h * h);
        }
        if (i < n) {
            A[i][i+1] = -1.0 / (h * h);
        }
    }
    return A;
}

// product of matrix A and vector u
std::vector<double> multiplyMatrixVector(const std::vector<std::vector<double>>& A, const std::vector<double>& u) {
    std::vector<double> result(u.size(), 0.0);
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < u.size(); ++j) {
            result[i] += A[i][j] * u[j];
        }
    }
    return result;
}

//norm of vector r
double norm(const std::vector<double>& r) {
    double sum = 0.0;
    for (double val : r) {
        sum += val * val;
    }
    return std::sqrt(sum);
}

int main() {
    // n and h
    const int n = 100;
    const double h = 1.0 / n;

    // matrix A
    auto A = createMatrix(n, h);

    // Initialize vectors u and b
    std::vector<double> u(n+1, 0.0);
    std::vector<double> b(n+1);
    for (int i = 0; i <= n; ++i) {
        b[i] = std::cos(M_PI * i * h);
    }

    // 'a'
    const double a = 0.5 * h * h;

    // iterate
    int iterations = 0;
    std::vector<double> r(n+1);
    auto start = std::chrono::high_resolution_clock::now();

    do {
        // r = b - A * u
        auto Au = multiplyMatrixVector(A, u);
        for (int i = 0; i <= n; ++i) {
            r[i] = b[i] - Au[i];
        }

        // u = u + a * r
        for (int i = 0; i <= n; ++i) {
            u[i] += a * r[i];
        }

        iterations++;
    } while (norm(r) >= 1e-3);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    double timePerIteration = elapsed.count() / iterations;

    // output
    std::cout << "Number of iterations: " << iterations << std::endl;
    std::cout << "Final norm of r: " << norm(r) << std::endl;
    std::cout << "Time per iteration: " << timePerIteration << " seconds" << std::endl;

    return 0;
}
