//
// The MIT License (MIT)
// 
// Copyright (C) 2015 Michael Tesch tesch a tum de
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
#include <complex>
#include <cxxduals/dual>

#define PRECISION (1e-16)

typedef std::complex<float> complexf;
typedef std::complex<double> complexd;
typedef std::complex<long double> complexld;

using namespace cxxduals;

template <typename DUALTYPE, typename Scalar>
void construct()
{
  DUALTYPE x = (Scalar)1.1;
  EXPECT_EQ(x.rpart(), (Scalar)1.1);
  EXPECT_EQ(rpart(x), (Scalar)1.1);
  EXPECT_EQ(x.ipart(), (Scalar)0.0);
  EXPECT_EQ(ipart(x), (Scalar)0.0);

  DUALTYPE z(1.1);
  EXPECT_EQ(z.rpart(), (Scalar)1.1);
  EXPECT_EQ(rpart(z), (Scalar)1.1);
  EXPECT_EQ(z.ipart(), (Scalar)0.0);
  EXPECT_EQ(ipart(z), (Scalar)0.0);

  DUALTYPE y(1.1, 2.2);
  EXPECT_EQ(y.rpart(), (Scalar)1.1);
  EXPECT_EQ(rpart(y), (Scalar)1.1);
  EXPECT_EQ(y.ipart(), (Scalar)2.2);
  EXPECT_EQ(ipart(y), (Scalar)2.2);

  DUALTYPE w = {1.1, 2.2};
  EXPECT_EQ(w.rpart(), (Scalar)1.1);
  EXPECT_EQ(w.ipart(), (Scalar)2.2);

  DUALTYPE a{1.1, 2.2};
  EXPECT_EQ(a.rpart(), (Scalar)1.1);
  EXPECT_EQ(a.ipart(), (Scalar)2.2);
}

// need the 100.0 factor in epsilon for 'long double'
template <typename UNOTYPE>
bool expect_near(const UNOTYPE & A, const UNOTYPE & B, 
                 typename dual_trait_helper<UNOTYPE>::scalar_type PREC 
                 = 100.0 * std::numeric_limits<typename dual_trait_helper<UNOTYPE>::scalar_type >::epsilon()
                 )
{
  if (std::abs(A - B) >= PREC)
    std::cout << "std::abs(A - B) = " << std::abs(A - B) << " PREC= " << PREC << "\n";
  return std::abs(A - B) < PREC;
}

template <typename UNOTYPE>
bool expect_near_dual(const dual<UNOTYPE> & A, const dual<UNOTYPE> & B)
{
  return expect_near(A.rpart(), B.rpart()) && expect_near(A.ipart(), B.ipart());
}

#define MY_EXPECT_NEAR(A,B) \
  if (!expect_near(A,B))                  \
    do {                                  \
      ADD_FAILURE_AT(__FILE__, __LINE__) << #A << " !~= " << #B << "\n (" << A << " !~= " << B; \
    } while (0)
#define DU_EXPECT_NEAR(A,B)                                             \
  if (!expect_near_dual(A,B))                                           \
    do {                                                                \
      ADD_FAILURE_AT(__FILE__, __LINE__) << #A << " !~= " << #B << "\n (" << A << " !~= " << B; \
    } while (0)

template <typename DUALTYPE, typename Scalar>
void equality()
{
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
  EXPECT_EQ(abs(h), g);
  EXPECT_EQ(abs(-h), g);
  EXPECT_EQ(-abs(h), h);
  EXPECT_EQ(abs(h), (Scalar)2.2);
  EXPECT_EQ(+abs(h), (Scalar)2.2);
  EXPECT_EQ(-abs(h), (Scalar)-2.2);
  DU_EXPECT_NEAR(pow(j,(Scalar)2.0), DUALTYPE(9.,6.));
  DU_EXPECT_NEAR(sqrt(l), DUALTYPE(3., 0.5*pow(9,-0.5)) );
}

