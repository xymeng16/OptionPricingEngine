#ifndef OPTION_H
#define OPTION_H

#include <common.h>

enum class OptionType { Call, Put };

template <typename Derived> class Option {
public:
  Option(const double &spot_price, const double &strike_price,
         const double &risk_free_rate, const double &time_to_maturity,
         const double &sigma, const OptionType &type,
         const double &dividend_yield = 0.0)
      : spot_price_(spot_price), strike_price_(strike_price),
        risk_free_rate_(risk_free_rate), time_to_maturity_(time_to_maturity),
        sigma_(sigma), type_(type), dividend_yield_(dividend_yield) {}

  virtual ~Option() = default;

  [[nodiscard]] double getVolatility() const {
    return static_cast<const Derived *>(this)->getVolatilityImpl();
  }

  [[nodiscard]] double getSpotPrice() const {
    return static_cast<const Derived *>(this)->getSpotPriceImpl();
  }

  [[nodiscard]] double getStrikePrice() const {
    return static_cast<const Derived *>(this)->getStrikePriceImpl();
  }

  [[nodiscard]] double getRiskFreeRate() const {
    return static_cast<const Derived *>(this)->getRiskFreeRateImpl();
  }

  [[nodiscard]] double getMaturity() const {
    return static_cast<const Derived *>(this)->getMaturityImpl();
  }

  [[nodiscard]] OptionType getType() const {
    return static_cast<const Derived *>(this)->getTypeImpl();
  }

  [[nodiscard]] double getDividendYield() const {
    return static_cast<const Derived *>(this)->getDividendYieldImpl();
  }

  [[nodiscard]] double payoff(double underlying_price) const {
    return static_cast<const Derived *>(this)->payoffImpl(underlying_price);
  }

  [[nodiscard]] bool isAmerican() const {
    return static_cast<const Derived *>(this)->isAmericanImpl();
  }

protected:
  double spot_price_;
  double strike_price_;
  double risk_free_rate_;
  double time_to_maturity_;
  double sigma_;
  OptionType type_;
  double dividend_yield_;

private:
  // for compile-time polymorphism (lite version of CRTP)
  friend Derived;
};

#endif // OPTION_H