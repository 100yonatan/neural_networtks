#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "Dense.h"
#include <cassert>


void print_matrix(const std::string& name, const Matrix& m)
{
    std::cout << "--- " << name << " (" << m.rows() << "x" << m.cols() << ") ---" << std::endl;
    for (size_t r = 0; r < m.rows(); ++r) {
        std::cout << "[ ";
        for (size_t c = 0; c < m.cols(); ++c) {
            std::cout << std::setw(8) << std::fixed << std::setprecision(4) << m(r, c) << " ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << "       1. Matrix Class Tests            " << std::endl;
    std::cout << "========================================" << std::endl;

    // A. Basic addition and multiplication tests
    Matrix A(2, 2);
    A(0, 0) = 1.0f; A(0, 1) = 2.0f;
    A(1, 0) = 3.0f; A(1, 1) = 4.0f;

    Matrix B(2, 2);
    B(0, 0) = 5.0f; B(0, 1) = 6.0f;
    B(1, 0) = 7.0f; B(1, 1) = 8.0f;

    print_matrix("Matrix A", A);
    print_matrix("Matrix B", B);

    Matrix C = A + B;
    print_matrix("A + B", C);
    assert(C(0, 0) == 6.0f && C(1, 1) == 12.0f);

    Matrix D = A * B;
    print_matrix("A * B", D);
    // (1*5 + 2*7 = 19), (1*6 + 2*8 = 22), (3*5 + 4*7 = 43), (3*6 + 4*8 = 50)
    assert(D(0, 0) == 19.0f && D(0, 1) == 22.0f);
    assert(D(1, 0) == 43.0f && D(1, 1) == 50.0f);

    // B. Transpose test
    Matrix T = A.transpose();
    print_matrix("A Transposed", T);
    assert(T(0, 1) == 3.0f && T(1, 0) == 2.0f);

    // C. add_bias test
    Matrix bias(1, 2);
    bias(0, 0) = 10.0f;
    bias(0, 1) = 20.0f;

    Matrix mat_for_bias = A;
    mat_for_bias.add_bias(bias);
    print_matrix("A after add_bias([10, 20])", mat_for_bias);
    assert(mat_for_bias(0, 0) == 11.0f && mat_for_bias(0, 1) == 22.0f);
    assert(mat_for_bias(1, 0) == 13.0f && mat_for_bias(1, 1) == 24.0f);

    std::cout << ">> All Matrix tests passed successfully!\n\n";

    std::cout << "========================================" << std::endl;
    std::cout << "       2. Dense Layer Tests             " << std::endl;
    std::cout << "========================================" << std::endl;

    // A. Layer creation: 2 inputs -> 3 output neurons
    const size_t in_features = 2;
    const size_t out_features = 3;
    Dense dense_layer(in_features, out_features);

    // B. Check weights and biases dimensions
    print_matrix("Initialized Weights (Xavier)", dense_layer.get_weights());
    print_matrix("Initialized Biases (Zeros)", dense_layer.get_biases());

    assert(dense_layer.get_weights().rows() == in_features);
    assert(dense_layer.get_weights().cols() == out_features);
    assert(dense_layer.get_biases().rows() == 1);
    assert(dense_layer.get_biases().cols() == out_features);

    // Verify biases are initialized to zero
    for (size_t c = 0; c < out_features; ++c) {
        assert(dense_layer.get_biases()(0, c) == 0.0f);
    }

    // C. Forward pass test with batch of 2 examples
    Matrix X(2, 2);
    X(0, 0) = 1.0f;  X(0, 1) = 2.0f;
    X(1, 0) = 0.5f;  X(1, 1) = -1.0f;

    print_matrix("Input Batch X (2 examples)", X);

    Matrix output = dense_layer.forward(X);
    print_matrix("Forward Output Z = X*W + b", output);

    assert(output.rows() == 2);
    assert(output.cols() == out_features);

    // D. Polymorphism test (via Layer pointer)
    std::unique_ptr<Layer> polymorphic_layer = std::make_unique<Dense>(2, 1);
    Matrix poly_out = polymorphic_layer->forward(X);
    print_matrix("Polymorphic Forward Output (2x1)", poly_out);
    assert(poly_out.rows() == 2 && poly_out.cols() == 1);

    std::cout << ">> All Dense layer tests passed successfully!" << std::endl;

    return 0;
}