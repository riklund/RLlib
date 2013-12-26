#include "VerbosePrinterEventEnabledTest.hh"

bool VerbosePrinterEventEnabledTest::Test_ConstructsCorrectly_Case1() const
{
  VerbosePrinterEventEnabled * myEnabled = new VerbosePrinterEventEnabled();
  delete myEnabled;
  return true;
}


int VerbosePrinterEventEnabledTest::RunTests() const
{
  if(!Test_ConstructsCorrectly_Case1())
    return 1;
  return 0;
}


string VerbosePrinterEventEnabledTest::ToString() const
{
  return "VerbosePrinterEventEnabled";
}
