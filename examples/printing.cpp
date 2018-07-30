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
#include <iostream>
#include <cmath>
#include <cxxduals/dual>
#include <complex>

using namespace cxxduals;

typedef dual<double> duald;
typedef dual<float> dualf;
typedef dual<std::complex<double> > dualcd;
typedef dual<std::complex<float> > dualcf;
typedef std::complex<double> complexd;
typedef std::complex<float> complexf;

int main(int argc, char *argv[])
{
  dual<double> f = {3,1};
  std::complex<double> ax(3,1);
  dualcd g = {std::complex<double>(3), 1};
  dualcd h = {ax, 1};
  std::complex<dual<double>> m;
  std::complex<dual<double>> n({3,1},0);
  std::complex<dual<double>> o({3,1},{1,0});

  std::cout.precision(20);
  std::cerr.precision(20);

  cxxduals::rand(m);

  std::cout << "f=" << f << "\n";
  std::cout << "g=" << g << "\n";
  std::cout << "h=" << h << "\n";
  std::cout << "m=" << m << "\n";

  std::cout << "f*f = " << (f*f) << "\n";
  std::cout << "g*g = " << (g*g) << "\n";
  std::cout << "h*h = " << (h*h) << "\n";
  std::cout << "m*m=" << m*m << "\n";
  std::cout << "pow(f,2.0) = " << pow(f,2.0) << "\n";
  std::cout << "pow(g,2.0) = " << pow(g,(complexd)2.0) << "\n";
  std::cout << "pow(m,2.0) = " << pow(n,(duald)2.0) << "\n";
  std::cout << "0.5*(9)^(-0.5) = " << 0.5 * std::sqrt(9) << "\n";
  std::cout << "0.5*(3+1i)^(-0.5) = " << 0.5 * std::pow(ax,-0.5) << "\n";

  std::cout << "d/dx f*f = " << epart(f*f) << "\n";
  std::cout << "d/dx g*g = " << epart(g*g) << "\n";
  std::cout << "d/dx h*h = " << epart(h*h) << "\n";
  std::cout << "d/dx o*o = " << (o*o) << "\n";
  std::cout << "d/dx n*n = " << epart(real(n*n)) << "\n";
  std::cout << "d/dx h^0.5 = " << sqrt(h) << "\n";
  std::cout << "d/dx pow(f,2) = " << epart(pow(f,2.0)) << "\n";

  std::cout << "hyperduals:\n";
  std::cout << hyperdualf(1,2) << "\n";
}
