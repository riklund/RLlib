#include "RunTests.hh"


int main()
{
  addTests();
  cout << "Running unit tests..." << endl;
  for(list<GenericUnitTest*>::iterator it = myTests.begin(); it!=myTests.end(); it++)
    {
	  cout << "Running tests on " << (*it)->ToString() << "...";
	  cout << flush;
      int response = (*it)->RunTests();
      if(response!=0)
		{
		  cout << "Test failed! Further testing terminated." << endl;
		  return response;
		}
	  cout << "done" << endl;
    }
  cout << "All tests were successful." << endl;
  return 0;
}


void addTests()
{
  #include "ExistingTests.cff"
}
