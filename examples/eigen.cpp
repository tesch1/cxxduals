//
// The MIT License (MIT)
//
// This file is a part of the cxxduals project.
// 
// Copyright (C) 2015 Michael Tesch,  tesch1 a gmail
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
#include <cmath>
#include <Eigen/Dense>
#include <cxxduals/dual>
#include <complex>

using namespace cxxduals;

typedef std::complex<double> complexd;
typedef std::complex<float> complexf;
typedef dual<double> duald;
typedef dual<float> dualf;
typedef dual<complexd> dualcd;
typedef dual<complexf> dualcf;
typedef std::complex<duald> cduald;
typedef std::complex<dualf> cdualf;

template <class eT, int N=2> using emtx = Eigen::Matrix<eT, N, N>;

int main(int argc, char *argv[])
{
  complexd cd;
  complexf cf;
  duald dd;
  dualf df;
  dualcd dcd;
  dualcf dcf;
  cduald cdd;
  cdualf cdf;

  emtx<complexd> ecd;
  emtx<complexf> ecf;
  emtx<duald> edd;
  emtx<dualf> edf;
  emtx<dualcd> edcd;
  emtx<dualcf> edcf;
  emtx<cduald> ecdd;
  emtx<cdualf> ecdf;

  std::cout << cd << cf << dd << df << dcd << dcf << cdd << cdf << "\n";
  std::cout << ecd << ecf << edd << edf << edcd << edcf << ecdd << ecdf << "\n";

  cxxduals::rand(cd);
  cxxduals::rand(cf);
  cxxduals::rand(dd);
  cxxduals::rand(df);
  cxxduals::rand(dcd);
  cxxduals::rand(dcf);
  cxxduals::rand(cdd);
  cxxduals::rand(cdf);

  dd = random<duald>();
  df = random<dualf>();
  dcd = random<dualcd>();
  dcf = random<dualcf>();

  std::cout << cd << cf << dd << df << dcd << dcf << cdd << cdf << "\n";

  std::cout << 1 * dd  << "\n";
  std::cout << 1. * dd << "\n";
  std::cout << dd * 1  << "\n";
  std::cout << dd * 1. << "\n";

  std::cout << 1 * dcd << "\n";
  std::cout << 1. * dcd << "\n";
  std::cout << dcd * 1 << "\n";
  std::cout << dcd * 1. << "\n";

  std::cout << 1 * dcf << "\n";
  std::cout << 1. * dcf << "\n";
  std::cout << dcf * 1 << "\n";
  std::cout << dcf * 1. << "\n";

  std::cout << dcf * cf << "\n";
  std::cout << cf * dcf << "\n";

  std::cout << (duald)1 * cdd << "\n";
  std::cout << (duald)1. * cdd << "\n";
  std::cout << cdd * (duald)1 << "\n";
  std::cout << cdd * (duald)1. << "\n";

  std::cout << (dualf)1 * cdf << "\n";
  std::cout << (dualf)1. * cdf << "\n";
  std::cout << cdf * (dualf)1 << "\n";
  std::cout << cdf * (dualf)1. << "\n";
  std::cout << cdf * (complexf)1. << "\n";
  std::cout << (complexf)1. * cdf << "\n";

  std::cout << (duald)1 * ecdd << "\n";
  std::cout << ecdd * (duald)1 << "\n";

  std::cout << (dualf)1 * ecdf << "\n";
  std::cout << (complexf)1 * ecdf << "\n";

  std::cout << edf * ecdf << "\n";
  std::cout << ecf * ecdf << "\n";
  std::cout << cf * ecdf << "\n";
  std::cout << df * ecdf << "\n";
  std::cout << ecdf * edf << "\n";
  std::cout << ecdf * ecf << "\n";
  std::cout << ecdf * cf << "\n";
  std::cout << ecdf * df << "\n";

#if 0
  ecd = ecd.Random();
  ecf = ecf.Random();
  edd = edd.Random();
  edf = edf.Random();
  edcd = edcd.Random();
  edcf = edcf.Random();
  ecdd = ecdd.Random();
  ecdf = ecdf.Random();
  std::cout << ecd << "\n";
#endif
  std::cout << "\n";
}
