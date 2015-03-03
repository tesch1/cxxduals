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

int main(int argc, char **argv)
{
  duald x;

  x = {3,1};

  std::cout << "x=" << x << "\n";
  std::cout << "x*x=" << x*x << "\n";
  std::cout << "ipart(x*x) = d(x*x)/dx = " << ipart(x*x) << "\n";

  typedef dual<double> DUALTYPE;
  typedef dual<dual<double> > HDUALTYPE;
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
}
