## cxxduals
Template library for dual numbers in c++

[![Build Status](https://api.travis-ci.org/tesch1/cxxduals.svg?branch=master)](http://travis-ci.org/tesch1/cxxduals)

## Usage

```cpp
#include <cxxduals/dual>
...
cxxduals::dual<double> x;
x = 3;
```

## TODO
- lots more tests
- `dot(dual<complex<> >)`
- hyperdual

## History
This started as a simple non-templated class found here: 
[http://adl.stanford.edu/hyperdual/](http://adl.stanford.edu/hyperdual/).

## License
MIT, same as the source library
