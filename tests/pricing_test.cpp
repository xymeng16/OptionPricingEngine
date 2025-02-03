#include "options/american_option.h"
#include "options/european_option.h"
#include "pricing/binomial_tree.h"
#include "pricing/black_scholes.h"
#include "pricing/implied_vol.h"
#include "utils/numerical_methods.h"
#include <cmath>
#include <gtest/gtest.h>

TEST(BlackScholesTest, CallOptionPrice) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  double price = BlackScholes::price(option);
  ASSERT_NEAR(price, 10.4506, 1e-4);
}

TEST(BlackScholesTest, PutOptionPrice) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  double price = BlackScholes::price(option);
  ASSERT_NEAR(price, 5.5735, 1e-4);
}

TEST(BlackScholesTest, CallOptionDelta) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  double delta = BlackScholes::delta(option);
  ASSERT_NEAR(delta, 0.6368, 1e-4);
}

TEST(BlackScholesTest, PutOptionDelta) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  double delta = BlackScholes::delta(option);
  ASSERT_NEAR(delta, -0.3632, 1e-4);
}

TEST(BlackScholesTest, CallOptionGamma) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  double gamma = BlackScholes::gamma(option);
  ASSERT_NEAR(gamma, 0.0188, 1e-4);
}

TEST(BlackScholesTest, PutOptionGamma) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  double gamma = BlackScholes::gamma(option);
  ASSERT_NEAR(gamma, 0.0188, 1e-4);
}

TEST(BlackScholesTest, CallOptionVega) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  double vega = BlackScholes::vega(option);
  ASSERT_NEAR(vega, 37.524, 1e-4);
}

TEST(BlackScholesTest, PutOptionVega) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  double vega = BlackScholes::vega(option);
  ASSERT_NEAR(vega, 37.524, 1e-4);
}

TEST(BlackScholesTest, CallOptionTheta) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  double theta = BlackScholes::theta(option);
  ASSERT_NEAR(theta, -6.414, 1e-3);
}

TEST(BlackScholesTest, PutOptionTheta) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  const double &theta = BlackScholes::theta(option);
  ASSERT_NEAR(theta, -1.658, 1e-3);
}

TEST(BlackScholesTest, CallOptionRho) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  const double &rho = BlackScholes::rho(option);
  ASSERT_NEAR(rho, 53.2325, 1e-4);
}

TEST(BlackScholesTest, PutOptionRho) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  const double &rho = BlackScholes::rho(option);
  ASSERT_NEAR(rho, -41.8905, 1e-4);
}

TEST(BinomialTreeTest, AmericanCallOptionPrice) {
  AmericanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  int numSteps = 1000;
  const double &price = BinomialTree::price(option, numSteps);
  ASSERT_NEAR(price, 10.45, 1e-2);
}

TEST(BinomialTreeTest, AmericanPutOptionPrice) {
  AmericanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  constexpr int numSteps = 1000;
  const double &price = BinomialTree::price(option, numSteps);
  ASSERT_NEAR(price, 6.0896, 1e-2);
}

TEST(ImpliedVolatilityTest, ImpliedVolatilityCalculation) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  constexpr double marketPrice = 10.45;
  const double &impliedVol =
      ImpliedVolatility::calculateImpliedVolatility(option, marketPrice);
  ASSERT_NEAR(impliedVol, 0.2, 1e-2);
}