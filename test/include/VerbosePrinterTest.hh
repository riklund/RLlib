#ifndef VerbosePrinterTest_hh
#define VerbosePrinterTest_hh 1

#include <iostream>
#include <assert.h>
#include <map>
#include <vector>
#include <cmath>
#include <string.h>
#include <stdio.h>

#include "GenericUnitTest.hh"
#include "VerbosePrinter.hh"

#include <iostream>

#ifndef EPSILON
#define EPSILON 1E-9
#endif

#ifndef TEMP_FILE
#define TEMP_FILE "temp/vask1.txt"
#endif

using namespace std;

class VerbosePrinterTest 
  : public GenericUnitTest
{
 public:
  int RunTests() const; ///Main function.
  string ToString() const;
 protected:
  bool Test_WritesToFileCorrectly_Case1() const; /// Test case.
  bool Test_WritesToFileCorrectly_Case2() const; /// Test case.
};
#endif
