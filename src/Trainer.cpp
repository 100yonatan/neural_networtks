#include "nn/Trainer.h"

Trainer::Trainer(Sequential& model, MSELoss& criterion, float learning_rate, int epochs) :
m_model(model), m_criterion(criterion), m_learning_rate(learning_rate), m_epochs(epochs) {}

