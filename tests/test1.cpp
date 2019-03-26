//
// The MIT License (MIT)
// 
// Copyright (C) 2015 Michael Tesch tesch1 a gmail com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
#include "gtest/gtest.h"
#include <iostream>
#include <limits>
#include <cxxduals/dual>
#include <complex>

#include "test_helpers.h"

template <typename DUALTYPE>
void construct()
{
  typedef typename DUALTYPE::value_type Value;

  DUALTYPE x = (Value)1.1;
  EXPECT_EQ(x.rpart(), (Value)1.1);
  EXPECT_EQ(rpart(x), (Value)1.1);
  EXPECT_EQ(x.epart(), (Value)0.0);
  EXPECT_EQ(epart(x), (Value)0.0);

  DUALTYPE z(1.1);
  EXPECT_EQ(z.rpart(), (Value)1.1);
  EXPECT_EQ(rpart(z), (Value)1.1);
  EXPECT_EQ(z.epart(), (Value)0.0);
  EXPECT_EQ(epart(z), (Value)0.0);

  DUALTYPE y(1.1, 2.2);
  EXPECT_EQ(y.rpart(), (Value)1.1);
  EXPECT_EQ(rpart(y), (Value)1.1);
  EXPECT_EQ(y.epart(), (Value)2.2);
  EXPECT_EQ(epart(y), (Value)2.2);

  DUALTYPE w(1.1, 2.2);
  EXPECT_EQ(w.rpart(), (Value)1.1);
  EXPECT_EQ(w.epart(), (Value)2.2);

  DUALTYPE a{1.1, 2.2};
  EXPECT_EQ(a.rpart(), (Value)1.1);
  EXPECT_EQ(a.part(0), (Value)1.1);
  EXPECT_EQ(a.part(1), (Value)2.2);
}

template <typename DUALTYPE>
void equality()
{
  typedef typename DUALTYPE::value_type Value;
  DUALTYPE d{1.1, 2.2};
  DUALTYPE e{1.1, 2.2};
  DUALTYPE f{1.1, 2.21};
  DUALTYPE g{2.2, 2.21};
  DUALTYPE h{-2.2, -2.21};
  DUALTYPE j{3, 1};
  DUALTYPE k{9, 6};
  DUALTYPE l{9, 1};
  EXPECT_EQ(e, d);
  EXPECT_EQ(e, f);
  EXPECT_NE(f, g);
  EXPECT_NE(f, h);
  EXPECT_NE(f, (Value)1.2);
  EXPECT_NE((Value)1.2, f);
  EXPECT_EQ(j*j, k);
  DUALTYPE res{9.,6.};
  DU_EXPECT_NEAR(pow(j,(Value)2.0), res);
  DUALTYPE res2{3., (Value)(0.5*pow(9,-0.5))};
  DU_EXPECT_NEAR(sqrt(l), res2 );
}

template <typename DUALTYPE>
void compare()
{
  typedef typename DUALTYPE::value_type Value;
  DUALTYPE d{1.1, 2.2};
  DUALTYPE e{1.1, 2.2};
  DUALTYPE f{1.1, 2.21};
  DUALTYPE g{2.2, 2.21};
  DUALTYPE h{-2.2, -2.21};
  DUALTYPE j{3, 1};
  DUALTYPE k{9, 6};
  DUALTYPE l{9, 1};
  MY_EXPECT_NEAR(epart(sqrt(l)), (Value)(0.5*pow(9,-0.5)));
  MY_EXPECT_NEAR(epart(pow(j,(Value)2.0)), (Value)6.0);
  EXPECT_GT((Value)1.2, d);
  EXPECT_GT(d,(Value)1.0);
  EXPECT_GT(g,f);
  EXPECT_LT((Value)1.0, d);
  EXPECT_LT(d,(Value)1.2);
  EXPECT_LT(f,g);
  EXPECT_LE(d,(Value)1.1);
  EXPECT_LE((Value)1.1,d);
  EXPECT_LE(f,g);
  EXPECT_LE(f,e);
  EXPECT_GE(d,(Value)1.1);
  EXPECT_GE((Value)1.1,d);
  EXPECT_GE(g,f);
  EXPECT_GE(e,f);
  EXPECT_EQ(abs(h), g);
  EXPECT_EQ(abs(-h), g);
  EXPECT_EQ(-abs(h), h);
  EXPECT_EQ(abs(h), (Value)2.2);
  EXPECT_EQ(+abs(h), (Value)2.2);
  EXPECT_EQ(-abs(h), (Value)-2.2);
  EXPECT_TRUE(max(f,(Value)2.2) == (Value)2.2);
  EXPECT_TRUE(max((Value)2.2,f) == (Value)2.2);
  EXPECT_TRUE(min(f,(Value)2.2) == f);
  EXPECT_TRUE(min((Value)2.2,f) == f);
  EXPECT_TRUE(max(f,g) == g);
  EXPECT_TRUE(max(g,f) == g);
  EXPECT_TRUE(min(f,g) == f);
  EXPECT_TRUE(min(g,f) == f);
}

