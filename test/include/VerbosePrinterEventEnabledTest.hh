#ifndef VerbosePrinterEventEnabledTest_hh
#define VerbosePrinterEventEnabledTest_hh 1

#include <iostream>
#include <assert.h>
#include <map>
#include <vector>
#include <cmath>
#include <string.h>
#include <stdio.h>

#include "GenericUnitTest.hh"
#include "VerbosePrinterEventEnabled.hh"

#include <iostream>

#ifndef EPSILON
#define EPSILON 1E-9
#endif

using namespace std;

class VerbosePrinterEventEnabledTest : public GenericUnitTest
{
 public:
  int runUnitTests() const; ///Main function.
 protected:
  bool Test_ConstructsCorrectly_Case1() const; /// Test case.

};
#endif
