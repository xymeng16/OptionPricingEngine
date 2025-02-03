#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

namespace ErrorMessages {

  namespace BlackScholes {
    constexpr auto kInvalidSpotPrice = "Spot price must be positive.";
    constexpr auto kInvalidStrikePrice = "Strike price must be positive.";
    constexpr auto kInvalidRiskFreeRate =
        "Risk-free rate must be non-negative.";
    constexpr auto kInvalidTimeToMaturity =
        "Time to maturity must be positive.";
    constexpr auto kInvalidVolatility = "Volatility must be positive.";
  } // namespace BlackScholes

  namespace BinomialTree {
    constexpr auto kInvalidNumSteps = "Number of steps must be positive.";
  }

  namespace ImpliedVol {
    constexpr auto kInvalidMarketPrice = "Market price must be positive.";
  }

} // namespace ErrorMessages

#endif // ERROR_MESSAGES_H