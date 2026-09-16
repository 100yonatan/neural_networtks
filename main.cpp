#include <iostream>
#include "Matrix.h"
#include <cassert>


bool areFloatsClose(float a, float b, float eps = 1e-5f) {
    return std::fabs(a - b) < eps;
}

void printMatrix(const Matrix& m, size_t rows, size_t cols, const std::string& name) {
    std::cout << "--- " << name << " (" << rows << "x" << cols << ") ---" << std::endl;
    for (size_t r = 0; r < rows; r++) {
        std::cout << "[ ";
        for (size_t c = 0; c < cols; c++) {
            std::cout << m(r, c) << " ";
        }
        std::cout << "]" << std::endl;
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "     Running Matrix Class Unit Tests    " << std::endl;
    std::cout << "========================================" << std::endl;

    {
        std::cout << "[Test 1] Constructors and Indexing... ";
        Matrix m1(2, 3, 4.5f);
        assert(areFloatsClose(m1(0, 0), 4.5f));
        assert(areFloatsClose(m1(1, 2), 4.5f));

        m1(1, 1) = 9.0f; 
        assert(areFloatsClose(m1(1, 1), 9.0f));
        std::cout << "PASSED" << std::endl;
    }

    {
        std::cout << "[Test 2] Out of bounds exception... ";
        Matrix m(2, 2);
        bool caught = false;
        try {
            float val = m(2, 0); 
            (void)val;
        }
        catch (const std::exception& e) {
            caught = true;
        }
        assert(caught);
        std::cout << "PASSED" << std::endl;
    }

    {
        std::cout << "[Test 3] Matrix Addition... ";
        Matrix A(2, 2);
        A(0, 0) = 1.0f; A(0, 1) = 2.0f;
        A(1, 0) = 3.0f; A(1, 1) = 4.0f;

        Matrix B(2, 2);
        B(0, 0) = 5.0f; B(0, 1) = 6.0f;
        B(1, 0) = 7.0f; B(1, 1) = 8.0f;

        Matrix C = A + B;
        assert(areFloatsClose(C(0, 0), 6.0f));
        assert(areFloatsClose(C(0, 1), 8.0f));
        assert(areFloatsClose(C(1, 0), 10.0f));
        assert(areFloatsClose(C(1, 1), 12.0f));
        std::cout << "PASSED" << std::endl;
    }

    {
        std::cout << "[Test 4] Addition dimension mismatch... ";
        Matrix A(2, 3);
        Matrix B(3, 2);
        bool caught = false;
        try {
            Matrix C = A + B;
        }
        catch (const std::exception& e) {
            caught = true;
        }
        assert(caught);
        std::cout << "PASSED" << std::endl;
    }

    {
        std::cout << "[Test 5] Matrix Transpose... ";
        Matrix A(2, 3);
        A(0, 0) = 1.0f; A(0, 1) = 2.0f; A(0, 2) = 3.0f;
        A(1, 0) = 4.0f; A(1, 1) = 5.0f; A(1, 2) = 6.0f;

        Matrix AT = A.transpose();
        assert(areFloatsClose(AT(0, 0), 1.0f));
        assert(areFloatsClose(AT(1, 0), 2.0f));
        assert(areFloatsClose(AT(2, 0), 3.0f));
        assert(areFloatsClose(AT(0, 1), 4.0f));
        assert(areFloatsClose(AT(1, 1), 5.0f));
        assert(areFloatsClose(AT(2, 1), 6.0f));
        std::cout << "PASSED" << std::endl;
    }

    {
        std::cout << "[Test 6] Matrix Multiplication... ";
        // A: 2x3
        // [ 1, 2, 3 ]
        // [ 4, 5, 6 ]
        Matrix A(2, 3);
        A(0, 0) = 1.0f; A(0, 1) = 2.0f; A(0, 2) = 3.0f;
        A(1, 0) = 4.0f; A(1, 1) = 5.0f; A(1, 2) = 6.0f;

        // B: 3x2
        // [  7,  8 ]
        // [  9, 10 ]
        // [ 11, 12 ]
        Matrix B(3, 2);
        B(0, 0) = 7.0f;  B(0, 1) = 8.0f;
        B(1, 0) = 9.0f;  B(1, 1) = 10.0f;
        B(2, 0) = 11.0f; B(2, 1) = 12.0f;

        // C = A * B (2x2):
        // C(0,0) = 1*7 + 2*9 + 3*11 = 7 + 18 + 33 = 58
        // C(0,1) = 1*8 + 2*10 + 3*12 = 8 + 20 + 36 = 64
        // C(1,0) = 4*7 + 5*9 + 6*11 = 28 + 45 + 66 = 139
        // C(1,1) = 4*8 + 5*10 + 6*12 = 32 + 50 + 72 = 154
        Matrix C = A * B;

        assert(areFloatsClose(C(0, 0), 58.0f));
        assert(areFloatsClose(C(0, 1), 64.0f));
        assert(areFloatsClose(C(1, 0), 139.0f));
        assert(areFloatsClose(C(1, 1), 154.0f));
        std::cout << "PASSED" << std::endl;
    }

    {
        std::cout << "[Test 7] Multiplication dimension mismatch... ";
        Matrix A(2, 3);
        Matrix B(2, 3);
        bool caught = false;
        try {
            Matrix C = A * B;
        }
        catch (const std::exception& e) {
            caught = true;
        }
        assert(caught);
        std::cout << "PASSED" << std::endl;
    }

    std::cout << "\nAll Matrix tests passed successfully!\n" << std::endl;
    return 0;
}