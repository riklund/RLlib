#include "RunTests.hh"


int main()
{
  addTests();
  cout << "Running unit tests..." << endl;
  for(list<GenericUnitTest*>::iterator it = myTests.begin(); it!=myTests.end(); it++)
    {
      int response = (*it)->runUnitTests();
      if(response!=0)
	{
	  cout << "Test failed! Further testing terminated." << endl;
	  return response;
	}
    }
  cout << "All tests were successful." << endl;
  return 0;
}


void addTests()
{
  #include "ExistingTests.cff"
}
