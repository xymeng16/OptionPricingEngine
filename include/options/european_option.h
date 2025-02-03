#ifndef EUROPEAN_OPTION_H
#define EUROPEAN_OPTION_H

#include "option.h"

class EuropeanOption final : public Option<EuropeanOption> {
public:
  EuropeanOption(const double &spot_price, const double &strike_price,
                 const double &risk_free_rate, const double &time_to_maturity,
                 const double &sigma, const OptionType &type,
                 const double &dividend_yield = 0.0);

  ~EuropeanOption() override = default;

  void setVolatilityImpl(const double &sigma);

  [[nodiscard]] double getVolatilityImpl() const { return sigma_; }

  [[nodiscard]] double getSpotPriceImpl() const { return spot_price_; }

  [[nodiscard]] double getStrikePriceImpl() const { return strike_price_; }

  [[nodiscard]] double getRiskFreeRateImpl() const { return risk_free_rate_; }

  [[nodiscard]] double getMaturityImpl() const { return time_to_maturity_; }

  [[nodiscard]] OptionType getTypeImpl() const { return type_; }

  [[nodiscard]] double getDividendYieldImpl() const { return dividend_yield_; }

  [[nodiscard]] double payoffImpl(const double &underlying_price) const;

  [[nodiscard]] static bool isAmericanImpl() { return false; }
};

#endif // EUROPEAN_OPTION_H