cmake_minimum_required(VERSION 3.24)
project(OptionsPricing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(benchmark REQUIRED)

include_directories(include)

add_library(OptionsPricingLib
        src/options/european_option.cpp
        src/options/american_option.cpp
        src/options/option.cpp
        src/pricing/black_scholes.cpp
        src/pricing/binomial_tree.cpp
        src/pricing/implied_vol.cpp
        src/utils/data_fetcher.cpp
        src/utils/data_parser.cpp
        src/utils/numerical_methods.cpp
)

add_executable(PricingBenchmarks benchmarks/pricing_benchmarks.cpp)
target_link_libraries(PricingBenchmarks OptionsPricingLib benchmark::benchmark)

add_subdirectory(tests)
