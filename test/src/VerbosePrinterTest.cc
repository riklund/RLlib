#include "VerbosePrinterTest.hh"

bool VerbosePrinterTest::Test_WritesToFileCorrectly_Case1() const
{
  bool toReturn = true;
  char tempFileName [L_tmpnam];
  tmpnam (tempFileName);
  VerbosePrinter * myPrinter = new VerbosePrinter(5,tempFileName);
  for(int i = 0; i<10; ++i)
	myPrinter->Print(i, "%d ", i);

  delete myPrinter;
  FILE * in = fopen(tempFileName, "r");
  int count = 0;
  int N;
  while(fscanf(in, "%d", &N) != EOF)
	{
	  if( N != count )
		toReturn = false;
	  ++count;
	}
  if(count != 6)
	toReturn = false;
  fclose(in);

  remove(tempFileName);
  return toReturn;
}

bool VerbosePrinterTest::Test_WritesToFileCorrectly_Case2() const
{
  bool toReturn = true;
  char tempFileName [L_tmpnam];
  tmpnam (tempFileName);
  VerbosePrinter * myPrinter = new VerbosePrinter(5,tempFileName);
  myPrinter->Print(4, "TESTSTRANG%d", 1332);
  
  delete myPrinter;
  FILE * in = fopen(tempFileName, "r");
  char buffer[40];
  fscanf(in, "%s", buffer);
  if( strcmp(buffer, "TESTSTRANG1332") != 0)
	toReturn = false;

  fclose(in);

  remove(tempFileName);

  return toReturn;
}


int VerbosePrinterTest::runUnitTests() const
{
  cout << "Running unit tests on VerbosePrinter...";
  cout << flush;
  if(!Test_WritesToFileCorrectly_Case1())
    return 1;
  if(!Test_WritesToFileCorrectly_Case2())
    return 1;
  cout << "done" << endl;
  return 0;
}
