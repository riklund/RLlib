/** \file GenericUnitTest.hh
    \author Rikard Lundmark
    \brief Generic test class
    \ingroup Unit tests
*/
/**
   \file GenericUnitTest.cc
   \author Rikard Lundmark
   \brief Generic test class
 */

using namespace std;

#ifndef GenericUnitTest_hh
#define GenericUnitTest_hh 1

#include <string>

class GenericUnitTest
{
 public:
  virtual int RunTests() const = 0; /// Run the tests.
  GenericUnitTest(); /// Constructor, constructs the class.
  virtual string ToString() const = 0;
};
#endif