template <typename DUALTYPE>
void arithmetic()
{
  typedef typename DUALTYPE::value_type Value;
  DUALTYPE a, b;
  a = (Value)1;
  b = (Value)2;
  b = a;
  a = b;
  b = a;
  a = b + (Value)1.0; // 2
  //a = b + 1.0; // 2
  a = (Value)1.0 + b; // 2
  a = a + a; // 4
  a = a + b; // 5
  EXPECT_EQ(a, (Value)5);
  // +
  // -
  // *
  // /
}

template <typename DUALTYPE>
void numeric_limits()
{
#ifndef CXXDUALS_NO_LIMITS
  typedef typename DUALTYPE::value_type Value;

  EXPECT_EQ(std::numeric_limits<Value>::min(), std::numeric_limits<DUALTYPE>::min());
  EXPECT_EQ(std::numeric_limits<Value>::max(), std::numeric_limits<DUALTYPE>::max());
  EXPECT_EQ(std::numeric_limits<Value>::epsilon(), std::numeric_limits<DUALTYPE>::epsilon());
  EXPECT_EQ(std::numeric_limits<Value>::round_error(), std::numeric_limits<DUALTYPE>::round_error());
  EXPECT_EQ(std::numeric_limits<Value>::infinity(), std::numeric_limits<DUALTYPE>::infinity());
  //EXPECT_EQ(std::numeric_limits<Value>::quiet_NaN(), std::numeric_limits<DUALTYPE>::min());
  //EXPECT_EQ(std::numeric_limits<Value>::signaling_NaN(), std::numeric_limits<DUALTYPE>::min());
  EXPECT_EQ(std::numeric_limits<Value>::denorm_min(), std::numeric_limits<DUALTYPE>::denorm_min());
#endif
}

using std::isnormal;
template <typename T> bool isnormal(const std::complex<T> & v)
{
  return isnormal(real(v));
}

template <typename DUALTYPE>
void transcendental()
{
  typedef typename DUALTYPE::value_type Value;

  for (int ii = -10; ii < 10; ii++) {
    double S = ii / 5.0;
    Value x = ii / 5.0;
    DUALTYPE xx(ii / 5.0, 1);
    using std::pow;
    // pow
    DUALTYPE res(pow(x,4), Value(4.) * (Value)pow(x,3));
    DU_EXPECT_NEAR(pow(xx,4), res);
    res = DUALTYPE(pow(3,x), pow((Value)3,x)*log((Value)3));
    DU_EXPECT_NEAR(pow((Value)3.,xx), res);
    //std::cerr << "x=" << x << " x^2 = " << pow(x,2) << "\n";
    //Value y =  pow(x,pow(x,2));
    //std::cerr << "x=" << x << " x^x^2 = " << y << "\n";
    //std::cerr << "xx=" << xx << "\n";
    res = DUALTYPE(pow(x,(Value)pow(x,2)),
                   pow(x,(Value)pow(x,2) - (Value)1) * (Value)pow(x, 2) +
                   (Value)2 * x * (Value)pow(x,pow(x,2)) * log(x));
    //std::cerr << "res=" << res << "\n";
    if (cxxduals::is_complex<Value>::value ? S != 0. : S > 0.) {
      DU_EXPECT_NEAR(pow(xx,pow(xx,2)), res);
    }
    else
      EXPECT_FALSE(isnormal(res.epart()));
    // sqrt
    // log
    // exp
    DUALTYPE B(0, ii);
    EXPECT_EQ(B.rpart(), (Value)0);
    EXPECT_EQ(B.epart(), (Value)ii);
    EXPECT_EQ(rpart(exp(B)), (Value)1);
    EXPECT_EQ(epart(exp(B)), (Value)ii);
    // sin
    // cos
    // tan
    // asin
    // acos
    // atan
    // atan2
  }
}

#ifndef __CUDACC__
void takes_dualcd(dualcd blah)
{
  
}

void takes_dualcd_ref(dualcd & blah)
{
  
}
#endif

template <typename TYPE1, typename TYPE2>
void casting()
{
  dual<TYPE1> a;
  dual<TYPE2> b;
  const dual<TYPE2> cc(1);

  a = dual<TYPE1>{1,2};
  b = 1;
  b = 1.0f;
  b = 1.0;
  b = (TYPE2)1.0;
  b = cc + 1;
  b = 1.0 + cc;
  b = cc - 1.0;
  b = 1.0 - cc;
  b = cc * 1.0;
  b = 1.0 * cc;
  b = cc / 1.0;
  b = 1.0 / cc;
  a = cc / 1.0;
  a = 1.0 / cc;

  dual<TYPE1> c(b);
  dual<TYPE1> d = dual<TYPE1>(b);

  c = d;
  d = c;

  c += d;
  d += c;
  c -= d;
  d -= c;
  c *= d;
  d *= c;
  c /= d;
  d /= c;

  // illegal
  //dual<TYPE1> e = b;
  //dual<TYPE2> f = a;
}

