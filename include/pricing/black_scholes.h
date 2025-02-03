#ifndef BLACK_SCHOLES_H
#define BLACK_SCHOLES_H

#include "options/european_option.h"

class BlackScholes {
public:
  static double price(const EuropeanOption &option);
  static double delta(const EuropeanOption &option);
  static double gamma(const EuropeanOption &option);
  static double vega(const EuropeanOption &option);
  static double theta(const EuropeanOption &option);
  static double rho(const EuropeanOption &option);

private:
  static double calculate_d1(const EuropeanOption &option);
  static double calculate_d2(const EuropeanOption &option);

  // cdf of the standard normal distribution
  static double normal(const double &x);
};

#endif // BLACK_SCHOLES_H