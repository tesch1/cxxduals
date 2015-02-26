#include "gtest/gtest.h"
#include <iostream>
#include <complex>
#include <cxxduals/dual>

using namespace cxxduals;

TEST (DualTest, Construct)
{
  dual<double> x = 1.1;
  EXPECT_EQ(x.realpart(), 1.1);
  EXPECT_EQ(realpart(x), 1.1);
  EXPECT_EQ(x.epart(), 0.0);
  EXPECT_EQ(epart(x), 0.0);

  dual<double> z(1.1);
  EXPECT_EQ(z.realpart(), 1.1);
  EXPECT_EQ(realpart(z), 1.1);
  EXPECT_EQ(z.epart(), 0.0);
  EXPECT_EQ(epart(z), 0.0);

  dual<double> y(1.1, 2.2);
  EXPECT_EQ(y.realpart(), 1.1);
  EXPECT_EQ(realpart(y), 1.1);
  EXPECT_EQ(y.epart(), 2.2);
  EXPECT_EQ(epart(y), 2.2);

  dual<double> w = {1.1, 2.2};
  EXPECT_EQ(w.realpart(), 1.1);
  EXPECT_EQ(w.epart(), 2.2);

  dual<double> a{1.1, 2.2};
  EXPECT_EQ(a.realpart(), 1.1);
  EXPECT_EQ(a.epart(), 2.2);
}

template <typename DUALTYPE, typename Scalar>
void equality()
{
  DUALTYPE d{1.1, 2.2};
  DUALTYPE e{1.1, 2.2};
  DUALTYPE f{1.1, 2.21};
  DUALTYPE g{2.2, 2.21};
  DUALTYPE h{-2.2, -2.21};
  DUALTYPE j{3, 1};
  DUALTYPE k{9, 6};
  DUALTYPE l{9, 1};
  EXPECT_EQ(e, d);
  EXPECT_EQ(e, f);
  EXPECT_NE(f, g);
  EXPECT_NE(f, h);
  EXPECT_NE(f, (Scalar)1.2);
  EXPECT_NE((Scalar)1.2, f);
  EXPECT_EQ(j*j, k);
  EXPECT_EQ(pow(j,(Scalar)2.0), k);
  EXPECT_EQ(sqrt(l), j);
  EXPECT_EQ(abs(h), g);
  EXPECT_EQ(abs(-h), g);
  EXPECT_EQ(-abs(h), h);
  EXPECT_EQ(abs(h), (Scalar)2.2);
  EXPECT_EQ(+abs(h), (Scalar)2.2);
  EXPECT_EQ(-abs(h), (Scalar)-2.2);
}

template <typename DUALTYPE, typename Scalar>
void compare()
{
  DUALTYPE d{1.1, 2.2};
  DUALTYPE e{1.1, 2.2};
  DUALTYPE f{1.1, 2.21};
  DUALTYPE g{2.2, 2.21};
  DUALTYPE h{-2.2, -2.21};
  DUALTYPE j{3, 0};
  DUALTYPE k{9, 6};
  DUALTYPE l{9, 1};
  EXPECT_NEAR(epart(sqrt(l)), (Scalar)(0.5*pow(9,-0.5)), (Scalar)1e-15);
  EXPECT_GT((Scalar)1.2, d);
  EXPECT_GT(d,(Scalar)1.0);
  EXPECT_GT(g,f);
  EXPECT_LT((Scalar)1.0, d);
  EXPECT_LT(d,(Scalar)1.2);
  EXPECT_LT(f,g);
  EXPECT_LE(d,(Scalar)1.1);
  EXPECT_LE((Scalar)1.1,d);
  EXPECT_LE(f,g);
  EXPECT_LE(f,e);
  EXPECT_GE(d,(Scalar)1.1);
  EXPECT_GE((Scalar)1.1,d);
  EXPECT_GE(g,f);
  EXPECT_GE(e,f);
  EXPECT_TRUE(max(f,(Scalar)2.2) == (Scalar)2.2);
  EXPECT_TRUE(max((Scalar)2.2,f) == (Scalar)2.2);
  EXPECT_TRUE(min(f,(Scalar)2.2) == f);
  EXPECT_TRUE(min((Scalar)2.2,f) == f);
  EXPECT_TRUE(max(f,g) == g);
  EXPECT_TRUE(max(g,f) == g);
  EXPECT_TRUE(min(f,g) == f);
  EXPECT_TRUE(min(g,f) == f);
}

TEST (Duald, Equality)
{
  equality<duald, double>();
  //compare<duald, float>();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout.precision(20);
  std::cerr.precision(20);
  return RUN_ALL_TESTS();
}
