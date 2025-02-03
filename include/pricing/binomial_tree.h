#ifndef BINOMIAL_TREE_H
#define BINOMIAL_TREE_H

#include "options/american_option.h"

class BinomialTree {
public:
  static double price(const AmericanOption &option, const int &numSteps);

  static double delta(const AmericanOption &option, const int &numSteps);

  static double gamma(const AmericanOption &option, const int &numSteps);

  static double theta(const AmericanOption &option, const int &numSteps);

private:
  static double calculateOptionValue(const double &underlyingPrice,
                                     const AmericanOption &option);
};

#endif // BINOMIAL_TREE_H