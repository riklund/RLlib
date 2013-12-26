#ifndef RLExceptionTest_hh
#define RLExceptionTest_hh 1

#include <iostream>
#include <assert.h>
#include <map>
#include <vector>
#include <cmath>
#include <string.h>
#include <stdio.h>

#include "GenericUnitTest.hh"
#include "RLException.hh"

#include <iostream>

#ifndef EPSILON
#define EPSILON 1E-9
#endif

using namespace std;

class RLExceptionTest 
  : public GenericUnitTest
{
 public:
  int RunTests() const; ///Main function.
  string ToString() const;
 protected:
  bool Test_ConstructsAndReturnsCorrectly_Case1() const; /// Test case.
  bool Test_ConstructsAndReturnsCorrectly_Case2() const; /// Test case.
  bool Test_ConstructsAndReturnsCorrectly_VA1() const; /// Test case.
};
#endif
