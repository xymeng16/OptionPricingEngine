#include "pricing/binomial_tree.h"
#include "error_messages.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

double BinomialTree::price(const AmericanOption &option, const int &numSteps) {
  if (numSteps <= 0) {
    throw std::invalid_argument(ErrorMessages::BinomialTree::kInvalidNumSteps);
  }

  const double S = option.getSpotPrice();
  const double r = option.getRiskFreeRate();
  const double q = option.getDividendYield();
  const double T = option.getMaturity();
  const double sigma = option.getVolatility();

  const double dt = T / numSteps;
  const double u = std::exp(sigma * std::sqrt(dt));
  const double d = 1.0 / u;
  const double p = (std::exp((r - q) * dt) - d) / (u - d);

  std::vector<std::vector<double>> stockPrices(
      numSteps + 1, std::vector<double>(numSteps + 1, 0.0));
  for (int i = 0; i <= numSteps; ++i) {
    for (int j = 0; j <= i; ++j) {
      stockPrices[i][j] = S * std::pow(u, j) * std::pow(d, i - j);
    }
  }

  std::vector<double> optionValues(numSteps + 1);
  for (int j = 0; j <= numSteps; ++j) {
    optionValues[j] = option.payoffImpl(stockPrices[numSteps][j]);
  }

  // Backward induction
  for (int i = numSteps - 1; i >= 0; --i) {
    for (int j = 0; j <= i; ++j) {
      double continuationValue =
          std::exp(-r * dt) *
          (p * optionValues[j + 1] + (1 - p) * optionValues[j]);
      if (option.isAmerican()) {
        // early exercise
        optionValues[j] =
            std::max(continuationValue, option.payoffImpl(stockPrices[i][j]));
      } else {
        optionValues[j] = continuationValue;
      }
    }
  }

  return optionValues[0];
}

double BinomialTree::delta(const AmericanOption &option, const int &numSteps) {
  const double S = option.getSpotPrice();
  const double deltaS = 0.01 * S;

  AmericanOption optionPlus = option;
  optionPlus.setSpotPrice(S + deltaS);
  const double pricePlus = price(optionPlus, numSteps);

  AmericanOption optionMinus = option;
  optionMinus.setSpotPrice(S - deltaS);
  const double priceMinus = price(optionMinus, numSteps);

  return (pricePlus - priceMinus) / (2 * deltaS);
}

double BinomialTree::gamma(const AmericanOption &option, const int &numSteps) {
  // Calculate option prices with slightly higher and lower spot prices
  const double S = option.getSpotPrice();
  const double deltaS = 0.01 * S;

  AmericanOption optionPlus = option;
  optionPlus.setSpotPrice(S + deltaS);

  AmericanOption optionMinus = option;
  optionMinus.setSpotPrice(S - deltaS);

  return (delta(optionPlus, numSteps) - delta(optionMinus, numSteps)) /
         (2 * deltaS);
}

double BinomialTree::theta(const AmericanOption &option, const int &numSteps) {
  // Calculate option prices with slightly shorter and longer times to maturity
  const double &T = option.getMaturity();
  const double &deltaT =
      0.01; // Small change in time to maturity (e.g., 1/100 of a year)

  AmericanOption optionPlus = option;
  optionPlus.setMaturity(std::max(0.0, T - deltaT));

  AmericanOption optionMinus = option;
  optionMinus.setMaturity(T + deltaT);

  return (price(optionPlus, numSteps) - price(optionMinus, numSteps)) /
         (2 * deltaT);
}

double BinomialTree::calculateOptionValue(const double &underlyingPrice,
                                          const AmericanOption &option) {
  return option.payoffImpl(underlyingPrice);
}