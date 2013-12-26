#ifndef MatrixTest_hh
#define MatrixTest_hh 1

#include <iostream>
#include <assert.h>
#include <map>
#include <vector>
#include <cmath>
#include <string.h>
#include <stdio.h>

#include "RLMacros.hpp"
#include "GenericUnitTest.hh"
#include "Matrix.hpp"

#include <iostream>

using namespace std;

class MatrixTest : 
  public GenericUnitTest
{
 public:
  int RunTests() const; ///Main function.
  string ToString() const;
 protected:
  int TestCase1() const; /// Test case.
  int TestCase2() const; ///Test case.
  int TestCase3() const;
};
#endif
