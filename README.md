# *** THIS LIBRARY IS CURRENTLY UNDER DEVELOPMENT ***
Please do use it and report/fix any problems you find!

Once a good amount of test coverage is in place there will be numbered releases.

## cxxduals
Template header library for nesting [dual numbers](http://en.wikipedia.org/wiki/Dual_number) in c++, akin to complex numbers, but &epsilon; is nilpotent.  Nesting provides hyperdual numbers, and hyperhyperdual numbers, etc...

[![Build Status](https://api.travis-ci.org/tesch1/cxxduals.svg?branch=master)](http://travis-ci.org/tesch1/cxxduals)

Using dual numbers in place of basic types provides a simple way to compute the derivative of a function, because:

f(x + &epsilon; y) = f(x) + &epsilon; f'(x) y

Thus, to calculate f'(3), set z = (3 + &epsilon; 1) and take the &epsilon;-part of f(z) => ipart(f(z)) := f'(3)

## Usage

```cpp
  #include <cxxduals/dual>

  ...

  cxxduals::dual<double> x;
  x = {3,1};

  std::cout << "x=" << x << "\n";
  std::cout << "x*x=" << x*x << "\n";
  std::cout << "ipart(x*x) = d(x*x)/dx = " << ipart(x*x) << "\n";
```

Before including the header, some #defines will modify what's done by the header:
```cpp
#define CXXDUALS_NO_LIMITS   // disable specialization of std::numeric_limits<> for the ```dualf,duald...``` types
#define CXXDUALS_NO_TYPEDEFS // disable typedefs for ```dualf,duald,dualld,dualcf,dualcd,dualcld```
```

See the examples in tests/* and examples/*

## TODO
- lots more tests
- define ```dot(dual<complex<> >, dual<complex<> >)``` and ```norm(dual<complex<> >)```
- currently only tested on c++11, should make sure older c++ works as much as possible too
- maybe support the other possibilities for: (how easy would this be?!?!? maybe super-easy!)
  - (&epsilon; * &epsilon;) = -1  ("complex")
  - (&epsilon; * &epsilon;) = 1
  - (&epsilon; * &epsilon;) = 0
- dual vector support: let the value_type be a vector
- try to minimize subtractive cancellation within the library
- support & test multi-precision container types

## History
This started as a simple non-templated class by Jeff A. Pike found here: 
[http://adl.stanford.edu/hyperdual/](http://adl.stanford.edu/hyperdual/), also, 
[Fike's thesis](http://purl.stanford.edu/jw107zn5044) has some nice numerical demonstrations.

Another nice paper on duals and C++ [Piponi, D. (2004). Automatic Differentiation, C++ Templates, and Photogrammetry. Journal of Graphics Tools, 9(4), 41–55. doi:10.1080/10867651.2004.10504901](http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.89.7749&rep=rep1&type=pdf)

## License
MIT, same as the original Fike code.
