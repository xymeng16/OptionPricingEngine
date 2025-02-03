#include "error_messages.h"
#include "utils/numerical_methods.h"
#include <gtest/gtest.h>

TEST(NumericalMethodsTest, NewtonRaphson) {
  const std::function<double(double)> f = [](const double x) {
    return x * x - 2;
  };
  const std::function<double(double)> f_prime = [](const double x) {
    return 2 * x;
  };

  double root = NumericalMethods::newtonRaphson(f, f_prime, 1.0);
  ASSERT_NEAR(root, std::sqrt(2), 1e-9);

  root = NumericalMethods::newtonRaphson(f, f_prime, -1.0);
  ASSERT_NEAR(root, -std::sqrt(2), 1e-9);

  std::function<double(double)> g = [](const double x) { return x * x + 1; };
  std::function<double(double)> g_prime = [](const double x) { return 2 * x; };
  ASSERT_THROW(NumericalMethods::newtonRaphson(g, g_prime, 1.0),
               std::runtime_error);
}

// TODO: find a proper test case for this
// TEST(NumericalMethodsTest, NewtonRaphsonDerivativeCloseToZero) {
//   const std::function<double(double)> f = [](const double x) {
//     return x * x * x + 1;
//   };
//   const std::function<double(double)> f_prime = [](const double x) {
//     return 3 * x * x;
//   };
//
//   ASSERT_THROW(NumericalMethods::newtonRaphson(f, f_prime, 100),
//                std::runtime_error);
// }

TEST(NumericalMethodsTest, NewtonRaphsonMaxIterations) {
  // hard to converge
  const std::function<double(double)> f = [](const double x) {
    return std::exp(-x * x) - 0.5;
  };
  const std::function<double(double)> f_prime = [](const double x) {
    return -2 * x * std::exp(-x * x);
  };

  ASSERT_THROW(NumericalMethods::newtonRaphson(f, f_prime, 100.0, 1e-9, 10),
               std::runtime_error);
}

TEST(ErrorMessagesTest, ErrorMessages) {
  ASSERT_EQ(ErrorMessages::BlackScholes::kInvalidSpotPrice,
            "Spot price must be positive.");
  ASSERT_EQ(ErrorMessages::BlackScholes::kInvalidStrikePrice,
            "Strike price must be positive.");
  ASSERT_EQ(ErrorMessages::BlackScholes::kInvalidRiskFreeRate,
            "Risk-free rate must be non-negative.");
  ASSERT_EQ(ErrorMessages::BlackScholes::kInvalidTimeToMaturity,
            "Time to maturity must be positive.");
  ASSERT_EQ(ErrorMessages::BlackScholes::kInvalidVolatility,
            "Volatility must be positive.");
  ASSERT_EQ(ErrorMessages::BinomialTree::kInvalidNumSteps,
            "Number of steps must be positive.");
  ASSERT_EQ(ErrorMessages::ImpliedVol::kInvalidMarketPrice,
            "Market price must be positive.");
}