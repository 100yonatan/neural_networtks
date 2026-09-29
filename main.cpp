#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <string>

#include "Matrix.h"
#include "Dense.h"
#include "Sigmoid.h"
#include "ReLU.h"
#include "MSELoss.h"
#include "Sequential.h"



// Struct to hold metadata and binary bit representations
struct Sample {
    int a;
    int b;
    int expected_xor;
    std::vector<float> input_bits;   // 8 bits: [a3, a2, a1, a0, b3, b2, b1, b0]
    std::vector<float> output_bits;  // 4 bits: [c3, c2, c1, c0]
};

int main() {
    // -------------------------------------------------------------
    // 1. Generate All 256 Pairs of 4-bit Numbers (0 to 15)
    // -------------------------------------------------------------
    const size_t total_samples = 256;
    std::vector<Sample> dataset;
    dataset.reserve(total_samples);

    for (int a = 0; a < 16; ++a) {
        for (int b = 0; b < 16; ++b) {
            int c = a ^ b;
            Sample sample;
            sample.a = a;
            sample.b = b;
            sample.expected_xor = c;
            sample.input_bits.resize(8);
            sample.output_bits.resize(4);

            // Extract 4 bits for number 'a' (MSB to LSB)
            for (int bit = 0; bit < 4; ++bit) {
                sample.input_bits[bit] = static_cast<float>((a >> (3 - bit)) & 1);
            }

            // Extract 4 bits for number 'b' (MSB to LSB)
            for (int bit = 0; bit < 4; ++bit) {
                sample.input_bits[4 + bit] = static_cast<float>((b >> (3 - bit)) & 1);
            }

            // Extract 4 bits for expected output 'c' (MSB to LSB)
            for (int bit = 0; bit < 4; ++bit) {
                sample.output_bits[bit] = static_cast<float>((c >> (3 - bit)) & 1);
            }

            dataset.push_back(sample);
        }
    }

    // -------------------------------------------------------------
    // 2. Shuffle Dataset and Perform 80/20 Train/Test Split
    // -------------------------------------------------------------
    // Fixed seed (42) for reproducible evaluation
    std::mt19937 rng(42);
    std::shuffle(dataset.begin(), dataset.end(), rng);

    const size_t train_size = 205; // 80% of 256
    const size_t test_size = total_samples - train_size; // 51 samples (20%)

    Matrix X_train(train_size, 8);
    Matrix Y_train(train_size, 4);
    Matrix X_test(test_size, 8);
    Matrix Y_test(test_size, 4);

    // Populate Train Matrix
    for (size_t i = 0; i < train_size; ++i) {
        for (size_t j = 0; j < 8; ++j) {
            X_train(i, j) = dataset[i].input_bits[j];
        }
        for (size_t j = 0; j < 4; ++j) {
            Y_train(i, j) = dataset[i].output_bits[j];
        }
    }

    // Populate Test Matrix
    for (size_t i = 0; i < test_size; ++i) {
        size_t idx = train_size + i;
        for (size_t j = 0; j < 8; ++j) {
            X_test(i, j) = dataset[idx].input_bits[j];
        }
        for (size_t j = 0; j < 4; ++j) {
            Y_test(i, j) = dataset[idx].output_bits[j];
        }
    }

    std::cout << "================================================================" << std::endl;
    std::cout << "                 4-Bit Bitwise XOR Experiment                  " << std::endl;
    std::cout << "================================================================" << std::endl;
    std::cout << "Total Samples: " << total_samples << std::endl;
    std::cout << "Training Samples (80%): " << train_size << std::endl;
    std::cout << "Testing Samples  (20%): " << test_size << std::endl;

    // -------------------------------------------------------------
    // 3. Build Network Architecture
    // -------------------------------------------------------------
    // 8 inputs -> Hidden layer (32 neurons) -> 4 output neurons
    Sequential model;
    model.add(std::make_unique<Dense>(8, 32));
    model.add(std::make_unique<Sigmoid>());
    model.add(std::make_unique<Dense>(32, 4));
    model.add(std::make_unique<Sigmoid>());

    MSELoss criterion;

    const int epochs = 15000;
    const float learning_rate = 0.5f;

    std::cout << "\nStarting Training Process..." << std::endl;

    // -------------------------------------------------------------
    // 4. Training Loop (Train Set Only)
    // -------------------------------------------------------------
    for (int epoch = 1; epoch <= epochs; ++epoch) {
        // Forward pass
        Matrix predictions = model.forward(X_train);

        // Compute loss
        float loss = criterion.forward(predictions, Y_train);

        // Compute gradients and backpropagate
        Matrix loss_grad = criterion.backward(predictions, Y_train);
        model.backward(loss_grad, learning_rate);

        // Print training loss periodically
        if (epoch % 1500 == 0 || epoch == 1) {
            std::cout << "Epoch " << std::setw(5) << epoch
                << " | Training Loss: " << std::fixed << std::setprecision(6) << loss << std::endl;
        }
    }

    // -------------------------------------------------------------
    // 5. Test Evaluation on Unseen Test Set
    // -------------------------------------------------------------
    std::cout << "\n================================================================" << std::endl;
    std::cout << "              Evaluating on Unseen Test Dataset                 " << std::endl;
    std::cout << "================================================================" << std::endl;

    Matrix test_predictions = model.forward(X_test);
    float test_loss = criterion.forward(test_predictions, Y_test);
    std::cout << "Final Test Set MSE Loss: " << std::fixed << std::setprecision(6) << test_loss << "\n" << std::endl;

    int total_bits = 0;
    int correct_bits = 0;
    int fully_correct_numbers = 0;

    std::cout << std::left
        << std::setw(15) << "A ^ B (Dec)"
        << std::setw(16) << "A ^ B (Bin)"
        << std::setw(16) << "Expected (Bin)"
        << std::setw(16) << "Predicted (Bin)"
        << std::setw(14) << "Pred (Dec)"
        << "Result" << std::endl;
    std::cout << "----------------------------------------------------------------------------------" << std::endl;

    for (size_t i = 0; i < test_size; ++i) {
        size_t idx = train_size + i;
        int a_val = dataset[idx].a;
        int b_val = dataset[idx].b;
        int target_dec = dataset[idx].expected_xor;

        int predicted_dec = 0;
        bool all_bits_match = true;

        std::string a_bin = "";
        std::string b_bin = "";
        std::string target_bin = "";
        std::string pred_bin = "";

        // Evaluate each of the 4 bits
        for (int bit = 0; bit < 4; ++bit) {
            a_bin += std::to_string(static_cast<int>(dataset[idx].input_bits[bit]));
            b_bin += std::to_string(static_cast<int>(dataset[idx].input_bits[4 + bit]));

            int target_bit = static_cast<int>(Y_test(i, bit));
            target_bin += std::to_string(target_bit);

            float raw_val = test_predictions(i, bit);
            int pred_bit = (raw_val >= 0.5f) ? 1 : 0;
            pred_bin += std::to_string(pred_bit);

            predicted_dec = (predicted_dec << 1) | pred_bit;

            total_bits++;
            if (pred_bit == target_bit) {
                correct_bits++;
            }
            else {
                all_bits_match = false;
            }
        }

        if (all_bits_match) {
            fully_correct_numbers++;
        }

        std::string dec_str = std::to_string(a_val) + " ^ " + std::to_string(b_val);
        std::string bin_str = a_bin + " ^ " + b_bin;

        std::cout << std::left
            << std::setw(15) << dec_str
            << std::setw(16) << bin_str
            << std::setw(16) << target_bin
            << std::setw(16) << pred_bin
            << std::setw(14) << predicted_dec
            << (all_bits_match ? "[PASS]" : "[FAIL]") << std::endl;
    }

    // -------------------------------------------------------------
    // 6. Overall Metrics
    // -------------------------------------------------------------
    float bit_accuracy = (static_cast<float>(correct_bits) / total_bits) * 100.0f;
    float number_accuracy = (static_cast<float>(fully_correct_numbers) / test_size) * 100.0f;

    std::cout << "================================================================" << std::endl;
    std::cout << "                     Overall Test Metrics                       " << std::endl;
    std::cout << "================================================================" << std::endl;
    std::cout << "Total Test Samples Evaluated: " << test_size << std::endl;
    std::cout << "Individual Bit Accuracy:      " << std::fixed << std::setprecision(2) << bit_accuracy << "%" << std::endl;
    std::cout << "Full 4-Bit Number Accuracy:   " << std::fixed << std::setprecision(2) << number_accuracy << "%" << std::endl;

    return 0;
}