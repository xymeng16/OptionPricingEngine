include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/e235eb34c6c4fed790ccdad4b16394301360dcd4.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(OptionsTest options_test.cpp)
add_executable(PricingTest pricing_test.cpp)
add_executable(UtilsTest utils_test.cpp)

target_link_libraries(OptionsTest GTest::gtest_main OptionsPricingLib)
target_link_libraries(PricingTest GTest::gtest_main OptionsPricingLib)
target_link_libraries(UtilsTest GTest::gtest_main OptionsPricingLib)

include(GoogleTest)
gtest_discover_tests(OptionsTest)
gtest_discover_tests(PricingTest)
gtest_discover_tests(UtilsTest)