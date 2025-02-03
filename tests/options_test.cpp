#include "options/american_option.h"
#include "options/european_option.h"
#include <gtest/gtest.h>

TEST(EuropeanOptionTest, Constructor) {
  EuropeanOption option(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Put);
  ASSERT_EQ(option.getSpotPrice(), 100.0);
  ASSERT_EQ(option.getStrikePrice(), 95.0);
  ASSERT_EQ(option.getRiskFreeRate(), 0.05);
  ASSERT_EQ(option.getMaturity(), 1.0);
  ASSERT_EQ(option.getVolatility(), 0.2);
  ASSERT_EQ(option.getType(), OptionType::Put);
}

TEST(AmericanOptionTest, Constructor) {
  AmericanOption option(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Put);
  ASSERT_EQ(option.getSpotPrice(), 100.0);
  ASSERT_EQ(option.getStrikePrice(), 95.0);
  ASSERT_EQ(option.getRiskFreeRate(), 0.05);
  ASSERT_EQ(option.getMaturity(), 1.0);
  ASSERT_EQ(option.getVolatility(), 0.2);
  ASSERT_EQ(option.getType(), OptionType::Put);
}

TEST(EuropeanOptionTest, OptionType) {
  EuropeanOption call(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Call);
  EuropeanOption put(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Put);
  ASSERT_EQ(call.getType(), OptionType::Call);
  ASSERT_EQ(put.getType(), OptionType::Put);
}

TEST(AmericanOptionTest, OptionType) {
  AmericanOption call(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Call);
  AmericanOption put(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Put);
  ASSERT_EQ(call.getType(), OptionType::Call);
  ASSERT_EQ(put.getType(), OptionType::Put);
}

TEST(EuropeanOptionTest, SetVolatility) {
  EuropeanOption option(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Put);
  option.setVolatilityImpl(0.3);
  ASSERT_EQ(option.getVolatilityImpl(), 0.3);
}

TEST(AmericanOptionTest, SetSpotPrice) {
  AmericanOption option(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Put);
  option.setSpotPrice(105.0);
  ASSERT_EQ(option.getSpotPrice(), 105.0);
}

TEST(AmericanOptionTest, SetMaturity) {
  AmericanOption option(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Put);
  option.setMaturity(0.5);
  ASSERT_EQ(option.getMaturity(), 0.5);
}

TEST(EuropeanOptionTest, IsAmerican) {
  EuropeanOption option(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Put);
  ASSERT_FALSE(option.isAmerican());
}

TEST(AmericanOptionTest, IsAmerican) {
  AmericanOption option(100.0, 95.0, 0.05, 1.0, 0.2, OptionType::Put);
  ASSERT_TRUE(option.isAmerican());
}