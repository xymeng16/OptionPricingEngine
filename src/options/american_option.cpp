#include "options/american_option.h"
#include <cmath>

AmericanOption::AmericanOption(const double &spot_price,
                               const double &strike_price,
                               const double &risk_free_rate,
                               const double &time_to_maturity,
                               const double &sigma, const OptionType &type,
                               const double &dividend_yield)
    : Option<AmericanOption>(spot_price, strike_price, risk_free_rate,
                             time_to_maturity, sigma, type, dividend_yield) {}

double AmericanOption::payoffImpl(const double &underlying_price) const {
  if (type_ == OptionType::Call) {
    return std::max(0.0, underlying_price - strike_price_);
  }
  return std::max(0.0, strike_price_ - underlying_price);
}