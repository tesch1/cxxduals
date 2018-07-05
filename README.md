## cxxduals

*Under Construction!*

Template header library for [dual
numbers](http://en.wikipedia.org/wiki/Dual_number) in C++.  Dual
numbers are related to complex numbers, but &epsilon; is nilpotent.
Nesting provides hyperdual numbers, and hyperhyperdual numbers, etc...

Also compiles under CUDA.

[![Build Status](https://api.travis-ci.org/tesch1/cxxduals.svg?branch=master)](http://travis-ci.org/tesch1/cxxduals)
[![Coverage Status](https://coveralls.io/repos/github/tesch1/cxxduals/badge.svg?branch=master)](https://coveralls.io/github/tesch1/cxxduals?branch=master)

Using dual numbers in place of basic types provides a simple way to compute the derivative of a function, because:

\f$ f(x + &epsilon; y) = f(x) + &epsilon; f'(x) y \f$

Thus, to calculate \f$ f'(3) \f$, set \f$ y = 1 \f$, \f$ z = (3 +
&epsilon; 1) \f$ and take the \f$ &epsilon;\f$-part of \f$ f(z) \f$ =>
\f$ epart(f(z)) := f'(3) \f$

`cxxduals::dual<>`, `cxxduals::dual<float>`

## Usage

~~~~~~~~~~~~~~~{.cpp}
  
  #include <cxxduals/dual>
  using namespace cxxduals;

  ...
  dual<double> x;
  x = {3,1};

  std::cout << "x=" << x << "\n";
  std::cout << "x*x=" << x*x << "\n";
  std::cout << "epart(x*x) = d(x*x)/dx = " << epart(x*x) << "\n";
  
~~~~~~~~~~~~~~~

Before including the header, some "#defines" will modify what's done by
the header:

~~~~~~~~~~~~~~~{.cpp}

#define CXXDUALS_NO_LIMITS   // disable specialization of std::numeric_limits<>
#define CXXDUALS_NO_TYPEDEFS // disable typedefs for `dualf,duald,dualld,dualcf,dualcd,dualcld`
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

This started as a dual-number class implementation by Jeff A. Pike
found here:
[http://adl.stanford.edu/hyperdual/](http://adl.stanford.edu/hyperdual/),
also, [Fike's thesis](http://purl.stanford.edu/jw107zn5044) has some
nice numerical demonstrations.

Another nice paper on duals and C++ [Piponi, D. (2004). Automatic
Differentiation, C++ Templates, and Photogrammetry. Journal of
Graphics Tools, 9(4),
41–55. doi:10.1080/10867651.2004.10504901](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.89.7749&rep=rep1&type=pdf)

## References
http://people.rit.edu/harkin/research/articles/generalized_complex_numbers.pdf


## License
MIT, same as the original Fike code.

## Please report (and/or fix) any problems you find!

Once a good amount of test coverage is in place there should be
numbered releases.

