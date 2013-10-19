#include "VerbosePrinterEventEnabledTest.hh"

bool VerbosePrinterEventEnabledTest::Test_ConstructsCorrectly_Case1() const
{
  VerbosePrinterEventEnabled * myEnabled = new VerbosePrinterEventEnabled();
  delete myEnabled;
  return true;
}


int VerbosePrinterEventEnabledTest::runUnitTests() const
{
  cout << "Running unit tests on VerbosePrinterEventEnabled...";
  cout << flush;
  if(!Test_ConstructsCorrectly_Case1())
    return 1;
  cout << "done" << endl;
  return 0;
}
