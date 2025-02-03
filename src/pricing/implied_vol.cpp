#include "pricing/implied_vol.h"
#include "error_messages.h"
#include "pricing/black_scholes.h"
#include "utils/numerical_methods.h"

double ImpliedVolatility::calculateImpliedVolatility(
    const EuropeanOption &option, const double &marketPrice,
    const double &tolerance, const int &maxIterations) {
  if (marketPrice <= 0.0) {
    throw std::invalid_argument(ErrorMessages::ImpliedVol::kInvalidMarketPrice);
  }

  auto f = [&](const double &sigma) {
    EuropeanOption tempOption = option;
    tempOption.setVolatilityImpl(sigma);
    return BlackScholes::price(tempOption) - marketPrice;
  };

  auto fprime = [&](const double &sigma) {
    EuropeanOption tempOption = option;
    tempOption.setVolatilityImpl(sigma);
    return BlackScholes::vega(tempOption);
  };

  try {
    constexpr double initialGuess = 0.2; // TODO: fine-tuned
    return NumericalMethods::newtonRaphson(f, fprime, initialGuess, tolerance,
                                           maxIterations);
  } catch (const std::runtime_error &e) {
    throw std::runtime_error("ImpliedVolatility calculation failed: " +
                             std::string(e.what()));
  }
}