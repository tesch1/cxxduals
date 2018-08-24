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

typedef long double longdouble;

#ifndef __CUDACC__
typedef std::complex<float> complexf;
typedef std::complex<double> complexd;
typedef std::complex<long double> complexld;
#endif

using namespace cxxduals;

// need the 100.0 factor in epsilon for 'long double'
template <typename UNOTYPE>
bool expect_near(const UNOTYPE & A, const UNOTYPE & B)
{
  using std::abs;
  using std::sqrt;

  typename dual_traits<UNOTYPE>::scalar_type
    //PREC = sqrt(std::numeric_limits<typename dual_traits<UNOTYPE>::scalar_type >::epsilon());
    PREC = 1500.0 * std::numeric_limits<typename dual_traits<UNOTYPE>::scalar_type >::epsilon();

  if (abs(A - B) < PREC)
    return true;
  if (abs(B) != 0 && abs(A - B)/abs(sqrt(A*A + B*B)) < PREC)
    return true;
  std::cout << "----------------- FAIL -------------------\n";
  std::cout << "abs(A - B) = " << abs(A - B) << " PREC= " << PREC << " A=" << A << "\n";
  std::cout << "abs(A - B)/abs(sqrt(A*A + B*B)) = " << abs(A - B)/abs(sqrt(A*A + B*B)) << " PREC= " << PREC << "\n";
  return false;
}

template <typename UNOTYPE>
bool expect_near_dual(const dual<UNOTYPE> & A, const dual<UNOTYPE> & B)
{
  return expect_near(A.rpart(), B.rpart()) && expect_near(A.epart(), B.epart());
}

#define MY_EXPECT_NEAR(A,B)                                             \
    if (!expect_near(A,B))                                              \
      ADD_FAILURE_AT(__FILE__, __LINE__) << #A << " !~= " << #B << "\n (" << A << " !~= " << B
#define DU_EXPECT_NEAR(A,B)                                             \
    if (!expect_near_dual(A,B))                                         \
      ADD_FAILURE_AT(__FILE__, __LINE__) << #A << " !~= " << #B << "\n (" << A << " !~= " << B

#ifndef __CUDACC__
#define TESTALL(func)                   \
  TEST (dualf, func) { func<dualf>(); } \
  TEST (duald, func) { func<duald>(); } \
  TEST (dualld, func) { func<dualld>(); } \
  TEST (dualdf, func) { func<dualcf>(); } \
  TEST (dualcd, func) { func<dualcd>(); } \
  TEST (dualcld, func) { func<dualcld>(); }
#else
#define TESTALL(func) \
  TEST (dualf, func) { func<dualf>(); } \
  TEST (duald, func) { func<duald>(); }
#endif

//                                               
//  TEST (hyperdualf, func) { func<hyperdualf>(); }     
//  TEST (hyperdualcd, func) { func<hyperdualcd>(); }

#ifndef __CUDACC__
#define TESTREAL(func) \
  TEST (duald, func) { func<duald>(); } \
  TEST (dualf, func) { func<dualf>(); } \
  TEST (dualld, func) { func<dualld>(); }
#else
#define TESTREAL(func) \
  TEST (duald, func) { func<duald>(); } \
  TEST (dualf, func) { func<dualf>(); }
#endif

#define TEST_TYPEMIX(func, type1, type2) \
  TEST (func, type1##_##type2) { func<type1,type2>(); }

#ifndef __CUDACC__
#define TYPEMIX6(RTYPE, func)                   \
  TEST_TYPEMIX(func, RTYPE, float)              \
  TEST_TYPEMIX(func, RTYPE, double)             \
  TEST_TYPEMIX(func, RTYPE, longdouble)         \
  TEST_TYPEMIX(func, RTYPE, complexf)           \
  TEST_TYPEMIX(func, RTYPE, complexd)           \
  TEST_TYPEMIX(func, RTYPE, complexld)
#else
#define TYPEMIX6(RTYPE, func)                   \
  TEST_TYPEMIX(func, RTYPE, float)              \
  TEST_TYPEMIX(func, RTYPE, double)             \
  TEST_TYPEMIX(func, RTYPE, longdouble)
#endif
