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
    return (exp(x) * (fp_t(130.) - fp_t(12.) * cos(fp_t(2.)*x) + fp_t(30.)*cos(fp_t(4.)*x) 
                      + fp_t(12.)*cos(fp_t(6.)*x)
                      - fp_t(111.)*sin(fp_t(2.)*x) + fp_t(48.)*sin(fp_t(4.)*x) + fp_t(5.)*sin(fp_t(6.)*x))) /
      (fp_t(64.) * pow(pow(sin(x), fp_t(3.)) + pow(cos(x), fp_t(3.)), fp_t(5./2.)));
#if 0
    // same thing, different error
    return fp_t(1.0/4.0) * exp(x) * (fp_t(-24.0) * cos(x) * sin(x) 
                                     - fp_t(3.0) * pow(cos(x),fp_t(2.0))
                                     - fp_t(21.0) * pow(cos(x),fp_t(4.0))
                                     + fp_t(24.0) * pow(cos(x),fp_t(6.0))
                                     + fp_t(14.0) * pow(cos(x),fp_t(3.0)) * sin(x)
                                     + fp_t(10.0) * pow(cos(x),fp_t(5.0)) * sin(x)
                                     + fp_t(10.0))
      / pow(sin(x) + pow(cos(x),fp_t(3.0)) - pow(cos(x),fp_t(2.0)) * sin(x), fp_t(5.0/2.0));
#endif
  }

  // analytic third derivative
  template <typename TYPE>
  TYPE
  dddf(const TYPE & x) {
    typedef typename dual_trait_helper<TYPE>::scalar_type fp_t;
    return exp(x)*fp_t(1.0)
      / pow(sin(x)
            + pow(cos(x),fp_t(3.0))
            - pow(cos(x),fp_t(2.0)) * sin(x), fp_t(7.0)/fp_t(2.0))
      * (cos(x) *
         - fp_t(186.0)
         + sin(x)*fp_t(68.0)
         + pow(cos(x),fp_t(3.0))*fp_t(171.0)
         - pow(cos(x),fp_t(5.0))*fp_t(42.0) 
         - pow(cos(x),fp_t(7.0))*fp_t(33.0)
         + pow(cos(x),fp_t(9.0))*fp_t(110.0)
         + pow(cos(x),fp_t(2.0))*sin(x)*fp_t(256.0) 
         - pow(cos(x),fp_t(4.0))*sin(x)*fp_t(495.0)
         + pow(cos(x),fp_t(6.0))*sin(x)*fp_t(139.0)
         + pow(cos(x),fp_t(8.0))*sin(x)*fp_t(74.0))*(fp_t(1.0)/fp_t(8.0));
  }

};

template <typename UNOTYPE>
void
fike_example1()
{
  int reps = 10000;
  pike_f1 f1;
  typedef dual<UNOTYPE> DUALTYPE;
  typedef dual<dual<UNOTYPE> > HDUALTYPE;
  typedef dual<dual<dual<UNOTYPE> > > TDUALTYPE;
  srand48(1);

  for (int ii = 0; ii < reps; ii++) {
    // pick a random x
    UNOTYPE x = drand48() * 10;
    // calculate f, f' and f'' and f''' analytically
    UNOTYPE f = f1.f(x);
    UNOTYPE fp = f1.df(x);
    UNOTYPE fpp = f1.ddf(x);
    UNOTYPE fppp = f1.dddf(x);
    // calculate f, f' and f'' and f'' and f''' using duals
    DUALTYPE dfp = f1.f(DUALTYPE(x,1));
    DUALTYPE ddfp = f1.df(DUALTYPE(x,1));
    UNOTYPE x4 = 0;
    HDUALTYPE dfpp = f1.f(HDUALTYPE(DUALTYPE(x,1),DUALTYPE(1,x4)));
    TDUALTYPE dfppp = f1.f(TDUALTYPE(HDUALTYPE(DUALTYPE(x,1),
                                               DUALTYPE(1,1)),
                                     HDUALTYPE(DUALTYPE(1,1),
                                               DUALTYPE(1,x4))));

    // compare analytic and dual results
    MY_EXPECT_NEAR(f, rpart(dfp)) << " x=" << x;
    MY_EXPECT_NEAR(f, rpart(rpart(dfpp)));
    MY_EXPECT_NEAR(fp, ipart(dfp)) << " x=" << x;
    MY_EXPECT_NEAR(fp, rpart(ddfp)) << " x=" << x;
    MY_EXPECT_NEAR(fp, rpart(ipart(dfpp))) << " x=" << x;
    MY_EXPECT_NEAR(fp, ipart(rpart(dfpp))) << " x=" << x;
    MY_EXPECT_NEAR(fpp, ipart(ddfp)) << " x=" << x;
    UNOTYPE DDf = ipart(ipart(dfpp)) - x4 * ipart(rpart(dfpp));
    MY_EXPECT_NEAR(fpp, DDf) << " ::" << DDf;
#if 0
    std::cout << "x=" << x << "\nf=" << f << "\nfp=" << fp << "\nfpp=" << fpp << "\nfppp=" << fppp << "\n";
    std::cout << "hd=" << dfpp << "\n\n";
    std::cout << "td=" << dfppp << "\n";
    std::cout << "hx=" << ipart(ipart(dfpp)) - ipart(rpart(dfpp)) << "\n";
    std::cout << "ij=" << ipart(rpart(dfpp)) * ipart(ipart(dfpp)) << "\n";
    std::cout << "ij=" << rpart(dfpp) * ipart(dfpp) << "\n";
#endif
  }
}

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
