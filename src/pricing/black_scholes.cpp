#include "pricing/black_scholes.h"
#include "error_messages.h" // Include the header for error messages
#include <cmath>
#include <stdexcept>

// cdf of the normal distribution
double BlackScholes::normal(const double &x) {
  constexpr double a1 = 0.31938153;
  constexpr double a2 = -0.356563782;
  constexpr double a3 = 1.781477937;
  constexpr double a4 = -1.821255978;
  constexpr double a5 = 1.330274429;
  // constexpr double pi = 3.14159265358979323846;
  constexpr double one_over_sqrt_two_pi = 0.39894228040143267793994605993438;

  const double k = 1.0 / (1.0 + 0.2316419 * std::abs(x));
  const double cnd = one_over_sqrt_two_pi * std::exp(-x * x / 2.0) *
                     (a1 * k + a2 * k * k + a3 * std::pow(k, 3) +
                      a4 * std::pow(k, 4) + a5 * std::pow(k, 5));

  if (x >= 0.0) {
    return 1.0 - cnd;
  }
  return cnd;
}

double BlackScholes::calculate_d1(const EuropeanOption &option) {
  const double S = option.getSpotPrice();
  const double K = option.getStrikePrice();
  const double r = option.getRiskFreeRate();
  const double q = option.getDividendYield();
  const double T = option.getMaturity();
  const double sigma = option.getVolatilityImpl();

  if (S <= 0.0) {
    throw std::invalid_argument(ErrorMessages::BlackScholes::kInvalidSpotPrice);
  }
  if (K <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidStrikePrice);
  }
  if (r < 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidRiskFreeRate);
  }
  if (T <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidTimeToMaturity);
  }
  if (sigma <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidVolatility);
  }

  return (std::log(S / K) + (r - q + 0.5 * sigma * sigma) * T) /
         (sigma * std::sqrt(T));
}

double BlackScholes::calculate_d2(const EuropeanOption &option) {
  const double T = option.getMaturity();
  const double sigma = option.getVolatilityImpl();

  // Input validation using exceptions and fine-grained error messages
  if (T <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidTimeToMaturity);
  }
  if (sigma <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidVolatility);
  }

  return calculate_d1(option) - sigma * std::sqrt(T);
}

// Calculate the price of a European option using the Black-Scholes formula
double BlackScholes::price(const EuropeanOption &option) {
  const double S = option.getSpotPrice();
  const double K = option.getStrikePrice();
  const double r = option.getRiskFreeRate();
  const double q = option.getDividendYield();
  const double T = option.getMaturity();

  // Input validation using exceptions and fine-grained error messages
  if (S <= 0.0) {
    throw std::invalid_argument(ErrorMessages::BlackScholes::kInvalidSpotPrice);
  }
  if (K <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidStrikePrice);
  }
  if (r < 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidRiskFreeRate);
  }
  if (T <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidTimeToMaturity);
  }

  const double d1 = calculate_d1(option); // Could potentially throw
  const double d2 = calculate_d2(option); // Could potentially throw

  if (option.getType() == OptionType::Call) {
    return S * std::exp(-q * T) * normal(d1) -
           K * std::exp(-r * T) * normal(d2);
  }
  return K * std::exp(-r * T) * normal(-d2) -
         S * std::exp(-q * T) * normal(-d1);
}

// Calculate the Delta of a European option
double BlackScholes::delta(const EuropeanOption &option) {
  const double S = option.getSpotPrice();
  const double r = option.getRiskFreeRate();
  const double q = option.getDividendYield();
  const double T = option.getMaturity();

  // Input validation using exceptions and fine-grained error messages
  if (S <= 0.0) {
    throw std::invalid_argument(ErrorMessages::BlackScholes::kInvalidSpotPrice);
  }
  if (r < 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidRiskFreeRate);
  }
  if (T <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidTimeToMaturity);
  }

  const double d1 = calculate_d1(option); // Could potentially throw

  if (option.getType() == OptionType::Call) {
    return std::exp(-q * T) * normal(d1);
  }
  return std::exp(-q * T) * (normal(d1) - 1);
}

