#include "utils/numerical_methods.h"
#include <cmath>
#include <stdexcept>

double NumericalMethods::newtonRaphson(
    const std::function<double(double)> &f,
    const std::function<double(double)> &fprime, const double initialGuess,
    const double tolerance, const int maxIterations) {
  double x = initialGuess;
  for (int i = 0; i < maxIterations; ++i) {
    const double fx = f(x);
    if (std::abs(fx) < tolerance) {
      return x; // converged
    }

    double fprimex = fprime(x);
    std::cout << "fprimex: " << fprimex << ", x: " << x << std::endl;
    if (std::abs(fprimex) < 1e-15) {
      throw std::runtime_error("Newton-Raphson: Derivative is close to zero.");
    }

    x = x - fx / fprimex;
  }

  throw std::runtime_error(
      "Newton-Raphson: Maximum iterations reached without convergence.");
}