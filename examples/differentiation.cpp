//
// The MIT License (MIT)
// 
// Copyright (c) 2006 Jeffrey A. Fike
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

#include <iostream>
#include <cxxduals/dual>

using namespace cxxduals;

template <int POW>
struct F1 {
  // function
  template <typename TYPE>
  TYPE
  f(const TYPE & x) {
    return pow(x, POW);
  }

  // analytic derivative
  template <typename TYPE>
  TYPE
  df(const TYPE & x) {
    return POW * pow(x, POW-1);
  }

  // analytic second derivative
  template <typename TYPE>
  TYPE
  ddf(const TYPE & x) {
    return POW * (POW-1) * pow(x, POW-2);
  }

  // analytic third derivative
  template <typename TYPE>
  TYPE
  dddf(const TYPE & x) {
    return POW * (POW-1) * (POW-2) * pow(x, POW-3);
  }
};

int main(int argc, char **argv)
{
  duald x;

  x = {3,1};

  std::cout << "x=" << x << "\n";
  std::cout << "x*x=" << x*x << "\n";
  std::cout << "epart(x*x) = d(x*x)/dx = " << epart(x*x) << "\n";

  typedef double UNOTYPE;
  typedef dual<double> DUALTYPE;
  typedef dual<dual<double> > HDUALTYPE;
  typedef dual<dual<dual<UNOTYPE> > > TDUALTYPE;
  HDUALTYPE a(DUALTYPE(1,2),DUALTYPE(3,4));
  HDUALTYPE b(DUALTYPE(11,12),DUALTYPE(13,14));
  hyperdualcd c(DUALTYPE(1,2),DUALTYPE(3,4));
  hyperdualcd d{1,2,3,{4,4}};
  std::cout << a << "\n"
            << b << "\n"
            << a+b << "\n"
            << a*b << "\n"
            << c << "\n"
            << d << "\n";

  std::cout << "double<> depth:" << dual_trait_helper<double>::depth
            << " num_elem: " << dual_trait_helper<double>::num_elem
            << " is_nested: " << dual_trait_helper<double>::is_nested::value
            << "\n";
  std::cout << "dual<> depth:" << dual_trait_helper<DUALTYPE>::depth
            << " num_elem: " << dual_trait_helper<DUALTYPE>::num_elem
            << " is_nested: " << dual_trait_helper<DUALTYPE>::is_nested::value
            << "\n";
  std::cout << "dual<dual<>> depth:" << dual_trait_helper<HDUALTYPE>::depth
            << " num_elem: " << dual_trait_helper<HDUALTYPE>::num_elem
            << " is_nested: " << dual_trait_helper<HDUALTYPE>::is_nested::value
            << "\n";

  {
    // differentiate
    //UNOTYPE x = drand48() * 10;
    F1<3> f1;
    UNOTYPE x = 2;
    // calculate f, f' and f'' and f''' analytically
    UNOTYPE f = f1.f(x);
    UNOTYPE fp = f1.df(x);
    UNOTYPE fpp = f1.ddf(x);
    UNOTYPE fppp = f1.dddf(x); //TODO
    // calculate f, f' and f'' and f'' and f''' using duals
    DUALTYPE dfp = f1.f(DUALTYPE(x,1));
    DUALTYPE ddfp = f1.df(DUALTYPE(x,1));
    UNOTYPE x4 = 0;
    HDUALTYPE dfpp = f1.f(HDUALTYPE(DUALTYPE(x,1),DUALTYPE(1,x4)));
    TDUALTYPE dfppp = f1.f(TDUALTYPE(HDUALTYPE(DUALTYPE(x,1),
                                               DUALTYPE(1,0)),
                                     HDUALTYPE(DUALTYPE(1,0),
                                               DUALTYPE(0,0))));
    std::cout << "HD=" << HDUALTYPE(DUALTYPE(x,1),DUALTYPE(1,x4)) << "\n";
    std::cout << "TD=" << TDUALTYPE(HDUALTYPE(DUALTYPE(x,1),
                                               DUALTYPE(1,0)),
                                     HDUALTYPE(DUALTYPE(1,0),
                                               DUALTYPE(0,0))) << "\n";
    std::cout << "x=" << x << "\nf=" << f << "\nfp=" << fp
              << "\nfpp=" << fpp << "\nfppp=" << fppp << "\n";
    std::cout << "dfp=" << dfp << "\n";
    std::cout << "ddfp=" << ddfp << "\n";
    std::cout << "dfpp=" << dfpp << "\n";
    std::cout << "dfppp=" << dfppp << "\n";
  }
  return 0;
}
