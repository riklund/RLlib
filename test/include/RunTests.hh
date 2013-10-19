/** \file RunTests.hh
    \author Rikard Lundmark
    \brief Header for the unit test program, executes unit tests.
    \ingroup UnitTests
*/

/** \file RunTests.cc
    \author Rikard Lundmark
    \brief The unit test program, executes unit tests.
    \ingroup UnitTests
*/

/** @defgroup UnitTests Unit tests
 *  Unit tests.
 \author Rikard Lundmark
 \todo Create more unit tests
 */
#ifndef RunTests_hh
#define RunTests_hh 1

using namespace std;
#include <assert.h>
#include <iostream>
#include <list>
#include <string>
#include "AllHeaders.cff"


#define ADDMACRO_BEFORE myTests.push_back((GenericUnitTest*)(new 
#define ADDMACRO_AFTER ()));

#include "GenericUnitTest.hh"


int main();/// The main test function and program entry point.
void addTests(); /// Called by main() to prepare the test cases.
list<GenericUnitTest*> myTests; /// The existing test cases.

#endif
