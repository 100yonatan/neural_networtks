#pragma once

#include "Sequential.h"
#include "MSELoss.h"
#include "Matrix.h"

class Trainer {
private:
    Sequential& m_model;
    MSELoss& m_criterion;
    float m_learning_rate;
    int m_epochs;

public:
    Trainer(Sequential& model, MSELoss& criterion, float learning_rate, int epochs);
    void train(const Matrix& X_train, const Matrix& Y_train);
    void evaluate(const Matrix& X_test, const Matrix& Y_test);
};
