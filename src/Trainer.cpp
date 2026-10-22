#include "nn/Trainer.h"
#include <iostream>
#include <iomanip>
#include <string>

Trainer::Trainer(Sequential& model, MSELoss& criterion, float learning_rate, int epochs) :
m_model(model), m_criterion(criterion), m_learning_rate(learning_rate), m_epochs(epochs) {}

void Trainer::train(const Matrix& X_train, const Matrix& Y_train) {
    for (int epoch = 0; epoch < m_epochs; epoch++){
        Matrix perdictions = m_model.forward(X_train);
        float loss = m_criterion.forward(perdictions, Y_train);
        Matrix loss_grad = m_criterion.backward(predictions, Y_train);
        m_model.backward(loss_grad, m_learning_rate);

        if ((epoch % 1500 + 1) == 0 || epoch == 0) {
            std::cout << "Epoch " << std::setw(5) << epoch << " | Training Loss: " << std::fixed
                      << std::setprecision(6) << loss << std::endl;
        }
    }
}
