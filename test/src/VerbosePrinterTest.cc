#include "VerbosePrinterTest.hh"

bool VerbosePrinterTest::Test_WritesToFileCorrectly_Case1() const
{
  bool toReturn = true;
  VerbosePrinter * myPrinter = new VerbosePrinter(5,TEMP_FILE);
  for(int i = 0; i<10; ++i)
	myPrinter->Print(i, "%d ", i);

  delete myPrinter;
  FILE * in = fopen(TEMP_FILE, "r");
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

  remove(TEMP_FILE);
  return toReturn;
}

bool VerbosePrinterTest::Test_WritesToFileCorrectly_Case2() const
{
  bool toReturn = true;
  VerbosePrinter * myPrinter = new VerbosePrinter(5,TEMP_FILE);
  myPrinter->Print(4, "TESTSTRANG%d", 1332);
  
  delete myPrinter;
  FILE * in = fopen(TEMP_FILE, "r");
  char buffer[40];
  int vask2 = fscanf(in, "%s", buffer);
  (void) vask2;
  if( strcmp(buffer, "TESTSTRANG1332") != 0)
	toReturn = false;

  fclose(in);

  remove(TEMP_FILE);

  return toReturn;
}


int VerbosePrinterTest::RunTests() const
{
  if(!Test_WritesToFileCorrectly_Case1())
    return 1;
  if(!Test_WritesToFileCorrectly_Case2())
    return 1;
  return 0;
}

string VerbosePrinterTest::ToString() const
{
  return "VerbosePrinter";
}
