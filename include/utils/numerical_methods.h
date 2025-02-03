#ifndef NUMERICAL_METHODS_H
#define NUMERICAL_METHODS_H

#include <common.h>

class NumericalMethods {
public:
  // Newton-Raphson method for finding roots
  static double newtonRaphson(const std::function<double(double)> &f,
                              const std::function<double(double)> &fprime,
                              double initialGuess, double tolerance = 1e-9,
                              int maxIterations = 1000);
};

#endif // NUMERICAL_METHODS_H