#ifndef __CUDACC__
TEST (generic, generic)
{
  dualcd a;
  dualcf b;
  takes_dualcd_ref(a);
  //takes_dualcd(b);
  takes_dualcd(dualcd(b));
  //takes_dualcd_ref(dualcd(b));
}
#endif

// basics
TESTALL(construct)
TESTALL(equality)
TESTREAL(compare)
TESTALL(arithmetic)
TESTALL(numeric_limits)
TESTALL(transcendental)

TEST(basic, construction) {
  typedef std::complex<duald> cduald;
  typedef std::complex<dualf> cdualf;

  dualf a;
  dualf b(1);
  dualf c(1,2);
  dualf c1{1,2};

  dualcf d;
  dualcf e({1,2});
  dualcf e1{1,2};
  dualcf f({1,2}, {3,4});

  hyperdualf g;
  hyperdualf h(1);
  hyperdualf i(1,2);

  hyperdualcf j;
  hyperdualcf k(1);
  hyperdualcf l(1,2);

  std::complex<dual<double>> m;
  
  d = a;

  // verify some properties
  rand(a);
  rand(d);
  rand(e);
  std::complex<double> cd(3.5, 4.25);
  std::complex<float> cf(3.5, 4.25);
  cf = cd;
  cd = cf;
  EXPECT_EQ(cd*=2, std::complex<double>(7,8.5));
  EXPECT_EQ(cf*=2, std::complex<float>(7,8.5));
  EXPECT_EQ(conj(conj(d)), d);
  EXPECT_EQ(conj(d + e), conj(d) + conj(e));
  EXPECT_EQ(conj(d * e), conj(d) * conj(e));
  EXPECT_EQ(a, abs(a) * exp(dualf(0,1) * arg(a)));
  //EXPECT_EQ(d, abs(d) * exp(dualcf(0,1) * arg(d)));
  //EXPECT_EQ(conj(cf * d), conj(cf) * conj(d));
  //EXPECT_EQ(abs(conj(d)*d), abs(d) * abs(conj(d)));

  EXPECT_TRUE(cxxduals::is_dual<dualf>::value);
  EXPECT_TRUE(cxxduals::is_dual<duald>::value);
  EXPECT_TRUE(cxxduals::is_dual<dualcf>::value);
  EXPECT_TRUE(cxxduals::is_dual<dualcd>::value);
  EXPECT_FALSE(cxxduals::is_dual<float>::value);
  EXPECT_FALSE(cxxduals::is_dual<double>::value);
  EXPECT_FALSE(cxxduals::is_dual<cduald>::value);
  EXPECT_FALSE(cxxduals::is_dual<cduald>::value);

  EXPECT_TRUE(cxxduals::internal::is_arithmetic<float>::value);
  EXPECT_TRUE(cxxduals::internal::is_arithmetic<double>::value);
  EXPECT_TRUE(cxxduals::internal::is_arithmetic<complexf>::value);
  EXPECT_TRUE(cxxduals::internal::is_arithmetic<complexd>::value);
  EXPECT_TRUE(cxxduals::internal::is_arithmetic<cdualf>::value);
  EXPECT_TRUE(cxxduals::internal::is_arithmetic<cduald>::value);
  EXPECT_TRUE(cxxduals::is_complex<complexf>::value);
  EXPECT_TRUE(cxxduals::is_complex<complexd>::value);
  EXPECT_TRUE(cxxduals::is_complex<cdualf>::value);
  EXPECT_TRUE(cxxduals::is_complex<cduald>::value);
}

// simple types
TEST_TYPEMIX(casting, float, float)
TEST_TYPEMIX(casting, float, double)
TEST_TYPEMIX(casting, float, longdouble)
TEST_TYPEMIX(casting, double, float)
TEST_TYPEMIX(casting, double, double)
TEST_TYPEMIX(casting, double, longdouble)
TEST_TYPEMIX(casting, longdouble, float)
TEST_TYPEMIX(casting, longdouble, double)
TEST_TYPEMIX(casting, longdouble, longdouble)

// lhs is complex, casts to it
#ifndef __CUDACC__
TYPEMIX6(complexf, casting)
TYPEMIX6(complexd, casting)
TYPEMIX6(complexld, casting)
TYPEMIX6(dualcf, casting)
TYPEMIX6(dualcd, casting)
TYPEMIX6(dualcld, casting)
TYPEMIX6(hyperdualcf, casting)
TYPEMIX6(hyperdualcd, casting)
TYPEMIX6(hyperdualcld, casting)
#endif

// lhs is dual<real> and dual<complex> - ie, hyperdual

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout.precision(20);
  std::cerr.precision(20);
  return RUN_ALL_TESTS();
}
