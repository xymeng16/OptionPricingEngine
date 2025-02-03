#ifndef AMERICAN_OPTION_H
#define AMERICAN_OPTION_H

#include "option.h"

class AmericanOption final : public Option<AmericanOption> {
public:
  AmericanOption(const double &spot_price, const double &strike_price,
                 const double &risk_free_rate, const double &time_to_maturity,
                 const double &sigma, const OptionType &type,
                 const double &dividend_yield = 0.0);

  ~AmericanOption() override = default;

  void setVolatility(const double &sigma) { sigma_ = sigma; }

  void setSpotPrice(const double &spot_price) { spot_price_ = spot_price; }

  void setMaturity(const double &time_to_maturity) {
    time_to_maturity_ = time_to_maturity;
  }

  [[nodiscard]] double getVolatilityImpl() const { return sigma_; }

  [[nodiscard]] double getSpotPriceImpl() const { return spot_price_; }

  [[nodiscard]] double getStrikePriceImpl() const { return strike_price_; }

  [[nodiscard]] double getRiskFreeRateImpl() const { return risk_free_rate_; }

  [[nodiscard]] double getMaturityImpl() const { return time_to_maturity_; }

  [[nodiscard]] OptionType getTypeImpl() const { return type_; }

  [[nodiscard]] double getDividendYieldImpl() const { return dividend_yield_; }

  [[nodiscard]] double payoffImpl(const double &underlying_price) const;

  static bool isAmericanImpl() { return true; }
};

#endif // AMERICAN_OPTION_H