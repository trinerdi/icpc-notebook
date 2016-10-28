#include "gtest/gtest.h"
#include "fft.cpp"

TEST(FFT, Multiplies) {
    vector<ll> p1 = {8, 2, 1, 6, 3};
    vector<ll> p2 = {3, 4, 2};
    vector<ll> res = multiplyPolynomials(p1, p2);
    EXPECT_EQ((vector<ll> {24, 38, 27, 26, 35, 24, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0}), res);
}

TEST(FFT, MultipliesMillions) {
    vector<ll> p1 = {289383, 930886, 692777, 636915};
    vector<ll> p2 = {747793, 238335, 885386, 760492};
    vector<ll> res = multiplyPolynomials(p1, p2);
    EXPECT_EQ((vector<ll> {216398581719, 765080131903, 996132162809, 1685660473322,
                           1473105549359, 1090766990474, 484368762180, 0
                          }), res);
}

TEST(FFT, MultipliesBillions) {
    vector<ll> p1 = {1804289383, 846930886, 1681692777, 1714636915};
    vector<ll> p2 = {1957747793, 424238335, 719885386, 1649760492};
    vector<ll> res = multiplyPolynomials(p1, p2);
    EXPECT_EQ((vector<ll> {3532343557501581719, 2423525796592131903, 4950512430549162809, 7656603687825473322,
                           3335273879030549359, 4008732360580990474, 2828740240491762180, 0
                          }), res);
}

TEST(FFT, MultipliesNegative) {
    vector<ll> p1 = {3, 1, -2, 2};
    vector<ll> p2 = { -5, 1};
    vector<ll> res = multiplyPolynomials(p1, p2);
    EXPECT_EQ((vector<ll> { -15, -2, 11, -12, 2, 0, 0, 0}), res);
}

TEST(FFT, MultipliesOneEmpty) {
    vector<ll> p1 = {3, 1, 2};
    vector<ll> p2 = {};
    vector<ll> res = multiplyPolynomials(p1, p2);
    EXPECT_EQ((vector<ll> {0, 0, 0, 0, 0, 0, 0, 0}), res);
}

TEST(FFT, MultipliesBothEmpty) {
    vector<ll> p1 = {};
    vector<ll> p2 = {};
    vector<ll> res = multiplyPolynomials(p1, p2);
    EXPECT_EQ((vector<ll> {0, 0}), res);
}
