#include "options/american_option.h"
#include "options/european_option.h"
#include "pricing/binomial_tree.h"
#include "pricing/black_scholes.h"
#include <benchmark/benchmark.h>

static void BM_BlackScholesPrice_Call(benchmark::State &state) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  for (auto _ : state) {
    double price = BlackScholes::price(option);
    benchmark::DoNotOptimize(price);
  }
}
BENCHMARK(BM_BlackScholesPrice_Call);

static void BM_BlackScholesPrice_Put(benchmark::State &state) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  for (auto _ : state) {
    double price = BlackScholes::price(option);
    benchmark::DoNotOptimize(price);
  }
}
BENCHMARK(BM_BlackScholesPrice_Put);

static void BM_BlackScholesDelta_Call(benchmark::State &state) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  for (auto _ : state) {
    double delta = BlackScholes::delta(option);
    benchmark::DoNotOptimize(delta);
  }
}
BENCHMARK(BM_BlackScholesDelta_Call);

static void BM_BlackScholesDelta_Put(benchmark::State &state) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  for (auto _ : state) {
    double delta = BlackScholes::delta(option);
    benchmark::DoNotOptimize(delta);
  }
}
BENCHMARK(BM_BlackScholesDelta_Put);

static void BM_BlackScholesGamma(benchmark::State &state) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  for (auto _ : state) {
    double gamma = BlackScholes::gamma(option);
    benchmark::DoNotOptimize(gamma);
  }
}
BENCHMARK(BM_BlackScholesGamma);

static void BM_BlackScholesVega(benchmark::State &state) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  for (auto _ : state) {
    double vega = BlackScholes::vega(option);
    benchmark::DoNotOptimize(vega);
  }
}
BENCHMARK(BM_BlackScholesVega);

static void BM_BlackScholesTheta_Call(benchmark::State &state) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  for (auto _ : state) {
    double theta = BlackScholes::theta(option);
    benchmark::DoNotOptimize(theta);
  }
}
BENCHMARK(BM_BlackScholesTheta_Call);

static void BM_BlackScholesTheta_Put(benchmark::State &state) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  for (auto _ : state) {
    double theta = BlackScholes::theta(option);
    benchmark::DoNotOptimize(theta);
  }
}
BENCHMARK(BM_BlackScholesTheta_Put);

static void BM_BlackScholesRho_Call(benchmark::State &state) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  for (auto _ : state) {
    double rho = BlackScholes::rho(option);
    benchmark::DoNotOptimize(rho);
  }
}
BENCHMARK(BM_BlackScholesRho_Call);

static void BM_BlackScholesRho_Put(benchmark::State &state) {
  const EuropeanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Put);
  for (auto _ : state) {
    double rho = BlackScholes::rho(option);
    benchmark::DoNotOptimize(rho);
  }
}
BENCHMARK(BM_BlackScholesRho_Put);

static void BM_BinomialTreePrice(benchmark::State &state) {
  const AmericanOption option(100.0, 100.0, 0.05, 1.0, 0.2, OptionType::Call);
  const int &numSteps = state.range(0);
  for (auto _ : state) {
    double price = BinomialTree::price(option, numSteps);
    benchmark::DoNotOptimize(price);
  }
}
BENCHMARK(BM_BinomialTreePrice)->RangeMultiplier(2)->Range(16, 8192);

BENCHMARK_MAIN();