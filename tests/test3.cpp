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
#include <Eigen/Dense>
#include <cxxduals/dual>

#include "test_helpers.h"

using namespace cxxduals;
template <class eT, int N=2> using emtx = Eigen::Matrix<eT, N, N>;

typedef std::complex<double> complexd;
typedef std::complex<float> complexf;
typedef dual<double> duald;
typedef dual<float> dualf;
typedef dual<complexd> dualcd;
typedef dual<complexf> dualcf;
typedef std::complex<duald> cduald;
typedef std::complex<dualf> cdualf;

TEST(Eigen, construction)
{
  emtx<double> ed;
  emtx<float> ef;
  emtx<complexd> ecd;
  emtx<complexf> ecf;
  emtx<duald> edd;
  emtx<dualf> edf;
  emtx<dualcd> edcd;
  emtx<dualcf> edcf;
  emtx<cduald> ecdd;
  emtx<cdualf> ecdf;
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout.precision(20);
  std::cerr.precision(20);
  return RUN_ALL_TESTS();
}
