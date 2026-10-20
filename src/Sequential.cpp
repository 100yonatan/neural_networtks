#include "nn/Sequential.h"
#include <stdexcept>
#include <fstream>

void Sequential::add(std::unique_ptr<Layer> layer)
{
    if (!layer)
        throw std::invalid_argument("Cannot add a null layer to Sequential model!");

    m_layers.push_back(std::move(layer));
}

Matrix Sequential::forward(const Matrix& input)
{
    if (m_layers.empty())
        throw std::runtime_error("Cannot run forward on an empty Sequential model!");

    Matrix current_result = input;

    for (auto& layer_ptr : m_layers) {
        if (layer_ptr != nullptr)
            current_result = layer_ptr->forward(current_result);
    }

    return current_result;
}

void Sequential::backward(const Matrix& loss_grad, float learning_rate)
{
    if (m_layers.empty())
        throw std::runtime_error("Cannot run backward on an empty Sequential model!");

    Matrix current_grad = loss_grad;

    for (auto it = m_layers.rbegin(); it != m_layers.rend(); ++it) {
        if (*it != nullptr) {
            current_grad = (*it)->backward(current_grad, learning_rate);
        }
    }
}

void Sequential::save(const std::string& file_path) const
{
    std::ofstream out(file_path, std::ios::binary);
    if(!out.is_open())
        throw std::runtime_error("Error: Could not open file for writing: " + file_path);

    for (const auto& layer_ptr : m_layers) {
        layer_ptr->save(out);
    }
    out.close();
}

void Sequential::load(const std::string& file_path)
{
    std::ifstream in(file_path, std::ios::binary);
    if(!in.is_open())
        throw std::runtime_error("Error: Could not open file for reading: " + file_path);

    for (auto& layer_ptr : m_layers) {
        if (layer_ptr != nullptr) {
            layer_ptr->load(in);
        }
    }

    if (in.fail() && !in.eof()) {
        throw std::runtime_error("Error: Corrupted or incomplete model file: " + file_path);
    }

    in.close();
}
