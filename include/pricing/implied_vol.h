#ifndef IMPLIED_VOL_H
#define IMPLIED_VOL_H

#include "options/european_option.h"

class ImpliedVolatility {
public:
  // Calculate implied volatility using Newton-Raphson
  static double calculateImpliedVolatility(const EuropeanOption &option,
                                           const double &marketPrice,
                                           const double &tolerance = 1e-9,
                                           const int &maxIterations = 1000);
};

#endif // IMPLIED_VOL_H