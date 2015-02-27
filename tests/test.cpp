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
  EXPECT_EQ(x.realpart(), (Scalar)1.1);
  EXPECT_EQ(realpart(x), (Scalar)1.1);
  EXPECT_EQ(x.epart(), (Scalar)0.0);
  EXPECT_EQ(epart(x), (Scalar)0.0);

  DUALTYPE z(1.1);
  EXPECT_EQ(z.realpart(), (Scalar)1.1);
  EXPECT_EQ(realpart(z), (Scalar)1.1);
  EXPECT_EQ(z.epart(), (Scalar)0.0);
  EXPECT_EQ(epart(z), (Scalar)0.0);

  DUALTYPE y(1.1, 2.2);
  EXPECT_EQ(y.realpart(), (Scalar)1.1);
  EXPECT_EQ(realpart(y), (Scalar)1.1);
  EXPECT_EQ(y.epart(), (Scalar)2.2);
  EXPECT_EQ(epart(y), (Scalar)2.2);

  DUALTYPE w = {1.1, 2.2};
  EXPECT_EQ(w.realpart(), (Scalar)1.1);
  EXPECT_EQ(w.epart(), (Scalar)2.2);

  DUALTYPE a{1.1, 2.2};
  EXPECT_EQ(a.realpart(), (Scalar)1.1);
  EXPECT_EQ(a.epart(), (Scalar)2.2);
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
  return expect_near(A.realpart(), B.realpart()) && expect_near(A.epart(), B.epart());
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
  DUALTYPE a;
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

#define TESTALL(func) \
  TEST (dualf, func) { func<dualf, float>(); } \
  TEST (duald, func) { func<duald, double>(); } \
  TEST (dualld, func) { func<dualld, long double>(); } \
  TEST (dualdf, func) { func<dualcf, complexf>(); } \
  TEST (dualcd, func) { func<dualcd, complexd>(); } \
  TEST (dualcld, func) { func<dualcld, complexld>(); }

#define TESTREAL(func) \
  TEST (duald, func) { func<duald, double>(); } \
  TEST (dualf, func) { func<dualf, float>(); }

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
