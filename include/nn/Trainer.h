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
    Trainer();
};
