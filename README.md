## Simple Option Pricing Engine

This is a simple option pricing engine in C++. It implements the Black-Scholes and Binomial tree models to price
American and European options. This is a hobby and educational project and is not intended for production use. Further
optimizations and
improvements on the performance, verification and validation of the correctness of the model implementation are needed.

### Features

- Black-Scholes model for European options
- Binomial tree model for American/European options
- Implied volatility calculation
- Greeks calculation (Delta, Gamma, Theta, Vega, Rho)
- Compile-time polymorphism using CRTP to allow for different option types
- Unit tests using Google Test
- Benchmarking using Google Benchmark

### TODOs

- Using CUDA for GPU acceleration of the pricing models
- Add more option pricing models
- Implement a PDE solver for pricing options
- Implement different numerical methods
- Benchmark STL math functions and Boost's math library

### Run

#### Requirements

CMake 3.24.0 or later, Compiler with C++17 support, Google Test, Google Benchmark

```shell
$ git clone https://github.com/xymeng16/OptionPricingEngine.git
$ cd OptionPricingEngine && mkdir build && cd build
$ cmake .. && make
# run the tests or benchmarks in the build directory
```

### License

MIT License