template <typename DUALTYPE, typename Scalar>
void compare()
{
  DUALTYPE d{1.1, 2.2};
  DUALTYPE e{1.1, 2.2};
  DUALTYPE f{1.1, 2.21};
  DUALTYPE g{2.2, 2.21};
  DUALTYPE h{-2.2, -2.21};
  DUALTYPE j{3, 1};
  DUALTYPE k{9, 6};
  DUALTYPE l{9, 1};
  MY_EXPECT_NEAR(ipart(sqrt(l)), (Scalar)(0.5*pow(9,-0.5)));
  MY_EXPECT_NEAR(ipart(pow(j,(Scalar)2.0)), (Scalar)6.0);
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
  EXPECT_TRUE(max(f,(Scalar)2.2) == (Scalar)2.2);
  EXPECT_TRUE(max((Scalar)2.2,f) == (Scalar)2.2);
  EXPECT_TRUE(min(f,(Scalar)2.2) == f);
  EXPECT_TRUE(min((Scalar)2.2,f) == f);
  EXPECT_TRUE(max(f,g) == g);
  EXPECT_TRUE(max(g,f) == g);
  EXPECT_TRUE(min(f,g) == f);
  EXPECT_TRUE(min(g,f) == f);
}

template <typename DUALTYPE, typename Scalar>
void arithmetic()
{
  DUALTYPE a, b;
  a = (Scalar)1;
  b = (Scalar)2;
  b = a = b = a;
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

template <typename DUALTYPE, typename Scalar>
void transcendental()
{
  DUALTYPE a;
  // pow
  // sqrt
  // log
  // exp
  // sin
  // cos
  // tan
  // asin
  // acos
  // atan
  // atan2
}

void takes_dualcd(dualcd blah)
{
  
}

void takes_dualcd_ref(dualcd & blah)
{
  
}

template <typename TYPE1, typename TYPE2>
void casting()
{
  dual<TYPE1> a;
  dual<TYPE2> b;

  a = dual<TYPE1>{1,2};
  b = 1;
  b = 1.0f;
  b = 1.0;
  b = (TYPE2)1.0;

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

TEST (generic, generic)
{
  dualcd a;
  dualcf b;
  takes_dualcd_ref(a);
  //takes_dualcd(b);
  takes_dualcd(dualcd(b));
  //takes_dualcd_ref(dualcd(b));
}

#define TESTALL(func) \
  TEST (dualf, func) { func<dualf, float>(); } \
  TEST (duald, func) { func<duald, double>(); } \
  TEST (dualld, func) { func<dualld, long double>(); } \
  TEST (dualdf, func) { func<dualcf, complexf>(); } \
  TEST (dualcd, func) { func<dualcd, complexd>(); } \
  TEST (dualcld, func) { func<dualcld, complexld>(); }

#define TESTREAL(func) \
  TEST (duald, func) { func<duald, double>(); } \
  TEST (dualf, func) { func<dualf, float>(); } \
  TEST (dualld, func) { func<dualld, long double>(); }

#define TEST_TYPEMIX(func, type1, type2) \
  TEST (func, type1##_##type2) { func<type1,type2>(); }

typedef long double longdouble;

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

// complex types
#define TYPEMIX6(RTYPE)                         \
  TEST_TYPEMIX(casting, RTYPE, float)           \
  TEST_TYPEMIX(casting, RTYPE, double)          \
  TEST_TYPEMIX(casting, RTYPE, longdouble)      \
  TEST_TYPEMIX(casting, RTYPE, complexf)        \
  TEST_TYPEMIX(casting, RTYPE, complexd)        \
  TEST_TYPEMIX(casting, RTYPE, complexld)

TYPEMIX6(complexf)
TYPEMIX6(complexd)
TYPEMIX6(complexld)

TESTALL(construct)
TESTALL(equality)
TESTREAL(compare)
TESTALL(arithmetic)
TESTALL(transcendental)

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout.precision(20);
  std::cerr.precision(20);
  return RUN_ALL_TESTS();
}
