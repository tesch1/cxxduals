## cxxduals

*Under Construction!*

Template header library for [dual
numbers](http://en.wikipedia.org/wiki/Dual_number) in C++.  Dual
numbers are related to complex numbers, but &epsilon; is nilpotent
(&epsilon; * &epsilon; = 0).  Nesting provides hyperdual numbers, and
hyperhyperdual numbers, etc...

Also compiles under CUDA.

[![Build Status](https://api.travis-ci.org/tesch1/cxxduals.svg?branch=master)](http://travis-ci.org/tesch1/cxxduals)
[![Coverage Status](https://coveralls.io/repos/github/tesch1/cxxduals/badge.svg?branch=master)](https://coveralls.io/github/tesch1/cxxduals?branch=master)

Using dual numbers in place of basic types provides a simple way to
compute the derivative of a function, because:

\f$ f(x + &epsilon; y) = f(x) + &epsilon; f'(x) y \f$

Thus, to calculate \f$ f'(3) \f$, set \f$ y = 1 \f$, \f$ z = (3 +
&epsilon; 1) \f$ and take the \f$ &epsilon;\f$-part of \f$ f(z) \f$ =>
\f$ epart(f(z)) := f'(3) \f$

Shortcuts into the docs:

- `namespace cxxduals`
- `cxxduals::dual`
- `cxxduals::sin`

## Usage

A simple example calculating (x*x) and the derivative of (x*x):

~~~~~~~~~~~~~~~{.cpp}
  
  #include <iostream>
  #include <cxxduals/dual>
  using namespace cxxduals;
  
  int main(int argc, char *argv[])
  {
    dual<double> x;
    x = {3,1};
  
    std::cout << "x=" << x << "\n";
    std::cout << "x*x=" << x*x << "\n";
    std::cout << "epart(x*x) = d(x*x)/dx = " << epart(x*x) << "\n";
  }
  
~~~~~~~~~~~~~~~

Produces:

~~~~~~~~~~~~~~~
  x=(3 + e1*1)
  x*x=(9 + e1*6)
  epart(x*x) = d(x*x)/dx = 6
~~~~~~~~~~~~~~~


Before including the header, some "#defines" will modify what's done by
the header:

~~~~~~~~~~~~~~~{.cpp}

#define CXXDUALS_NO_LIMITS   // disable specialization of std::numeric_limits<>
#define CXXDUALS_NO_TYPEDEFS // disable typedefs for `dualf,duald,dualld,dualcf,dualcd,dualcld`
#define CXXDUALS_EIGEN       // force inclusion of Eigen interface (normally auto-detected)
#include <cxxduals/dual>

~~~~~~~~~~~~~~~

See the examples in tests/* and examples/*

## TODO

- lots more tests
- let the value_type be a std::vector
- add printer to show the number in linear form (as a matrix)
- define `dot(dual<complex<> >` , `dual<complex<> >)` and
  `norm(dual<complex<> >)`
- currently only tested on c++11, should make sure older c++ works as
  much as possible too
- support the other algebras, and their various nestings: (how easy
  would this be???)
  - (&epsilon; * &epsilon;) = -1  (["complex number"](http://en.wikipedia.org/wiki/Complex_number))
  - (&epsilon; * &epsilon;) = 1 (["double
  nunmber"](http://www.euclideanspace.com/maths/algebra/realNormedAlgebra/other/)
  / ["split complex
  number"](http://en.wikipedia.org/wiki/Split-complex_number))
- try to minimize subtractive cancellation within the library
- support & test multi-precision container types

## History

This started as a dual-number class implementation by Jeff A. Fike
found here:
[http://adl.stanford.edu/hyperdual/](http://adl.stanford.edu/hyperdual/).

It's been generalized for nesting, cleaned up for easier use in C++,
and been made suitable for use in
[Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page).

## References

- https://en.wikipedia.org/wiki/Dual_number
- [Fike's thesis](http://purl.stanford.edu/jw107zn5044)
- [Piponi, D. (2004). Automatic Differentiation, C++ Templates, and Photogrammetry. Journal of Graphics Tools, 9(4), 41–55. doi:10.1080/10867651.2004.10504901](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.89.7749&rep=rep1&type=pdf)
- http://people.rit.edu/harkin/research/articles/generalized_complex_numbers.pdf
- https://www.ams.org/journals/tran/1960-094-03/S0002-9947-1960-0146681-0/S0002-9947-1960-0146681-0.pdf
- http://www.dtecta.com/files/GDC13_vandenBergen_Gino_Math_Tut.pdf
- https://hal.archives-ouvertes.fr/hal-01114178/document

## Other implementations

- http://darioizzo.github.io/audi/gdual.html https://github.com/darioizzo/audi/blob/master/include/audi/gdual.hpp
- https://github.com/ceres-solver/ceres-solver/blob/master/include/ceres/jet.h
- https://github.com/dtecta/motion-toolkit/blob/master/moto/Dual.hpp
- https://github.com/JuliaDiff/DualNumbers.jl

## License

MIT, same as the original Fike code.

## Please report (and/or fix) any problems you find!

Once a good amount of test coverage is in place there should be
numbered releases.

