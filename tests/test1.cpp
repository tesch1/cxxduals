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
  typedef typename DUALTYPE::value_type Scalar;

  DUALTYPE x = (Scalar)1.1;
  EXPECT_EQ(x.rpart(), (Scalar)1.1);
  EXPECT_EQ(rpart(x), (Scalar)1.1);
  EXPECT_EQ(x.epart(), (Scalar)0.0);
  EXPECT_EQ(epart(x), (Scalar)0.0);

  DUALTYPE z(1.1);
  EXPECT_EQ(z.rpart(), (Scalar)1.1);
  EXPECT_EQ(rpart(z), (Scalar)1.1);
  EXPECT_EQ(z.epart(), (Scalar)0.0);
  EXPECT_EQ(epart(z), (Scalar)0.0);

  DUALTYPE y(1.1, 2.2);
  EXPECT_EQ(y.rpart(), (Scalar)1.1);
  EXPECT_EQ(rpart(y), (Scalar)1.1);
  EXPECT_EQ(y.epart(), (Scalar)2.2);
  EXPECT_EQ(epart(y), (Scalar)2.2);

  DUALTYPE w(1.1, 2.2);
  EXPECT_EQ(w.rpart(), (Scalar)1.1);
  EXPECT_EQ(w.epart(), (Scalar)2.2);

  DUALTYPE a{1.1, 2.2};
  EXPECT_EQ(a.rpart(), (Scalar)1.1);
  EXPECT_EQ(a.part(0), (Scalar)1.1);
  EXPECT_EQ(a.part(1), (Scalar)2.2);
}

template <typename DUALTYPE>
void equality()
{
  typedef typename DUALTYPE::value_type Scalar;
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
  EXPECT_NE(f, (Scalar)1.2);
  EXPECT_NE((Scalar)1.2, f);
  EXPECT_EQ(j*j, k);
  DUALTYPE res{9.,6.};
  DU_EXPECT_NEAR(pow(j,(Scalar)2.0), res);
  DUALTYPE res2{3., (Scalar)(0.5*pow(9,-0.5))};
  DU_EXPECT_NEAR(sqrt(l), res2 );
}

template <typename DUALTYPE>
void compare()
{
  typedef typename DUALTYPE::value_type Scalar;
  DUALTYPE d{1.1, 2.2};
  DUALTYPE e{1.1, 2.2};
  DUALTYPE f{1.1, 2.21};
  DUALTYPE g{2.2, 2.21};
  DUALTYPE h{-2.2, -2.21};
  DUALTYPE j{3, 1};
  DUALTYPE k{9, 6};
  DUALTYPE l{9, 1};
  MY_EXPECT_NEAR(epart(sqrt(l)), (Scalar)(0.5*pow(9,-0.5)));
  MY_EXPECT_NEAR(epart(pow(j,(Scalar)2.0)), (Scalar)6.0);
  EXPECT_GT((Scalar)1.2, d);
  EXPECT_GT(d,(Scalar)1.0);
  EXPECT_GT(g,f);
  EXPECT_LT((Scalar)1.0, d);
  EXPECT_LT(d,(Scalar)1.2);
  EXPECT_LT(f,g);
  EXPECT_LE(d,(Scalar)1.1);
  EXPECT_LE((Scalar)1.1,d);
  EXPECT_LE(f,g);
  EXPECT_LE(f,e);
  EXPECT_GE(d,(Scalar)1.1);
  EXPECT_GE((Scalar)1.1,d);
  EXPECT_GE(g,f);
  EXPECT_GE(e,f);
  EXPECT_EQ(abs(h), g);
  EXPECT_EQ(abs(-h), g);
  EXPECT_EQ(-abs(h), h);
  EXPECT_EQ(abs(h), (Scalar)2.2);
  EXPECT_EQ(+abs(h), (Scalar)2.2);
  EXPECT_EQ(-abs(h), (Scalar)-2.2);
  EXPECT_TRUE(max(f,(Scalar)2.2) == (Scalar)2.2);
  EXPECT_TRUE(max((Scalar)2.2,f) == (Scalar)2.2);
  EXPECT_TRUE(min(f,(Scalar)2.2) == f);
  EXPECT_TRUE(min((Scalar)2.2,f) == f);
  EXPECT_TRUE(max(f,g) == g);
  EXPECT_TRUE(max(g,f) == g);
  EXPECT_TRUE(min(f,g) == f);
  EXPECT_TRUE(min(g,f) == f);
}

template <typename DUALTYPE>
void arithmetic()
{
  typedef typename DUALTYPE::value_type Scalar;
  DUALTYPE a, b;
  a = (Scalar)1;
  b = (Scalar)2;
  b = a;
  a = b;
  b = a;
  a = b + (Scalar)1.0; // 2
  //a = b + 1.0; // 2
  a = (Scalar)1.0 + b; // 2
  a = a + a; // 4
  a = a + b; // 5
  EXPECT_EQ(a, (Scalar)5);
  // +
  // -
  // *
  // /
}

using std::isnormal;
template <typename T> bool isnormal(const std::complex<T> & v)
{
  return isnormal(real(v));
}

template <typename DUALTYPE>
void transcendental()
{
  typedef typename DUALTYPE::value_type Scalar;

  for (int ii = -10; ii < 10; ii++) {
    double S = ii / 5.0;
    Scalar x = ii / 5.0;
    DUALTYPE xx(ii / 5.0, 1);
    using std::pow;
    // pow
    DUALTYPE res(pow(x,4), Scalar(4.) * (Scalar)pow(x,3));
    DU_EXPECT_NEAR(pow(xx,4), res);
    res = DUALTYPE(pow(3,x), pow((Scalar)3,x)*log((Scalar)3));
    DU_EXPECT_NEAR(pow((Scalar)3.,xx), res);
    //std::cerr << "x=" << x << " x^2 = " << pow(x,2) << "\n";
    //Scalar y =  pow(x,pow(x,2));
    //std::cerr << "x=" << x << " x^x^2 = " << y << "\n";
    //std::cerr << "xx=" << xx << "\n";
    res = DUALTYPE(pow(x,(Scalar)pow(x,2)),
                   pow(x,(Scalar)pow(x,2) - (Scalar)1) * (Scalar)pow(x, 2) +
                   (Scalar)2 * x * (Scalar)pow(x,pow(x,2)) * log(x));
    //std::cerr << "res=" << res << "\n";
    if (cxxduals::is_complex<Scalar>::value ? S != 0. : S > 0.) {
      DU_EXPECT_NEAR(pow(xx,pow(xx,2)), res);
    }
    else
      EXPECT_FALSE(isnormal(res.epart()));
    // sqrt
    // log
    // exp
    DUALTYPE B(0, ii);
    EXPECT_EQ(B.rpart(), (Scalar)0);
    EXPECT_EQ(B.epart(), (Scalar)ii);
    EXPECT_EQ(rpart(exp(B)), (Scalar)1);
    EXPECT_EQ(epart(exp(B)), (Scalar)ii);
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
TESTALL(transcendental)

TEST(basic, construction) {
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
  rand(d);
  rand(e);
  //abs(d);
  std::complex<float> cf(3.3, 4.4);
  EXPECT_EQ(conj(conj(d)), d);
  EXPECT_EQ(conj(d + e), conj(d) + conj(e));
  EXPECT_EQ(conj(d * e), conj(d) * conj(e));
  //EXPECT_EQ(conj(cf * d), conj(cf) * conj(d));
  //EXPECT_EQ(abs(conj(d)*d), abs(d) * abs(conj(d)));
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
