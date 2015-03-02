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
#include <complex>
#include <cmath>
#include <cxxduals/dual>

#include "test_helpers.h"

using namespace cxxduals;

struct pike_f1 {
  // function
  template <typename TYPE>
  TYPE
  f(const TYPE & x) {
    typedef typename dual_trait_helper<TYPE>::scalar_type fp_t;
    return exp(x) / sqrt(pow(sin(x), fp_t(3.)) + pow(cos(x), fp_t(3.)));
  }

  // analytic derivative
  template <typename TYPE>
  TYPE
  df(const TYPE & x) {
    typedef typename dual_trait_helper<TYPE>::scalar_type fp_t;
    return (exp(x) * ((fp_t)3. * cos(x) + (fp_t)5.*cos((fp_t)3.*x) + (fp_t)9. * sin(x) + sin((fp_t)3.*x))) /
      ((fp_t)8. * pow(pow(sin(x), (fp_t)3.) + pow(cos(x), (fp_t)3.), (fp_t)(3./2.)));
  }

  // analytic second derivative
  template <typename TYPE>
  TYPE
  ddf(const TYPE & x) {
    typedef typename dual_trait_helper<TYPE>::scalar_type fp_t;
    return (exp(x) * (fp_t(130.) - fp_t(12.) * cos(fp_t(2.)*x) + fp_t(30.)*cos(fp_t(4.)*x) + fp_t(12.)*cos(fp_t(6.)*x)
                      - fp_t(111.)*sin(fp_t(2.)*x) + fp_t(48.)*sin(fp_t(4.)*x) + fp_t(5.)*sin(fp_t(6.)*x))) /
      (fp_t(64.) * pow(pow(sin(x), fp_t(3.)) + pow(cos(x), fp_t(3.)), fp_t(5./2.)));
  }

  // analytic third derivative
  template <typename TYPE>
  TYPE
  dddf(const TYPE & x) {
    typedef typename dual_trait_helper<TYPE>::scalar_type fp_t;
    return TYPE(0);
  }

};

template <typename UNOTYPE>
void
fike_example1()
{
  int reps = 1;
  pike_f1 f1;
  typedef dual<UNOTYPE> DUALTYPE;
  typedef dual<dual<UNOTYPE> > HDUALTYPE;
  srand48(1);

  for (int ii = 0; ii < reps; ii++) {
    // pick a random x
    UNOTYPE x = drand48() * 50;
    // calculate f, f' and f'' and f''' analytically
    UNOTYPE f = f1.f(x);
    UNOTYPE fp = f1.df(x);
    UNOTYPE fpp = f1.ddf(x);
    UNOTYPE fppp = f1.dddf(x);
    // calculate f, f' and f'' and f'' and f''' using duals
    DUALTYPE dfp = f1.f(DUALTYPE(x,1));
    DUALTYPE ddfp = f1.df(DUALTYPE(x,1));
    HDUALTYPE dfpp = f1.f(HDUALTYPE(DUALTYPE(x,1),DUALTYPE(1,1)));

    // compare analytic and dual results
    std::cout << "f=" << f << " fp=" << fp << " fpp=" << fpp << " fppp=" << fppp << "\n";
    MY_EXPECT_NEAR(f, rpart(dfp)) << " x=" << x;
    MY_EXPECT_NEAR(f, rpart(rpart(dfpp)));
    MY_EXPECT_NEAR(fp, ipart(dfp)) << " x=" << x;
    MY_EXPECT_NEAR(fp, rpart(ddfp)) << " x=" << x;
    MY_EXPECT_NEAR(fpp, ipart(ddfp)) << " x=" << x;
    MY_EXPECT_NEAR(fpp, ipart(rpart(dfpp))) << " ::" << dfpp;
    //MY_EXPECT_NEAR(fppp, ipart(ipart(dfpp)));
  }
}

//TEST(fike1,double) { fike_example1<double>(); }
TEST(fike1,complexf) { fike_example1<complexf>(); }
TEST(fike1,complexd) { fike_example1<complexd>(); }
TEST(fike1,complexld) { fike_example1<complexld>(); }

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout.precision(20);
  std::cerr.precision(20);
  return RUN_ALL_TESTS();
}