// Calculate the Gamma of a European option
double BlackScholes::gamma(const EuropeanOption &option) {
  const double S = option.getSpotPrice();
  const double q = option.getDividendYield();
  const double T = option.getMaturity();
  const double sigma = option.getVolatilityImpl();

  // Input validation using exceptions and fine-grained error messages
  if (S <= 0.0) {
    throw std::invalid_argument(ErrorMessages::BlackScholes::kInvalidSpotPrice);
  }
  if (T <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidTimeToMaturity);
  }
  if (sigma <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidVolatility);
  }

  const double d1 = calculate_d1(option); // Could potentially throw
  constexpr double one_over_sqrt_two_pi = 0.39894228040143267793994605993438;

  return std::exp(-q * T) * one_over_sqrt_two_pi * std::exp(-d1 * d1 / 2.0) /
         (S * sigma * std::sqrt(T));
}

double BlackScholes::vega(const EuropeanOption &option) {
  const double S = option.getSpotPrice();
  const double q = option.getDividendYield();
  const double T = option.getMaturity();

  if (S <= 0.0) {
    throw std::invalid_argument(ErrorMessages::BlackScholes::kInvalidSpotPrice);
  }
  if (T <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidTimeToMaturity);
  }

  const double d1 = calculate_d1(option); // Could potentially throw
  constexpr double one_over_sqrt_two_pi = 0.39894228040143267793994605993438;

  return S * std::exp(-q * T) * std::sqrt(T) * one_over_sqrt_two_pi *
         std::exp(-d1 * d1 / 2.0);
}

double BlackScholes::theta(const EuropeanOption &option) {
  const double S = option.getSpotPrice();
  const double K = option.getStrikePrice();
  const double r = option.getRiskFreeRate();
  const double q = option.getDividendYield();
  const double T = option.getMaturity();
  const double sigma = option.getVolatilityImpl();

  if (S <= 0.0) {
    throw std::invalid_argument(ErrorMessages::BlackScholes::kInvalidSpotPrice);
  }
  if (K <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidStrikePrice);
  }
  if (r < 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidRiskFreeRate);
  }
  if (T <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidTimeToMaturity);
  }
  if (sigma <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidVolatility);
  }

  const double d1 = calculate_d1(option);
  const double d2 = calculate_d2(option);
  constexpr double one_over_sqrt_two_pi = 0.39894228040143267793994605993438;

  const double term1 = S * std::exp(-q * T) * one_over_sqrt_two_pi *
                       std::exp(-d1 * d1 / 2.0) * sigma / (2.0 * std::sqrt(T));
  const double term2 =
      r * K * std::exp(-r * T) *
      normal((option.getType() == OptionType::Call) ? d2 : -d2);
  const double term3 =
      q * S * std::exp(-q * T) *
      normal((option.getType() == OptionType::Call) ? d1 : -d1);

  if (option.getType() == OptionType::Call) {
    return -term1 - term2 + term3;
  }
  return -term1 + term2 - term3;
}

double BlackScholes::rho(const EuropeanOption &option) {
  const double K = option.getStrikePrice();
  const double r = option.getRiskFreeRate();
  const double T = option.getMaturity();

  if (K <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidStrikePrice);
  }
  if (r < 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidRiskFreeRate);
  }
  if (T <= 0.0) {
    throw std::invalid_argument(
        ErrorMessages::BlackScholes::kInvalidTimeToMaturity);
  }

  const double d2 = calculate_d2(option); // Could potentially throw

  if (option.getType() == OptionType::Call) {
    return K * T * std::exp(-r * T) * normal(d2);
  }
  return -K * T * std::exp(-r * T) * normal(-d2);
}